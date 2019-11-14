/**
 * @license    BSD 3-Clause
 * @copyright  microHAL
 * @version    $Id$
 * @brief
 *
 * @authors    pawel
 * created on: 17-12-2016
 * last modification: 17-12-2016
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

#ifndef _MICROHAL_HARDWARE_STM_H_
#define _MICROHAL_HARDWARE_STM_H_
/* **************************************************************************************************************************************************
 * INCLUDES
 */
#ifdef MCU_TYPE_STM32F0XX
#include "ports/stm32f0xx/hardware_stm32f0xx.h"
#elif defined(MCU_TYPE_STM32F1XX)
#include "ports/stm32f1xx/hardware_stm32f1xx.h"
#elif defined(MCU_TYPE_STM32F4XX)
#include "ports/stm32f4xx/hardware_stm32f4xx.h"
namespace microhal {
// namespace activePort = stm32f4xx;
}
#elif defined(MCU_TYPE_STM32F3XX)
#include "ports/stm32f3xx/hardware_stm32f3xx.h"
namespace microhal {
// namespace activePort = stm32f4xx;
}
#else
#error "MCU type must be specified."
#endif

#endif  // _MICROHAL_HARDWARE_STM_H_
