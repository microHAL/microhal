/**
 * @file
 * @license    BSD 3-Clause
 * @version    $Id$
 * @brief      Serial Port implementation for STM32Fxxx
 *
 * @authors    Pawel Okas
 * created on: 2013
 * last modification: <DD-MM-YYYY>
 *
 * @copyright Copyright (c) 2013-2019, Pawel Okas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 	   2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the
 * 	      documentation and/or other materials provided with the distribution.
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

#ifndef _MICROHAL_PORTS_SERIALPORT_STMCOMMON_H_
#define _MICROHAL_PORTS_SERIALPORT_STMCOMMON_H_
/* ************************************************************************************************
 * 1.) Check if this driver should be used on selected MCU.
 * 2.) Check if this driver is enabled in microhal port configuration file
 */
#include <ports/stmCommon/driverConfiguration_stmCommon.h>
#if _MICROHAL_PORT_STM_SERIAL_PORT_DRIVER_VERSION == 1  // Check if driver is compatible with selected MCU
#include "serialPort_preprocessor_macros.h"
#if ENABLED_ANY_SERIAL_PORT(POLLING) || ENABLED_ANY_SERIAL_PORT(INTERRUPT) || \
    ENABLED_ANY_SERIAL_PORT(DMA)  // Check if driver is enabled in microhal port config
/* ************************************************************************************************
 * INCLUDES
 */
#include <ports/stmCommon/usart/usart.h>
#include <cstdint>
#include "../clockManager/usartClock.h"
#include "../stmCommonDefines.h"
#include "interfaces/serialPort_interface.h"

#if defined(MCU_TYPE_STM32F3XX) || defined(MCU_TYPE_STM32F0XX) || defined(MCU_TYPE_STM32G0XX)
#include "../registers/usartRegisters_v2.h"
#else
#include "../registers/usartRegisters_v1.h"
#endif

namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {
/* ************************************************************************************************
 * CLASS
 */
/**
 *
 * @class SerialPort
 *
 * @brief   This class implements SerialPort functions.
 */
class SerialPort : public microhal::SerialPort {
 public:
#if (MICROHAL_USE_SERIAL_PORT1_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT1_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT1_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT1_DMA == 1)
    static SerialPort &Serial1;
#endif
#if (MICROHAL_USE_SERIAL_PORT2_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT2_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT2_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT2_DMA == 1)
    static SerialPort &Serial2;
#endif
#if (MICROHAL_USE_SERIAL_PORT3_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT3_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT3_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT3_DMA == 1)
    static SerialPort &Serial3;
#endif
#if (MICROHAL_USE_SERIAL_PORT4_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT4_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT4_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT4_DMA == 1)
    static SerialPort &Serial4;
#endif
#if (MICROHAL_USE_SERIAL_PORT5_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT5_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT5_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT5_DMA == 1)
    static SerialPort &Serial5;
#endif
#if (MICROHAL_USE_SERIAL_PORT6_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT6_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT6_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT6_DMA == 1)
    static SerialPort &Serial6;
#endif
#if (MICROHAL_USE_SERIAL_PORT7_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT7_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT7_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT7_DMA == 1)
    static SerialPort &Serial7;
#endif
#if (MICROHAL_USE_SERIAL_PORT8_POLLING == 1) || (MICROHAL_USE_SERIAL_PORT8_INTERRUPT == 1) || (MICROHAL_USE_SERIAL_PORT8_INTERRUPT_DMA == 1) || \
    (MICROHAL_USE_SERIAL_PORT8_DMA == 1)
    static SerialPort &Serial8;
#endif

    bool open(OpenMode mode) noexcept override = 0;
    bool isOpen(void) const noexcept final { return usart.cr1.volatileLoad().UE; }
    void close() noexcept final { usart.cr1.volatileStore(0); }

    bool setBaudRate(uint32_t baudRate) noexcept final;
    uint32_t getBaudRate() const noexcept final;
    bool setParity(SerialPort::Parity parity) noexcept final;
    bool setStopBits(SerialPort::StopBits stopBits) noexcept final;
    bool setDataBits(SerialPort::DataBits dataBits) noexcept final;

    void priority(uint32_t priority);

 protected:
    //------------------------------------------- variables -----------------------------------------//
    registers::USART &usart;
//------------------------------------------- constructors --------------------------------------//
#if defined(__MICROHAL_MUTEX_CONSTEXPR_CTOR)
    constexpr
#endif
        SerialPort(registers::USART &usart) noexcept
        : usart(usart) {
    }

    void enableInterrupt(uint32_t priority);
};

}  // namespace _MICROHAL_ACTIVE_PORT_NAMESPACE
}  // namespace microhal
#else
namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {}
}  // namespace microhal
#endif  // ENABLED_ANY_SERIAL_PORT(POLLING) || ENABLED_ANY_SERIAL_PORT(INTERRUPT) || ENABLED_ANY_SERIAL_PORT(DMA)
#endif  // _MICROHAL_PORT_STM_SERIAL_PORT_DRIVER_VERSION == 1
#endif  // _MICROHAL_PORTS_SERIALPORT_STMCOMMON_H_
