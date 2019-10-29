/**
 * @file
 * @license    BSD 3-Clause
 * @version    $Id$
 * @brief      STM32F4xx serial port driver implementation. Driver support receiving and transmitting using interrupts.
 *
 * @authors    Pawel Okas
 * created on: 17-04-2014
 * last modification: <DD-MM-YYYY>
 *
 * @copyright Copyright (c) 2014-2019, Pawel Okas
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

/* ************************************************************************************************
 * INCLUDES
 */
#include "serialPort_interrupt_stmCommon.h"
#include _MICROHAL_INCLUDE_PORT_clockManager

namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {
//***********************************************************************************************//
//                                   STATIC VARIABLES
//***********************************************************************************************//
#ifdef MICROHAL_USE_SERIAL_PORT1_INTERRUPT
static char txBufferData_1[MICROHAL_SERIAL_PORT1_TX_BUFFER_SIZE];
static char rxBufferData_1[MICROHAL_SERIAL_PORT1_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial1(*USART1, rxBufferData_1, txBufferData_1, sizeof(rxBufferData_1), sizeof(txBufferData_1));
SerialPort &SerialPort::Serial1 = SerialPort_interrupt::Serial1;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT2_INTERRUPT
static char txBufferData_2[MICROHAL_SERIAL_PORT2_TX_BUFFER_SIZE];
static char rxBufferData_2[MICROHAL_SERIAL_PORT2_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial2(*USART2, rxBufferData_2, txBufferData_2, sizeof(rxBufferData_2), sizeof(txBufferData_2));
SerialPort &SerialPort::Serial2 = SerialPort_interrupt::Serial2;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT3_INTERRUPT
static char txBufferData_3[MICROHAL_SERIAL_PORT3_TX_BUFFER_SIZE];
static char rxBufferData_3[MICROHAL_SERIAL_PORT3_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial3(*USART3, rxBufferData_3, txBufferData_3, sizeof(rxBufferData_3), sizeof(txBufferData_3));
SerialPort &SerialPort::Serial3 = SerialPort_interrupt::Serial3;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT4_INTERRUPT
static char txBufferData_4[MICROHAL_SERIAL_PORT4_TX_BUFFER_SIZE];
static char rxBufferData_4[MICROHAL_SERIAL_PORT4_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial4(*UART4, rxBufferData_4, txBufferData_4, sizeof(rxBufferData_4), sizeof(txBufferData_4));
SerialPort &SerialPort::Serial4 = SerialPort_interrupt::Serial4;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT5_INTERRUPT
static char txBufferData_5[MICROHAL_SERIAL_PORT5_TX_BUFFER_SIZE];
static char rxBufferData_5[MICROHAL_SERIAL_PORT5_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial5(*UART5, rxBufferData_5, txBufferData_5, sizeof(rxBufferData_5), sizeof(txBufferData_5));
SerialPort &SerialPort::Serial5 = SerialPort_interrupt::Serial5;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT6_INTERRUPT
static char txBufferData_6[MICROHAL_SERIAL_PORT6_TX_BUFFER_SIZE];
static char rxBufferData_6[MICROHAL_SERIAL_PORT6_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial6(*USART6, rxBufferData_6, txBufferData_6, sizeof(rxBufferData_6), sizeof(txBufferData_6));
SerialPort &SerialPort::Serial6 = SerialPort_interrupt::Serial6;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT7_INTERRUPT
static char txBufferData_7[MICROHAL_SERIAL_PORT7_TX_BUFFER_SIZE];
static char rxBufferData_7[MICROHAL_SERIAL_PORT7_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial7(*UART7, rxBufferData_7, txBufferData_7, sizeof(rxBufferData_7), sizeof(txBufferData_7));
SerialPort &SerialPort::Serial7 = SerialPort_interrupt::Serial7;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT8_INTERRUPT
static char txBufferData_8[MICROHAL_SERIAL_PORT8_TX_BUFFER_SIZE];
static char rxBufferData_8[MICROHAL_SERIAL_PORT8_RX_BUFFER_SIZE];
SerialPort_interrupt SerialPort_interrupt::Serial8(*UART8, rxBufferData_8, txBufferData_8, sizeof(rxBufferData_8), sizeof(txBufferData_8));
SerialPort &SerialPort::Serial8 = SerialPort_interrupt::Serial8;
#endif

SerialPort_interrupt::SerialPort_interrupt(USART_TypeDef &usart, char *const rxData, char *const txData, size_t rxDataSize, size_t txDataSize)
    : SerialPort_BufferedBase(usart, rxData, rxDataSize, txData, txDataSize) {
#if defined(_MICROHAL_CLOCKMANAGER_HAS_POWERMODE) && _MICROHAL_CLOCKMANAGER_HAS_POWERMODE == 1
    ClockManager::enable(usart, ClockManager::PowerMode::Normal);
#else
    ClockManager::enable(usart);
#endif

#ifndef HAL_RTOS_FreeRTOS
    const uint32_t priority = 0;
#else
    const uint32_t priority = configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY;
#endif
    enableInterrupt(priority);
}

bool SerialPort_interrupt::open(OpenMode mode) noexcept {
    if (isOpen() || (mode > 0x03)) return false;
    usart.CR1 |= (mode << 2) | USART_CR1_UE | USART_CR1_RXNEIE;
    return true;
}

//***********************************************************************************************//
//                                     interrupt functions                                       //
//***********************************************************************************************//
#if defined(MCU_TYPE_STM32F3XX) || defined(MCU_TYPE_STM32F0XX)
void SerialPort_interrupt::__SerialPort_USART_interruptFunction() {
    uint32_t sr = usart.ISR;
    if (sr & USART_ISR_ORE) {
        usart.ICR = USART_ICR_ORECF;
    }
    if (sr & USART_ISR_RXNE) {
        char tmp = usart.RDR;
        rxBuffer.append(tmp);
        if (waitForBytes != 0 && rxBuffer.getLength() == waitForBytes) {
            waitForBytes = 0;
            bool shouldYeld = rxSemaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
            portYIELD_FROM_ISR(shouldYeld);
#else
            (void)shouldYeld;
#endif
        }
    }

    if ((sr & USART_ISR_TXE) && (usart.CR1 & USART_CR1_TXEIE)) {
        if (txBuffer.isEmpty()) {
            usart.CR1 &= ~USART_CR1_TXEIE;
            if (txWait) {
                usart.CR1 |= USART_CR1_TCIE;
            }
        } else {
            usart.TDR = txBuffer.get_unsafe();
        }
    } else if ((sr & USART_ISR_TC) && (usart.CR1 & USART_CR1_TCIE)) {
        usart.CR1 &= ~USART_CR1_TCIE;
        if (txWait) {
            txWait = false;
            auto shouldYeld = txFinish.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
            portYIELD_FROM_ISR(shouldYeld);
#else
            (void)shouldYeld;
#endif
        }
    }
}
#else
void SerialPort_interrupt::__SerialPort_USART_interruptFunction() {
    uint16_t sr = usart.SR;

    if (sr & USART_SR_RXNE) {
        char tmp = usart.DR;
        rxBuffer.append(tmp);
        if (waitForBytes != 0 && rxBuffer.getLength() == waitForBytes) {
            waitForBytes = 0;
            bool shouldYeld = rxSemaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
            portYIELD_FROM_ISR(shouldYeld);
#else
            (void)shouldYeld;
#endif
        }
    }
    if ((sr & USART_SR_TXE) && (usart.CR1 & USART_CR1_TXEIE)) {
        if (txBuffer.isEmpty()) {
            usart.CR1 &= ~USART_CR1_TXEIE;
            if (txWait) {
                usart.CR1 |= USART_CR1_TCIE;
                //    			auto shouldYeld = serial.txFinish.giveFromISR();
                //#if defined (HAL_RTOS_FreeRTOS)
                //    			portYIELD_FROM_ISR(shouldYeld);
                //#else
                //    			(void)shouldYeld;
                //#endif
            }
        } else {
            usart.DR = txBuffer.get_unsafe();
        }
    } else if ((sr & USART_SR_TC) && (usart.CR1 & USART_CR1_TCIE)) {
        usart.CR1 &= ~USART_CR1_TCIE;
        if (txWait) {
            txWait = false;
            auto shouldYeld = txFinish.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
            portYIELD_FROM_ISR(shouldYeld);
#else
            (void)shouldYeld;
#endif
        }
    }
}
#endif

//***********************************************************************************************//
//                                          IRQHandlers                                          //
//***********************************************************************************************//
#ifdef MICROHAL_USE_SERIAL_PORT1_INTERRUPT
void USART1_IRQHandler(void) {
    SerialPort_interrupt::Serial1.__SerialPort_USART_interruptFunction();
}
#endif
#ifdef MICROHAL_USE_SERIAL_PORT2_INTERRUPT
void USART2_IRQHandler(void) {
    SerialPort_interrupt::Serial2.__SerialPort_USART_interruptFunction();
}
#endif
#ifdef MICROHAL_USE_SERIAL_PORT3_INTERRUPT
void USART3_IRQHandler(void) {
    SerialPort_interrupt::Serial3.__SerialPort_USART_interruptFunction();
}
#endif
#ifdef MICROHAL_USE_SERIAL_PORT4_INTERRUPT
void UART4_IRQHandler(void) {
    SerialPort_interrupt::Serial4.__SerialPort_USART_interruptFunction();
}
#endif
#ifdef MICROHAL_USE_SERIAL_PORT5_INTERRUPT
void UART5_IRQHandler(void) {
    SerialPort_interrupt::Serial5.__SerialPort_USART_interruptFunction();
}
#endif
#ifdef MICROHAL_USE_SERIAL_PORT6_INTERRUPT
void USART6_IRQHandler(void) {
    SerialPort_interrupt::Serial6.__SerialPort_USART_interruptFunction();
}
#endif
#ifdef MICROHAL_USE_SERIAL_PORT7_INTERRUPT
void UART7_IRQHandler(void) {
    SerialPort_interrupt::Serial7.__SerialPort_USART_interruptFunction();
}
#endif
#ifdef MICROHAL_USE_SERIAL_PORT8_INTERRUPT
void UART8_IRQHandler(void) {
    SerialPort_interrupt::Serial8.__SerialPort_USART_interruptFunction();
}
#endif

}  // namespace _MICROHAL_ACTIVE_PORT_NAMESPACE
}  // namespace microhal
