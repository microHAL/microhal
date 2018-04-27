/**
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief
 *
 * @authors    buleks
 * created on: 25-08-2016
 * last modification: 25-08-2016
 *
 * @copyright Copyright (c) 2016, microHAL
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

#ifndef _MICROHAL_SERIALPORT_POLLING_STM32F3XX_H_
#define _MICROHAL_SERIALPORT_POLLING_STM32F3XX_H_
/* **************************************************************************************************************************************************
 * INCLUDES
 */

#include "../serialPort_stm32f3xx.h"
/* **************************************************************************************************************************************************
 * CLASS
 */

namespace microhal {
namespace stm32f3xx {

class SerialPort_polling : public stm32f3xx::SerialPort {
 public:
#ifdef MICROHAL_USE_SERIAL_PORT1_POLLING
    static SerialPort_polling Serial1;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT2_POLLING
    static SerialPort_polling Serial2;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT3_POLLING
    static SerialPort_polling Serial3;
#endif

 private:
    SerialPort_polling(USART_TypeDef &usart) : stm32f3xx::SerialPort(usart) {
        uint32_t rccEnableFlag;

        switch (reinterpret_cast<uint32_t>(&usart)) {
            case reinterpret_cast<uint32_t>(USART1_BASE):
                rccEnableFlag = RCC_APB2ENR_USART1EN;
                break;
            case reinterpret_cast<uint32_t>(USART2_BASE):
                rccEnableFlag = RCC_APB1ENR_USART2EN;
                break;
            case reinterpret_cast<uint32_t>(USART3_BASE):
                rccEnableFlag = RCC_APB1ENR_USART3EN;
                break;
        }
        if (reinterpret_cast<uint32_t>(&usart) == reinterpret_cast<uint32_t>(USART1)) {
            RCC->APB2ENR |= rccEnableFlag;
        } else {
            RCC->APB1ENR |= rccEnableFlag;
        }
    }

    bool open(OpenMode mode) noexcept {
        if (isOpen() || (mode > 0x03)) return false;
        usart.CR1 |= (mode << 2) | USART_CR1_UE;
        return true;
    }
    /**
     *
     * @param c
     * @return
     */
    bool putChar(char c) noexcept final {
        while (!(usart.ISR & USART_ISR_TXE)) {
        }
        usart.TDR = c;
        return true;
    }
    /**
     *
     * @return
     */
    bool getChar(char &c) noexcept final {
        while (!(usart.ISR & USART_ISR_RXNE)) {
        }
        c = usart.RDR;
        return true;
    }
    /**@brief This function write data to serial port buffer.
     *
     * @param[in] data - pointer to buffer where data are stored.
     * @param[in] maxSize - number of bytes to copy.
     * @return number of bytes that was copy to buffer.
     */
    size_t write(const char *data, size_t length) noexcept final {
        size_t writeByte = 0;

        for (; writeByte < length; writeByte++) {
            putChar(*data++);
        }

        return writeByte;
    }
    /**@brief This function copy read data from serial buffer to data pointer.
     *        If in buffer are less bytes than maxSize then function copy all bytes storage in buffer
     *        and return bytes count.
     *
     * @param[out] data - pointer to buffer where read data will be copy
     * @param[in] maxSize - size of data to copy.
     * @return number of bytes stored in data buffer.
     */
    size_t read(char *data, size_t length, std::chrono::milliseconds /*timeout*/) noexcept final {
        size_t tmp = length;
        while (length--) {
            getChar(*data++);
        }
        return tmp;
    }
    /**@brief This function clear buffer specified in dir parameter. If dir == Input function will
     *        flush rxBuffer, if dir == Output then txBuffer will be flushed.
     *        If dir == AllDirections both buffers will be cleared.
     *
     * @param[in] dir - buffer direction to be cleared
     * @retval true - if buffer was cleared successful
     * @retval false - if an error occurred
     */
    bool clear(Direction dir) noexcept final {
        (void)dir;
        return true;
    }
    /**
     *
     * @return
     */
    size_t inputQueueSize() const noexcept final { return 1; }
    /**
     *
     * @return
     */
    size_t outputQueueSize() const noexcept final { return 1; }

    size_t availableBytes() const noexcept final {
        if ((usart.ISR & USART_ISR_RXNE)) {
            return 1;
        }
        return 0;
    }

    bool waitForWriteFinish(std::chrono::milliseconds timeout) const noexcept final {
        (void)timeout;
        return true;
    }
};

}  // namespace stm32f3xx
}  // namespace microhal

#endif  // _MICROHAL_SERIALPORT_POLLING_STM32F3XX_H_
