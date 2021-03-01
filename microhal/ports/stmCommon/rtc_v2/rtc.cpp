/**
 * @license    BSD 3-Clause
 * @version    $Id$
 * @brief      RTC driver for STM microcontrolers version 2
 *
 * @authors    Pawel Okas
 * created on: 09-02-2021
 *
 * @copyright Copyright (c) 2021, Pawel Okas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this
 *        software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ports/stmCommon/rtc_v2/rtc.h>
#include <cassert>
#include _MICROHAL_INCLUDE_PORT_DEVICE

namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {

Signal<void> RTC::interrupt;

//------------------------------------------------------------------------------
//                             time read
//------------------------------------------------------------------------------
RTC::ResultSubsecond RTC::subsecond() {
    ResultSubsecond result(Error::NoData);
    if (registers::rtc->icsr.volatileLoad().RSF) {
        auto ssr = registers::rtc->ssr.volatileLoad();
        result.value(ssr.SS.get());
    }
    return result;
}

RTC::ResultTime RTC::time() {
    ResultTime result(Error::NoData);
    if (registers::rtc->icsr.volatileLoad().RSF) {
        auto tr = registers::rtc->tr.volatileLoad();
        Time &time = result.value();
        time.hour = tr.HT * 10 + tr.HU;
        time.minute = tr.MNT * 10 + tr.MNU;
        time.second = tr.ST * 10 + tr.SU;
        time.amPm = static_cast<AM_PM>(tr.PM.get());
        result.error(Error::None);
        return result;
    }
    return result;
}

RTC::ResultDate RTC::date() {
    ResultDate result(Error::NoData);
    if (registers::rtc->icsr.volatileLoad().RSF) {
        auto dr = registers::rtc->dr.volatileLoad();
        Date &date = result.value();
        date.weekDay = dr.WDU;
        date.month = dr.MT * 10 + dr.MU;
        date.monthDay = dr.DT * 10 + dr.DU;
        result.error(Error::None);
    }
    return result;
}
//------------------------------------------------------------------------------
//                             timestamp read
//------------------------------------------------------------------------------
RTC::ResultSubsecond RTC::timestampSubsecond() {
    ResultSubsecond result(Error::NoData);
    if (registers::rtc->sr.volatileLoad().TSF) {
        auto ssr = registers::rtc->tsssr.volatileLoad();
        result.value(ssr.SS.get());
    }
    return result;
}

RTC::ResultTime RTC::timestampTime() {
    ResultTime result(Error::NoData);
    auto sr = registers::rtc->sr.volatileLoad();
    if (sr.TSF) {
        auto tstr = registers::rtc->tstr.volatileLoad();
        Time &time = result.value();
        time.hour = tstr.HT * 10 + tstr.HU;
        time.minute = tstr.MNT * 10 + tstr.MNU;
        time.second = tstr.ST * 10 + tstr.SU;
        time.amPm = static_cast<AM_PM>(tstr.PM.get());
        result.error(Error::None);
    }
    return result;
}

RTC::ResultDate RTC::timestampDate() {
    ResultDate result(Error::NoData);
    auto sr = registers::rtc->sr.volatileLoad();
    if (sr.TSF) {
        auto tsdr = registers::rtc->tsdr.volatileLoad();
        Date &date = result.value();
        date.weekDay = tsdr.WDU;
        date.month = tsdr.MT * 10 + tsdr.MU;
        date.monthDay = tsdr.DT * 10 + tsdr.DU;
        result.error(Error::None);
    }
    return result;
}
//------------------------------------------------------------------------------
//                             set date & time
//------------------------------------------------------------------------------
bool RTC::setSubsecond(uint16_t subsecond) {
    if (registers::rtc->icsr.volatileLoad().INITF) {
        registers::RTC::SSR ssr{};
        ssr.SS = subsecond;
        registers::rtc->ssr.volatileStore(ssr);
        return true;
    }
    return false;
}

bool RTC::setTime(const Time &time) {
    if (registers::rtc->icsr.volatileLoad().INITF) {
        registers::RTC::TR tr{};
        tr.HT = time.hour / 10;
        tr.HU = time.hour % 10;
        tr.MNT = time.minute / 10;
        tr.MNU = time.minute % 10;
        tr.ST = time.second / 10;
        tr.SU = time.second % 10;
        tr.PM = static_cast<uint8_t>(time.amPm);
        registers::rtc->tr.volatileStore(tr);
        return true;
    }
    return false;
}

bool RTC::setDate(const Date &date) {
    assert(date.month > 0);
    assert(date.month <= 12);
    assert(date.weekDay > 0);
    assert(date.weekDay < 8);
    assert(date.year >= 2000);
    assert(date.year < 2100);

    if (registers::rtc->icsr.volatileLoad().INITF) {
        registers::RTC::DR dr{};
        dr.YT = (date.year % 100) / 10;
        dr.YU = date.year % 10;
        dr.MT = date.month / 10;
        dr.MU = date.month % 10;
        dr.WDU = date.weekDay;
        dr.DT = date.monthDay / 10;
        dr.DU = date.monthDay % 10;
        registers::rtc->dr.volatileStore(dr);
        return true;
    }
    return false;
}

bool RTC::setPrescaler(uint16_t async_prescaler, uint16_t sync_prescaler) {
    assert(async_prescaler > 0);
    assert(async_prescaler <= 128);
    assert(sync_prescaler > 0);
    assert(sync_prescaler <= 65536);

    registers::RTC::PRER prer{};
    prer.PREDIV_A = async_prescaler - 1;
    prer.PREDIV_S = sync_prescaler - 1;
    registers::rtc->prer.volatileStore(prer);
    return true;
}
//------------------------------------------------------------------------------
//                             Wakeup timer
//------------------------------------------------------------------------------
bool RTC::configureWakeupTimer(WakeupTimerClk clk, uint16_t wakeup) {
    auto cr = registers::rtc->cr.volatileLoad();
    if (!cr.WUTE) {
        auto icsr = registers::rtc->icsr.volatileLoad();
        if (!icsr.INIT) {
            // Poll WUTWF until it is set
            while (!icsr.WUTWF) {
                icsr = registers::rtc->icsr.volatileLoad();
            }
        }

        cr.WUCKSEL = static_cast<uint32_t>(clk);
        registers::rtc->cr.volatileStore(cr);

        registers::rtc->wutr.volatileStore(wakeup);
        return true;
    }
    return false;
}

bool RTC::enableWakeupTimer() {
    auto cr = registers::rtc->cr.volatileLoad();
    cr.WUTE.set();
    registers::rtc->cr.volatileStore(cr);
    if (!registers::rtc->cr.volatileLoad().WUTE) return false;
    return true;
}

bool RTC::disableWakeupTimer() {
    auto cr = registers::rtc->cr.volatileLoad();
    if (cr.WUTE) {
        cr.WUTE.clear();
        registers::rtc->cr.volatileStore(cr);
        if (registers::rtc->cr.volatileLoad().WUTE) return false;
    }
    return true;
}

bool RTC::isWakeupTimerEnabled() {
    return registers::rtc->cr.volatileLoad().WUTE;
}
//------------------------------------------------------------------------------
//                             Interrupts
//------------------------------------------------------------------------------
bool RTC::enableInterrupt(Interrupt interrupt) {
    auto cr = registers::rtc->cr.volatileLoad();
    if (interrupt & Interrupt::AlarmA) cr.ALRAIE.set();
    if (interrupt & Interrupt::AlarmB) cr.ALRBIE.set();
    if (interrupt & (Interrupt::Timestamp | Interrupt::TimestampOverflow)) cr.TSIE.set();
    if (interrupt & Interrupt::WakeupTimer) cr.WUTIE.set();
    registers::rtc->cr.volatileStore(cr);
    return true;
}

bool RTC::disableInterrupt(Interrupt interrupt) {
    auto cr = registers::rtc->cr.volatileLoad();
    if (interrupt & Interrupt::AlarmA) cr.ALRAIE.clear();
    if (interrupt & Interrupt::AlarmB) cr.ALRBIE.clear();
    if (interrupt & (Interrupt::Timestamp | Interrupt::TimestampOverflow)) cr.TSIE.clear();
    if (interrupt & Interrupt::WakeupTimer) cr.WUTIE.clear();
    registers::rtc->cr.volatileStore(cr);
    return true;
}

bool RTC::clearInterruptFlag(Interrupt interrupt) {
    registers::rtc->scr.volatileStore(static_cast<uint32_t>(interrupt));
    return true;
}

RTC::Interrupt RTC::getInterruptFlag() {
    return static_cast<Interrupt>((uint32_t)registers::rtc->sr.volatileLoad());
}

bool RTC::enableNVICInterrupt(uint32_t priority) {
    NVIC_SetPriority(RTC_TAMP_IRQn, priority);
    NVIC_EnableIRQ(RTC_TAMP_IRQn);
    return true;
}
//------------------------------------------------------------------------------
//                             Configuration mode
//------------------------------------------------------------------------------
bool RTC::enterConfigurationMode() {
    auto icsr = registers::rtc->icsr.volatileLoad();
    icsr.INIT.set();
    registers::rtc->icsr.volatileStore(icsr);
    if (registers::rtc->icsr.volatileLoad().INIT) {
        while (!registers::rtc->icsr.volatileLoad().INITF) {
        }
        return true;
    }
    return false;
}

void RTC::exitConfigurationMode() {
    auto icsr = registers::rtc->icsr.volatileLoad();
    icsr.INIT.clear();
    registers::rtc->icsr.volatileStore(icsr);
}

void RTC::disableWriteProtection() {
    uint32_t key = 0xCA;
    registers::rtc->wpr.volatileStore(key);
    key = 0x53;
    registers::rtc->wpr.volatileStore(key);
}

void RTC::enableWriteProtection() {
    uint32_t key = 0x00;
    registers::rtc->wpr.volatileStore(key);
}

extern "C" void RTC_TAMP_IRQHandler(void) {
    RTC::interrupt.emit();
}

}  // namespace _MICROHAL_ACTIVE_PORT_NAMESPACE
}  // namespace microhal
