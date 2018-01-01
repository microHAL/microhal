/**
 * @file
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief      board support package for nucleo-f411re board
 *
 * @authors    Pawel Okas
 * created on: 18-11-2016
 * last modification: <DD-MM-YYYY>
 *
 * @copyright Copyright (c) 2016, Paweł Okas
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

#ifndef NUCLEO_F411RE_H_
#define NUCLEO_F411RE_H_

namespace bsp {
static microhal::SerialPort &debugPort = microhal::stm32f4xx::SerialPort::Serial2;

namespace moduleA {
static microhal::SPI &spi = microhal::stm32f4xx::SPI::spi1;
constexpr microhal::GPIO::IOPin csDat(microhal::stm32f4xx::GPIO::Port::PortD, 8);
constexpr microhal::GPIO::IOPin csCon(microhal::stm32f4xx::GPIO::Port::PortD, 1);
constexpr microhal::GPIO::IOPin IRQ0(microhal::stm32f4xx::GPIO::Port::PortD, 3);
constexpr microhal::GPIO::IOPin IRQ1(microhal::stm32f4xx::GPIO::Port::PortD, 10);
constexpr microhal::GPIO::IOPin RESET(microhal::stm32f4xx::GPIO::Port::PortD, 0);
}
namespace moduleB {
static microhal::SPI &spi = microhal::stm32f4xx::SPI::spi2;
constexpr microhal::GPIO::IOPin csDat(microhal::stm32f4xx::GPIO::Port::PortB, 8);
constexpr microhal::GPIO::IOPin csCon(microhal::stm32f4xx::GPIO::Port::PortA, 3);
constexpr microhal::GPIO::IOPin IRQ0(microhal::stm32f4xx::GPIO::Port::PortA, 2);
constexpr microhal::GPIO::IOPin IRQ1(microhal::stm32f4xx::GPIO::Port::PortE, 4);
constexpr microhal::GPIO::IOPin RESET(microhal::stm32f4xx::GPIO::Port::PortA, 1);
}
}
#endif  // NUCLEO_F411RE_H_