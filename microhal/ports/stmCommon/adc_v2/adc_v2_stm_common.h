/**
 * @license    BSD 3-Clause
 * @version    $Id$
 * @brief      ADC port driver for: STM32F102, STM32F107, STM32F101, STM32F103, STM32F101, STM32F7x9, STM32F765, STM32F7x8, STM32F7x3, STM32F7x2,
 *                                  STM32F745, STM32F730, STM32F750, STM32F7x7, STM32F7x6, STM32F407, STM32F429, STM32F469, STM32F411, STM32F413,
 *                                  STM32F412, STM32F401, STM32F427, STM32F405, STM32F446, STM32F410, STM32F217, STM32F215
 *
 * @authors    Pawel Okas
 *
 * @copyright Copyright (c) 2020, Pawel Okas
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

#ifndef _MICROHAL_PORTS_ADC_V2_STMCOMMON_H_
#define _MICROHAL_PORTS_ADC_V2_STMCOMMON_H_
/* **************************************************************************************************************************************************
 * INCLUDES
 */
#include "../registers/adc_registers_v2.h"
#include "../stmCommonDefines.h"
#include "gsl/gsl"
#include "microhal_semaphore.h"
#include "ports/stm32f1xx/nvic.h"
#include "ports/stmCommon/clockManager/adcClock.h"
#include "signalSlot/signalSlot.h"

#include _MICROHAL_INCLUDE_PORT_DEVICE  // stmCommonDefines.h have to be included before this
#include _MICROHAL_INCLUDE_PORT_CONFIG

#ifndef _MICROHAL_ACTIVE_PORT_NAMESPACE
#error _MICROHAL_ACTIVE_PORT_NAMESPACE have to be defined.
#endif

namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {

/* ************************************************************************************************
 * EXTERN DECLARATION
 */
extern "C" {
void ADC1_2_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
}
/* **************************************************************************************************************************************************
 * CLASS
 */
namespace adc_detail {
enum class Interrupt {
    AnalogWatchdog1 = 0b0'0001,          //
    EndOfRegularConversion = 0b0'0010,   //
    EndOfInjectedConversion = 0b0'0100,  //
};

constexpr Interrupt operator|(Interrupt a, Interrupt b) {
    return static_cast<Interrupt>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

constexpr Interrupt operator&(Interrupt a, Interrupt b) {
    return static_cast<Interrupt>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
constexpr uint32_t operator&(uint32_t a, adc_detail::Interrupt b) {
    return a & static_cast<uint32_t>(b);
}

}  // namespace adc_detail

using adc_detail::operator|;
using adc_detail::operator&;

class Adc final {
 public:
    using Interrupt = adc_detail::Interrupt;

    /**
     * @brief Possible ADC channels
     */
    typedef enum : uint32_t {
        Channel0 = 0x00000000,
        Channel1,
        Channel2,
        Channel3,
        Channel4,
        Channel5,
        Channel6,
        Channel7,
        Channel8,
        Channel9,
        Channel10,
        Channel11,
        Channel12,
        Channel13,
        Channel14,
        Channel15,
        Channel16,
        Channel17,
        Channel18,
    } Channel;

    enum class TriggerSource {
        TIM1_CC1_TIM3_CC1,          //!< TIM1 CC1 on ADC1 and ADC2, TIM3 CC1 on ADC3,
        TIM1_CC2_TIM2_CC3,          //!< TIM1 CC2 on ADC1 and ADC2, TIM2 CC3 on ADC3,
        TIM1_CC3,                   //!< TIM1 CC3 on ADC1, ADC2 and ADC3,
        TIM2_CC2_TIM8_CC1,          //!< TIM2 CC2 on ADC1 and ADC2, TIM8 CC1 on ADC3,
        TIM3_TRGO_TIM8_TRGO,        //!< TIM3 TRGO on ADC1 and ADC2, TIM8 TRGO on ADC3,
        TIM4_CC4_TIM5_CC1,          //!< TIM4 CC4 on ADC1 and ADC2, TIM5 CC1 on ADC3,
        EXTI11_TIM8_TRGO_TIM5_CC3,  //!< EXTI11 or TIM8 TRGO on ADC1 and ADC2, TIM5 CC3 on ADC3,
        Software
    };

    enum class DualADCMode {
        Independent = 0,
        CombinedRegularSimultaneousAndInjectedSimultaneous,
        CombinedRegularSimultaneousAndAlternateTrigger,
        CombinedInjectedSimultaneousAndFastInterleaved,
        CombinedInjectedSimultaneousAndSlowInterleaved = 0b0100,
        InjectedSimultaneousOnly,
        RegularSimultaneousOnly,
        FastInterleavedOnly,
        AlternateTriggerOnly
    };

    void initDMA(uint16_t *data, size_t len);

    Interrupt getInterrupFlags() const {
        uint32_t sr = adc.sr.volatileLoad();
        return static_cast<Interrupt>(sr);
    }
    void clearInterruptFlags(Interrupt interrupt) {
        auto sr = adc.sr.volatileLoad();
        sr &= ~static_cast<uint32_t>(interrupt);
        adc.sr.volatileStore(sr);
    }

    //=================== ADC On Off functions ===================
    bool enable() {
        auto cr2 = adc.cr2.volatileLoad();
        cr2.ADON = 1;
        adc.cr2.volatileStore(cr2);
        return true;
    }

    bool disable() {
        auto cr2 = adc.cr2.volatileLoad();
        cr2.ADON = 0;
        adc.cr2.volatileStore(cr2);
        return true;
    }

    bool isEnabled() { return adc.cr2.volatileLoad().ADON; }

    //=================== Regular conversion functions ===================
    /**
     *
     * @return
     */
    bool configureSamplingSequence(gsl::span<Adc::Channel> sequence);
    /**
     *
     * @param triggerSource - @ref TriggerSource
     * @param eventNumber - Select hardware trigger source
     */
    void configureTriggerSource(TriggerSource externalTrigger);
    void enableTriggerSource() {
        auto cr2 = adc.cr2.volatileLoad();
        cr2.EXTTRIG.set();
        adc.cr2.volatileStore(cr2);
    }
    void disableTriggerSource() {
        auto cr2 = adc.cr2.volatileLoad();
        cr2.EXTTRIG.clear();
        adc.cr2.volatileStore(cr2);
    }
    /**
     *
     * @retval true if conversion was started
     * @retval false when conversion start is impossible. This may be caused by disabled ADC or ADC trigger is different from Software trigger.
     */
    bool startConversion() {
        // Software is allowed to set SWSTART only when ADON=1 and EXTSEL=SWSTART (ADC is enabled and conversion trigger is set to software)
        auto cr2 = adc.cr2.volatileLoad();
        if (cr2.ADON == 1 && cr2.EXTSEL == 0b111) {
            cr2.SWSTART.set();
            adc.cr2.volatileStore(cr2);
            return true;
        }
        return false;
    }
    bool waitForConversionEnd(uint32_t ms = 10000) {
        while (ms--) {
            if (adc.sr.volatileLoad().EOC) {
                return true;
            }
        }
        return false;
    }
    bool waitForRegularSequenceEnd(std::chrono::milliseconds timeout) { return regularSequenceFinishSemaphore.wait(timeout); }
    uint16_t readSamples() { return adc.dr.volatileLoad().DATA; }

    //=================== Injected conversion functions ===================
    bool configureInjectedSamplingSequence(gsl::span<Adc::Channel> sequence);
    bool configureInjectedChannelOffset(Channel channel, uint16_t offset);
    std::array<uint16_t, 4> readInjectedSamples() {
        return {adc.jdr[0].volatileLoad().JDATA, adc.jdr[1].volatileLoad().JDATA, adc.jdr[2].volatileLoad().JDATA, adc.jdr[3].volatileLoad().JDATA};
    }
    /**
     *
     * @retval true if injected conversion was started
     * @retval false when conversion start is impossible. This may be caused by disabled ADC or ADC trigger is different from Software trigger.
     */
    bool startInjectedConversion() {
        // Software is allowed to set JSWSTART only when ADON=1 and EXTSEL=SWSTART (ADC is enabled and conversion trigger is set to software)
        auto cr2 = adc.cr2.volatileLoad();
        if (cr2.ADON == 1 && cr2.JEXTSEL == 0b111) {
            cr2.JSWSTART.set();
            adc.cr2.volatileStore(cr2);
            return true;
        }
        return false;
    }
    //=================== Analog watchdog functions ===================
    bool configureAnalogWatchdog(Channel channel, uint16_t lowThreshold, uint16_t highThreshold);
    bool enableAnalogWatchdog();
    bool disableAnalogWatchdog();
    bool enableAnalogWatchdogInterrupt();
    bool disableAnalogWatchdogInterrupt();
    bool registerAnalogWatchdogIsrFunction(void (*interruptFunction)(void), uint32_t interruptPriority) { return false; }

    template <typename T>
    bool registerAnalogWatchdogIsrFunction(const T &slot, const typename T::type &object) {
        return false;
    }

    //=================== ADC callibration functions ===================
    /**
     * @note ADC has to be enabled before calibration.
     */
    bool calibrate();
    bool waitForCallibrationFinish();
    bool resetCallibration() {
        auto cr2 = adc.cr2.volatileLoad();
        cr2.RSTCAL.set();
        adc.cr2.volatileStore(cr2);
        return true;
    }

    //=================== Temperature sensor functions ===================
    bool enableTemperatureSensor() {
        auto cr2 = adc.cr2.volatileLoad();
        cr2.TSVREFE.set();
        adc.cr2.volatileStore(cr2);
        return true;
    }
    bool disableTemperatureSensor() {
        auto cr2 = adc.cr2.volatileLoad();
        cr2.TSVREFE.clear();
        adc.cr2.volatileStore(cr2);
        return true;
    }

    Channel getTemperatureSensorChannel() const { return Channel16; }
    Channel getInteranlReferenceChannel() const { return Channel17; }

    bool registerIsrFunction(void (*interruptFunction)(void)) {
        if (interruptFunction == nullptr) {
            //   DMA::dma1->stream[0].disableInterrupt(DMA::Channel::Interrupt::TransferComplete);
            //  DMA::dma1->disableInterrupt(DMA::dma1->stream[0]);
        }
        if (signal.connect(interruptFunction)) {
            auto cr1 = adc.cr1.volatileLoad();
            cr1.EOCIE.set();
            adc.cr1.volatileStore(cr1);
            return true;
        }
        return false;
    }

    template <typename T>
    bool registerIsrFunction(const T &slot, const typename T::type &object) {
        if (signal.connect(slot, object)) {
            return true;
        }
        return false;
    }
    /**
     * Note: This function is enabling interrupt for both ADC1 and ADC2 devices
     * @param priority
     */
    void enableInterrupt(uint32_t priority) {
        NVIC_ClearPendingIRQ(ADC1_2_IRQn);
        NVIC_SetPriority(ADC1_2_IRQn, priority);
        NVIC_EnableIRQ(ADC1_2_IRQn);
    }
    /**
     * Note: This function is disabling interrupt for both ADC1 and ADC2 devices
     */
    void disableInterrupt() { NVIC_DisableIRQ(ADC1_2_IRQn); }

    void setDualADCMode(DualADCMode dualMode) {
        auto cr1 = adc.cr1.volatileLoad();
        cr1.DUALMOD = static_cast<uint32_t>(dualMode);
        adc.cr1.volatileStore(cr1);
    }

 public:
    Adc(registers::ADC *adc) : adc(*adc) {
        int adcNumber = 0;
        if ((int)adc == _MICROHAL_ADC1_BASE_ADDRESS) {
            adc1 = this;
            adcNumber = 1;
        }
        if ((int)adc == _MICROHAL_ADC2_BASE_ADDRESS) {
            adc2 = this;
            adcNumber = 2;
        }
        if ((int)adc == _MICROHAL_ADC3_BASE_ADDRESS) {
            adcNumber = 2;
        }

        ClockManager::enableADC(adcNumber);
    }
    ~Adc();

 private:
    static Adc *adc1;
    static Adc *adc2;
    microhal::registers::ADC &adc;
    microhal::os::Semaphore regularSequenceFinishSemaphore = {};
    Signal<void> signal = {};

    //    void enableInterrupts(Interrupt interrupts) {
    //        auto ier = adc.ier.volatileLoad();
    //        ier |= static_cast<uint32_t>(interrupts);
    //        adc.ier.volatileStore(ier);
    //    }

    void setSamplingSequence(uint_fast8_t sequenceLength, uint_fast8_t sequencePosition, Channel channel);

    void interruptFunction();

    friend void ADC1_2_IRQHandler(void);
    friend void DMA1_Channel1_IRQHandler(void);
};
}  // namespace _MICROHAL_ACTIVE_PORT_NAMESPACE
}  // namespace microhal
#endif  // _MICROHAL_PORTS_ADC_V2_STMCOMMON_H_
