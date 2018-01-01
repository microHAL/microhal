/* ========================================================================================================================== */ /**
 @license    BSD 3-Clause
 @copyright  microHAL
 @version    $Id$
 @brief      board support package for stm32f4Discovery board

 @authors    Pawel Okas
 created on: 16-04-2014
 last modification: <DD-MM-YYYY>

 @copyright Copyright (c) 2014, microHAL
 All rights reserved.
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
 conditions are met:
 	 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 	 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
 	 	in the documentation and/or other materials provided with the distribution.
 	 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived
 	 	from this software without specific prior written permission.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */ /* ==========================================================================================================================
                                                                                                                                        */

#ifndef MICROHALPORTCONFIG_H_
#define MICROHALPORTCONFIG_H_

#include <cstdint>
//***********************************************************************************************//
//                                     Hardware Configuration                                    //
//***********************************************************************************************//
static constexpr bool externalClockPresent = true;
static constexpr uint32_t externalClockFrequency = 8000000;  // this is HSE frequency
static constexpr bool externalLSEPresent = false;
static constexpr uint32_t externalLSEFrequency = 32768;
//***********************************************************************************************//
//                                       configure interfaces                                    //
//***********************************************************************************************//
//***********************************************************************************************//
//                                    Serial Port configurations                                 //
//***********************************************************************************************//
#define MICROHAL_USE_SERIAL_PORT1_POLLING  // available settings are MICROHAL_USE_SERIAL_PORTx_POLLING
//						 MICROHAL_USE_SERIAL_PORTx_INTERRUPT
//						 MICROHAL_USE_SERIAL_PORTx_DMA
#define MICROHAL_SERIAL_PORT1_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT1_RX_BUFFER_SIZE 128

#define MICROHAL_USE_SERIAL_PORT2_POLLING
#define MICROHAL_SERIAL_PORT2_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT2_RX_BUFFER_SIZE 128

#if !defined(STM32F401xC) && !defined(STM32F401xE) && !defined(STM32F411xE) && !defined(STM32F412Cx) && !defined(STM32F410Cx) && \
    !defined(STM32F410Rx) && !defined(STM32F410Tx)
#define MICROHAL_USE_SERIAL_PORT3_POLLING
#define MICROHAL_SERIAL_PORT3_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT3_RX_BUFFER_SIZE 128
#endif

#if !defined(STM32F401xC) && !defined(STM32F401xE) && !defined(STM32F411xE) && !defined(STM32F412Cx) && !defined(STM32F412Zx) && \
    !defined(STM32F412Vx) && !defined(STM32F412Rx) && !defined(STM32F410Cx) && !defined(STM32F410Rx) && !defined(STM32F410Tx)
#define MICROHAL_USE_SERIAL_PORT4_POLLING
#define MICROHAL_SERIAL_PORT4_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT4_RX_BUFFER_SIZE 128
#endif

#if !defined(STM32F401xC) && !defined(STM32F401xE) && !defined(STM32F411xE) && !defined(STM32F412Cx) && !defined(STM32F412Zx) && \
    !defined(STM32F412Vx) && !defined(STM32F412Rx) && !defined(STM32F410Cx) && !defined(STM32F410Rx) && !defined(STM32F410Tx)
#define MICROHAL_USE_SERIAL_PORT5_POLLING
#define MICROHAL_SERIAL_PORT5_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT5_RX_BUFFER_SIZE 128
#endif

#define MICROHAL_USE_SERIAL_PORT6_POLLING
#define MICROHAL_SERIAL_PORT6_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT6_RX_BUFFER_SIZE 128

#define MICROHAL_USE_SERIAL_PORT7_POLLING
#define MICROHAL_SERIAL_PORT7_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT7_RX_BUFFER_SIZE 128

#define MICROHAL_USE_SERIAL_PORT8_POLLING
#define MICROHAL_SERIAL_PORT8_TX_BUFFER_SIZE 1024
#define MICROHAL_SERIAL_PORT8_RX_BUFFER_SIZE 128

#endif /* MICROHALPORTCONFIG_H_ */