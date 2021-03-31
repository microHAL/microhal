/**
 * @license    BSD 3-Clause
 * @version    $Id$
 * @brief
 *
 * @authors    Pawel Okas
 * created on: 27-03-2021
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

/* **************************************************************************************************************************************************
 * INCLUDES
 */
#include <stdint.h>

static void __Default_Handler(void) __attribute__((interrupt));
static void __Default_Handler(void) {
    __asm volatile("BKPT #01");
    while (1)
        ;
}

static void __Default_HardFault_Handler(void) {
    __asm volatile("BKPT #01");
    while (1)
        ;
}

static void Reserved_Handler(void) {
    __asm volatile("BKPT #01");
    while (1)
        ;
}

void NMI_Handler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void HardFault_Handler(void) __attribute__((interrupt, weak, alias("__Default_HardFault_Handler")));
void SVC_Handler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void PendSV_Handler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void SysTick_Handler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void WWDG_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void PVD_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void RTC_TAMP_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void RCC_CRS_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void EXTI0_1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void EXTI2_3_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void EXTI4_15_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void UCPD1_UCPD2_USB_Handler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void DMA1_Channel1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void DMA1_Channel2_3_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void ADC_COMP_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM3_4_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM6_DAC_LPTIM1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM7_LPTIM2_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM14_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM15_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM16_FDCAN_IT0_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void TIM17_FDCAN_IT1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void I2C1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void I2C2_3_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void SPI2_3_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void USART1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void USART2_LPUART2_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void USART3_4_5_6_LPUART1_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void CEC_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));
void AES_RNG_IRQHandler(void) __attribute__((interrupt, weak, alias("__Default_Handler")));

/*
+=============================================================================+
| Vector table
+=============================================================================+
*/

extern const char __main_stack_end;  // imported main stack end (from linker script)

void Reset_Handler(void);  // import the address of Reset_Handler()

void (*const vectors[])(void) __attribute__((section(".vectors"), used)) = {
    (void (*)(void)) & __main_stack_end,                          // Main stack end address
    Reset_Handler,                                                // Reset
    NMI_Handler,                                                  // Non-maskable interrupt (RCC clock security system)
    HardFault_Handler,                                            // All class of fault
    Reserved_Handler,                                             // Memory management
    Reserved_Handler,                                             // Pre-fetch fault, memory access fault
    Reserved_Handler,                                             // Undefined instruction or illegal state
    Reserved_Handler,                                             // Reserved
    Reserved_Handler,                                             // Reserved
    Reserved_Handler,                                             // Reserved
    Reserved_Handler,                                             // Reserved
    SVC_Handler,                                                  // 0x2C System service call via SWI instruction
    Reserved_Handler,                                             // 0x30 Debug monitor
    Reserved_Handler,                                             // 0x34 Reserved
    PendSV_Handler,                                               // 0x38 Pendable request for system service
    SysTick_Handler,                                              // 0x3C System tick timer
    WWDG_IRQHandler,                                              // Window WatchDog
    PVD_IRQHandler,                                               // PVD through EXTI Line detection (EXTI line 16)
    RTC_TAMP_IRQHandler,                                          // RTC and TAMP interrupts (combined EXTI lines 19 & 21) 0x48
    FLASH_IRQHandler,                                             // FLASH
    RCC_CRS_IRQHandler,                                           // RCC
    EXTI0_1_IRQHandler,                                           // EXTI Line0 & 1
    EXTI2_3_IRQHandler,                                           // EXTI Line2 & 3
    EXTI4_15_IRQHandler,                                          // EXTI Line4 to 15
    UCPD1_UCPD2_USB_Handler,                                      // UCPD and USB global interrupt (combined with EXTI lines 32 & 33
    DMA1_Channel1_IRQHandler,                                     // DMA1 Channel 1
    DMA1_Channel2_3_IRQHandler,                                   // DMA1 Channel 2 & 3
    DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5_IRQHandler,  // DMA1 channel 4, 5, 6, 7, DMAMUX, DMA2 channel 1, 2, 3, 4, 5 interrupts
    ADC_COMP_IRQHandler,                                          // ADC and COMP interrupts (ADC combined with EXTI 17 & 18)
    TIM1_BRK_UP_TRG_COM_IRQHandler,                               // TIM1 break, update, trigger and commutation interrupts
    TIM1_CC_IRQHandler,                                           // TIM1 Capture Compare
    TIM2_IRQHandler,                                              // TIM2 global interrupt
    TIM3_4_IRQHandler,                                            // TIM3 & TIM4
    TIM6_DAC_LPTIM1_IRQHandler,                                   // TIM6, LPTIM1 and DAC global interrupt
    TIM7_LPTIM2_IRQHandler,                                       // TIM7
    TIM14_IRQHandler,                                             // TIM14
    TIM15_IRQHandler,                                             // TIM15
    TIM16_FDCAN_IT0_IRQHandler,                                   // TIM16 and FDCAN_IT0 global interrupt
    TIM17_FDCAN_IT1_IRQHandler,                                   // TIM17 and FDCAN_IT1 global interrupt
    I2C1_IRQHandler,                                              // I2C1 Event
    I2C2_3_IRQHandler,                                            // I2C2 & I2C3 Event
    SPI1_IRQHandler,                                              // SPI1
    SPI2_3_IRQHandler,                                            // SPI2 & SPI3
    USART1_IRQHandler,                                            // USART1
    USART2_LPUART2_IRQHandler,                                    // USART2 and LPUART2 global interrupt (combined with EXTI 26)
    USART3_4_5_6_LPUART1_IRQHandler,                              // USART3/4/5/6 and LPUART1 global interrupt (combined with EXTI 28)
    CEC_IRQHandler,                                               // CEC global interrupt (combined with EXTI 27)
    AES_RNG_IRQHandler                                            // AES and RNG global interrupts
};