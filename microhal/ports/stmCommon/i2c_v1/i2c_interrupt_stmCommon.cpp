/**
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief
 *
 * @authors    Pawel Okas
 * created on: 17-04-2014
 * last modification: 29-06-2016
 *
 * @copyright Copyright (c) 2014-2016, Pawel Okas
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

#include "i2c_interrupt_stmCommon.h"
/* ************************************************************************************************
 * 1.) Check if this driver should be used on selected MCU.
 * 2.) Check if this driver is enabled in microhal port configuration file
 */
#if _MICROHAL_PORT_STM_I2C_DRIVER_VERSION == 1  // Check if driver is compatible with selected MCU
#if ENABLED_ANY_I2C(INTERRUPT)                  // Check if driver is enabled in microhal port config

#include _MICROHAL_INCLUDE_PORT_CONFIG

namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {
/* ************************************************************************************************
 *                                   STATIC VARIABLES
 * ***********************************************************************************************/
#ifdef MICROHAL_USE_I2C1_INTERRUPT
I2C_interrupt I2C_interrupt::i2c1(registers::i2c1);
I2C &I2C::i2c1 = I2C_interrupt::i2c1;
#endif
#ifdef MICROHAL_USE_I2C2_INTERRUPT
I2C_interrupt I2C_interrupt::i2c2(registers::i2c2);
I2C &I2C::i2c2 = I2C_interrupt::i2c2;
#endif
#ifdef MICROHAL_USE_I2C3_INTERRUPT
I2C_interrupt I2C_interrupt::i2c3(registers::i2c3);
I2C &I2C::i2c3 = I2C_interrupt::i2c3;
#endif
/* ************************************************************************************************
 *                                            FUNCTIONS
 * ***********************************************************************************************/
I2C::Error I2C_interrupt::write(uint8_t deviceAddress, const uint8_t *data, size_t length) noexcept {
    transfer.deviceAddress = deviceAddress;
    transfer.bufferA.ptr = const_cast<uint8_t *>(data);
    transfer.bufferA.length = length;
    transfer.mode = Mode::Transmit;

    // send start
    while (i2c.sr2.volatileLoad().BUSY) {
    }
    auto cr2 = i2c.cr2.volatileLoad();
    cr2.ITBUFEN.set();
    i2c.cr2.volatileStore(cr2);
    auto cr1 = i2c.cr1.volatileLoad();
    cr1.START.set();
    i2c.cr1.volatileStore(cr1);

    error = Error::None;
    semaphore.wait(std::chrono::milliseconds::max());

    return error;
}
I2C::Error I2C_interrupt::write(DeviceAddress deviceAddress, const uint8_t *write_data, size_t write_data_size, const uint8_t *write_dataB,
                                size_t write_data_sizeB) noexcept {
    transfer.deviceAddress = deviceAddress;
    transfer.bufferA.ptr = const_cast<uint8_t *>(write_data);
    transfer.bufferA.length = write_data_size;
    transfer.bufferB.ptr = const_cast<uint8_t *>(write_dataB);
    transfer.bufferB.length = write_data_sizeB;
    transfer.mode = Mode::TransmitDoubleBuffer;

    // send start
    while (i2c.sr2.volatileLoad().BUSY) {
    }
    auto cr2 = i2c.cr2.volatileLoad();
    cr2.ITBUFEN.set();
    i2c.cr2.volatileStore(cr2);
    auto cr1 = i2c.cr1.volatileLoad();
    cr1.START.set();
    i2c.cr1.volatileStore(cr1);

    error = Error::None;
    semaphore.wait(std::chrono::milliseconds::max());

    return error;
}
I2C::Error I2C_interrupt::read(uint8_t deviceAddress, uint8_t *data, size_t length) noexcept {
    transfer.deviceAddress = deviceAddress;
    transfer.bufferA.ptr = data;
    transfer.bufferA.length = length;
    transfer.mode = Mode::Receive;

    auto cr2 = i2c.cr2.volatileLoad();
    cr2.ITBUFEN.clear();
    i2c.cr2.volatileStore(cr2);
    // send start
    while (i2c.sr2.volatileLoad().BUSY) {
    }
    auto cr1 = i2c.cr1.volatileLoad();
    cr1.START.set();
    i2c.cr1.volatileStore(cr1);

    error = Error::None;
    semaphore.wait(std::chrono::milliseconds::max());

    return error;
}

I2C::Error I2C_interrupt::read(uint8_t deviceAddress, uint8_t *data, size_t dataLength, uint8_t *dataB, size_t dataBLength) noexcept {
    transfer.deviceAddress = deviceAddress;
    transfer.bufferA.ptr = data;
    transfer.bufferA.length = dataLength;
    transfer.bufferB.ptr = dataB;
    transfer.bufferB.length = dataBLength;
    transfer.mode = Mode::ReceiveDoubleBuffer;

    auto cr2 = i2c.cr2.volatileLoad();
    cr2.ITBUFEN.clear();
    i2c.cr2.volatileStore(cr2);
    // send start
    while (i2c.sr2.volatileLoad().BUSY) {
    }
    auto cr1 = i2c.cr1.volatileLoad();
    cr1.START.set();
    i2c.cr1.volatileStore(cr1);

    error = Error::None;
    semaphore.wait(std::chrono::milliseconds::max());

    return error;
}

I2C::Error I2C_interrupt::writeRead(DeviceAddress address, const uint8_t *write, size_t write_size, uint8_t *read, size_t read_size) noexcept {
    transfer.deviceAddress = address;
    transfer.bufferA.ptr = const_cast<uint8_t *>(write);
    transfer.bufferA.length = write_size;
    transfer.bufferB.ptr = read;
    transfer.bufferB.length = read_size;
    transfer.mode = Mode::TransmitReceive;

    auto cr2 = i2c.cr2.volatileLoad();
    cr2.ITBUFEN.clear();
    i2c.cr2.volatileStore(cr2);
    while (i2c.sr2.volatileLoad().BUSY) {
    }
    // send start
    auto cr1 = i2c.cr1.volatileLoad();
    cr1.START.set();
    i2c.cr1.volatileStore(cr1);

    error = Error::None;
    semaphore.wait(std::chrono::milliseconds::max());

    return error;
}
//***********************************************************************************************//
//                                     interrupt functions //
//***********************************************************************************************//
void I2C_interrupt::IRQFunction(I2C_interrupt &obj, registers::I2C *i2c) {
    using Mode = I2C_interrupt::Mode;

    auto sr1 = i2c->sr1.volatileLoad();

    registers::I2C::SR1 sr1_txe;
    sr1_txe.TxE.set();

    if (sr1.SB && !sr1.TxE && !sr1.RxNE && !sr1.ADDR) {
        // start sequence was sent, now we need to send device address
        i2c->dr.volatileStore(obj.transfer.deviceAddress |
                              (static_cast<uint8_t>(obj.transfer.mode) & 0x01));  // set last bit of addres depending on active mode
    } else if (sr1.ADDR) {
        // address was sent, now we are working in master mode
        i2c->sr2.volatileLoad();  // to clear interrupt flag register SR2 read is necessarily

        uint32_t restart = 0;
        if (obj.transfer.mode == Mode::Transmit || obj.transfer.mode == Mode::TransmitReceive || obj.transfer.mode == Mode::TransmitDoubleBuffer) {
            i2c->dr.volatileStore(*obj.transfer.bufferA.ptr);
            obj.transfer.bufferA.ptr++;
            obj.transfer.bufferA.length--;

            if (obj.transfer.bufferA.length == 0 && obj.transfer.mode == Mode::TransmitReceive) {
                obj.transfer.bufferA = obj.transfer.bufferB;
                obj.transfer.mode = Mode::Receive;
                auto cr1 = i2c->cr1.volatileLoad();
                cr1.START.set();
                i2c->cr1.volatileStore(cr1);
                return;
            }
        }

        if (obj.transfer.mode == Mode::Receive || obj.transfer.mode == Mode::ReceiveDoubleBuffer) {
            auto toReceive =
                obj.transfer.mode == Mode::Receive ? obj.transfer.bufferA.length : obj.transfer.bufferA.length + obj.transfer.bufferB.length;

            auto cr1 = i2c->cr1.volatileLoad();
            auto cr2 = i2c->cr2.volatileLoad();
            if (toReceive == 1) {
                // i2c->CR2 &= ~I2C_CR2_ITBUFEN;
                cr2.ITBUFEN.set();
                cr1.ACK.clear();
                cr1.POS.clear();
                cr1 |= restart;
                // i2c->CR1 = (i2c->CR1 & (~I2C_CR1_ACK & ~I2C_CR1_POS)) | restart;
            } else if (toReceive == 2) {
                cr2.ITBUFEN.clear();
                cr1.ACK.clear();
                cr1.POS.set();
                cr1 |= restart;
                // i2c->CR2 &= ~I2C_CR2_ITBUFEN;
                // i2c->CR1 = (i2c->CR1 & ~I2C_CR1_ACK) | I2C_CR1_POS | restart;
            } else {
                cr2.ITBUFEN.set();
                cr1.ACK.set();
                cr1 |= restart;
                // i2c->CR2 |= I2C_CR2_ITBUFEN;
                // i2c->CR1 |= I2C_CR1_ACK /* | I2C_CR1_POS */ | restart;
            }
            i2c->cr2.volatileStore(cr2);
            i2c->cr1.volatileStore(cr1);
        } else {
            if (obj.transfer.mode != Mode::Receive || obj.transfer.bufferA.length >= 2) {
                auto cr2 = i2c->cr2.volatileLoad();
                cr2.ITBUFEN.set();
                i2c->cr2.volatileStore(cr2);
                // i2c->CR2 |= I2C_CR2_ITBUFEN;
            }
        }
    } else {
        registers::I2C::SR1 sr = {};
        sr.RxNE.set();
        sr.BTF.set();
        if (sr1 == sr) {
            // here we are receiving last two bytes
            auto cr1 = i2c->cr1.volatileLoad();
            cr1.STOP.set();
            // i2c->CR1 |= I2C_CR1_STOP;
            i2c->cr1.volatileStore(cr1);
            auto toReceive =
                obj.transfer.mode == Mode::Receive ? obj.transfer.bufferA.length : obj.transfer.bufferA.length + obj.transfer.bufferB.length;
            if (toReceive == 1) {
                *obj.transfer.bufferA.ptr = i2c->dr.volatileLoad().DATA;
            } else if (obj.transfer.mode == Mode::Receive) {
                *obj.transfer.bufferA.ptr++ = i2c->dr.volatileLoad().DATA;
                *obj.transfer.bufferA.ptr = i2c->dr.volatileLoad().DATA;
            } else {
                *obj.transfer.bufferA.ptr = i2c->dr.volatileLoad().DATA;
                *obj.transfer.bufferB.ptr = i2c->dr.volatileLoad().DATA;
            }
            auto shouldYeld = obj.semaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
            portYIELD_FROM_ISR(shouldYeld);
#else
            (void)shouldYeld;
#endif
        } else if (sr1.RxNE) {
            auto toReceive =
                obj.transfer.mode == Mode::Receive ? obj.transfer.bufferA.length : obj.transfer.bufferA.length + obj.transfer.bufferB.length;
            if (toReceive > 3) {
                *obj.transfer.bufferA.ptr = i2c->dr.volatileLoad().DATA;
                obj.transfer.bufferA.ptr++;
                obj.transfer.bufferA.length--;
                if (obj.transfer.bufferA.length == 0) {
                    // we have to be in double buffer mode
                    obj.transfer.bufferA = obj.transfer.bufferB;
                    obj.transfer.mode = Mode::Receive;
                }
            } else if (toReceive == 3) {
                *obj.transfer.bufferA.ptr = i2c->dr.volatileLoad().DATA;
                obj.transfer.bufferA.ptr++;
                obj.transfer.bufferA.length--;
                if (obj.transfer.bufferA.length == 0) {
                    // we have to be in double buffer mode
                    obj.transfer.bufferA = obj.transfer.bufferB;
                    obj.transfer.mode = Mode::Receive;
                }
                auto cr1 = i2c->cr1.volatileLoad();
                auto cr2 = i2c->cr2.volatileLoad();
                cr2.ITBUFEN.clear();
                cr1.ACK.clear();
                cr1.POS.set();
                // i2c->CR2 &= ~I2C_CR2_ITBUFEN;
                // i2c->CR1 = (i2c->CR1 & ~I2C_CR1_ACK) | I2C_CR1_POS;
                i2c->cr2.volatileStore(cr2);
                i2c->cr1.volatileStore(cr1);
            } else if (toReceive == 1) {
                auto cr1 = i2c->cr1.volatileLoad();
                cr1.STOP.set();
                // i2c->CR1 |= I2C_CR1_STOP;
                i2c->cr1.volatileStore(cr1);
                *obj.transfer.bufferA.ptr = i2c->dr.volatileLoad().DATA;
                auto shouldYeld = obj.semaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
                portYIELD_FROM_ISR(shouldYeld);
#else
                (void)shouldYeld;
#endif
            }
        } else if (sr1 == sr1_txe) {
            if (obj.transfer.bufferA.length) {
                // registers::I2C::DR dr;
                // dr = ;
                i2c->dr.volatileStore(*obj.transfer.bufferA.ptr++);
                obj.transfer.bufferA.length--;
            } else {
                if (obj.transfer.mode == Mode::TransmitDoubleBuffer) {
                    obj.transfer.bufferA = obj.transfer.bufferB;
                    obj.transfer.mode = Mode::Transmit;
                } else if (obj.transfer.mode == Mode::TransmitReceive) {
                    obj.transfer.bufferA = obj.transfer.bufferB;
                    obj.transfer.mode = Mode::Receive;

                    auto cr1 = i2c->cr1.volatileLoad();
                    auto cr2 = i2c->cr2.volatileLoad();
                    if (obj.transfer.bufferA.length == 1) {
                        cr2.ITBUFEN.clear();
                        cr1.ACK.clear();
                        cr1.POS.clear();
                        cr1.START.set();
                        // i2c->CR2 &= ~I2C_CR2_ITBUFEN;
                        // i2c->CR1 = (i2c->CR1 & (~I2C_CR1_ACK & ~I2C_CR1_POS)) | I2C_CR1_START;
                    } else if (obj.transfer.bufferA.length == 2) {
                        cr2.ITBUFEN.clear();
                        cr1.ACK.set();
                        cr1.POS.set();
                        cr1.START.set();
                        // i2c->CR2 &= ~I2C_CR2_ITBUFEN;
                        // i2c->CR1 = I2C_CR1_ACK | I2C_CR1_POS | I2C_CR1_START;
                    } else {
                        cr1.ACK.set();
                        cr1.START.set();
                        // i2c->CR1 |= I2C_CR1_ACK | I2C_CR1_START;
                    }
                    i2c->cr2.volatileStore(cr2);
                    i2c->cr1.volatileStore(cr1);
                } else {
                    auto cr1 = i2c->cr1.volatileLoad();
                    auto cr2 = i2c->cr2.volatileLoad();
                    cr1.STOP.set();
                    cr2.ITBUFEN.clear();
                    // i2c->CR1 |= I2C_CR1_STOP;
                    // i2c->CR2 &= ~I2C_CR2_ITBUFEN;
                    i2c->cr1.volatileStore(cr1);
                    i2c->cr2.volatileStore(cr2);
                    auto shouldYeld = obj.semaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
                    portYIELD_FROM_ISR(shouldYeld);
#else
                    (void)shouldYeld;
#endif
                }
            }
        }
    }
}
//***********************************************************************************************//
//                                          IRQHandlers //
//***********************************************************************************************//
#ifdef MICROHAL_USE_I2C1_INTERRUPT
void I2C1_EV_IRQHandler(void) {
    I2C_interrupt::IRQFunction(I2C_interrupt::i2c1, registers::i2c1);
}
#endif
#ifdef MICROHAL_USE_I2C2_INTERRUPT
extern "C" void I2C2_EV_IRQHandler(void) {
    I2C_interrupt::IRQFunction(I2C_interrupt::i2c2, registers::i2c2);
}
#endif
#ifdef MICROHAL_USE_I2C3_INTERRUPT
void I2C3_EV_IRQHandler(void) {
    I2C_interrupt::IRQFunction(I2C_interrupt::i2c3, registers::i2c3);
}
#endif
//***********************************************************************************************//
//                                         error IRQHandlers //
//***********************************************************************************************//
#ifdef MICROHAL_USE_I2C1_INTERRUPT
void I2C1_ER_IRQHandler(void) {
    auto cr1 = registers::i2c1->cr1.volatileLoad();
    cr1.STOP.set();
    registers::i2c1->cr1.volatileStore(cr1);
    I2C_interrupt::i2c1.error = I2C::errorCheckAndClear(registers::i2c1, registers::i2c1->sr1.volatileLoad());
    auto shouldYeld = I2C_interrupt::i2c1.semaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
    portYIELD_FROM_ISR(shouldYeld);
#else
    (void)shouldYeld;
#endif
}
#endif
#ifdef MICROHAL_USE_I2C2_INTERRUPT
extern "C" void I2C2_ER_IRQHandler(void) {
    auto cr1 = registers::i2c2->cr1.volatileLoad();
    cr1.STOP.set();
    registers::i2c2->cr1.volatileStore(cr1);
    I2C_interrupt::i2c2.error = I2C::errorCheckAndClear(registers::i2c2, registers::i2c2->sr1.volatileLoad());
    auto shouldYeld = I2C_interrupt::i2c2.semaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
    portYIELD_FROM_ISR(shouldYeld);
#else
    (void)shouldYeld;
#endif
}
#endif
#ifdef MICROHAL_USE_I2C3_INTERRUPT
void I2C3_ER_IRQHandler(void) {
    I2C3->CR1 |= I2C_CR1_STOP;
    I2C_interrupt::i2c3.error = I2C::errorCheckAndClear(registers::i2c2, registers::i2c3->sr1.volatileLoad());
    auto shouldYeld = I2C_interrupt::i2c3.semaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
    portYIELD_FROM_ISR(shouldYeld);
#else
    (void)shouldYeld;
#endif
}
#endif

}  // namespace _MICROHAL_ACTIVE_PORT_NAMESPACE
}  // namespace microhal
#endif
#endif
