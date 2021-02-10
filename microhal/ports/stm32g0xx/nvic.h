/*
 * nvic.h
 *
 *  Created on: Feb 4, 2021
 *      Author: pokas
 */

#ifndef SRC_MICROHAL_PORTS_STM32G0XX_NVIC_H_
#define SRC_MICROHAL_PORTS_STM32G0XX_NVIC_H_

#define __CM0PLUS_REV 0U          /*!< Core Revision r0p0                            */
#define __MPU_PRESENT 1U          /*!< STM32G0xx  provides an MPU                    */
#define __VTOR_PRESENT 1U         /*!< Vector  Table  Register supported             */
#define __NVIC_PRIO_BITS 2U       /*!< STM32G0xx uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig 0U /*!< Set to 1 if different SysTick Config is used  */

typedef enum {
    /******  Cortex-M0+ Processor Exceptions Numbers ***************************************************************/
    NonMaskableInt_IRQn = -14, /*!< 2 Non Maskable Interrupt                                          */
    HardFault_IRQn = -13,      /*!< 3 Cortex-M Hard Fault Interrupt                                   */
    SVC_IRQn = -5,             /*!< 11 Cortex-M SV Call Interrupt                                     */
    PendSV_IRQn = -2,          /*!< 14 Cortex-M Pend SV Interrupt                                     */
    SysTick_IRQn = -1,         /*!< 15 Cortex-M System Tick Interrupt                                 */
                               /******  STM32G0xxxx specific Interrupt Numbers ****************************************************************/
    WWDG_IRQn = 0,             /*!< Window WatchDog Interrupt                                         */
    PVD_IRQn = 1,              /*!< PVD through EXTI line 16                                          */
    RTC_TAMP_IRQn = 2,         /*!< RTC interrupt through the EXTI line 19 & 21                       */
    FLASH_IRQn = 3,            /*!< FLASH global Interrupt                                            */
    RCC_IRQn = 4,              /*!< RCC global Interrupt                                              */
    EXTI0_1_IRQn = 5,          /*!< EXTI 0 and 1 Interrupts                                           */
    EXTI2_3_IRQn = 6,          /*!< EXTI Line 2 and 3 Interrupts                                      */
    EXTI4_15_IRQn = 7,         /*!< EXTI Line 4 to 15 Interrupts                                      */
    UCPD1_2_IRQn = 8,          /*!< UCPD1 and UCPD2 global Interrupt                                  */
    DMA1_Channel1_IRQn = 9,    /*!< DMA1 Channel 1 Interrupt                                          */
    DMA1_Channel2_3_IRQn = 10, /*!< DMA1 Channel 2 and Channel 3 Interrupts                           */
    DMA1_Ch4_7_DMAMUX1_OVR_IRQn = 11, /*!< DMA1 Channel 4 to Channel 7 and DMAMUX1 Overrun Interrupts        */
    ADC1_COMP_IRQn = 12,              /*!< ADC1, COMP1 and COMP2 Interrupts (combined with EXTI 17 & 18)     */
    TIM1_BRK_UP_TRG_COM_IRQn = 13,    /*!< TIM1 Break, Update, Trigger and Commutation Interrupts            */
    TIM1_CC_IRQn = 14,                /*!< TIM1 Capture Compare Interrupt                                    */
    TIM2_IRQn = 15,                   /*!< TIM2 Interrupt                                                    */
    TIM3_IRQn = 16,                   /*!< TIM3 global Interrupt                                             */
    TIM6_DAC_LPTIM1_IRQn = 17,        /*!< TIM6, DAC and LPTIM1 global Interrupts                            */
    TIM7_LPTIM2_IRQn = 18,            /*!< TIM7 and LPTIM2 global Interrupt                                  */
    TIM14_IRQn = 19,                  /*!< TIM14 global Interrupt                                            */
    TIM15_IRQn = 20,                  /*!< TIM15 global Interrupt                                            */
    TIM16_IRQn = 21,                  /*!< TIM16 global Interrupt                                            */
    TIM17_IRQn = 22,                  /*!< TIM17 global Interrupt                                            */
    I2C1_IRQn = 23,                   /*!< I2C1 Interrupt  (combined with EXTI 23)                           */
    I2C2_IRQn = 24,                   /*!< I2C2 Interrupt                                                    */
    SPI1_IRQn = 25,                   /*!< SPI1/I2S1 Interrupt                                               */
    SPI2_IRQn = 26,                   /*!< SPI2 Interrupt                                                    */
    USART1_IRQn = 27,                 /*!< USART1 Interrupt                                                  */
    USART2_IRQn = 28,                 /*!< USART2 Interrupt                                                  */
    USART3_4_LPUART1_IRQn = 29,       /*!< USART3, USART4 and LPUART1 globlal Interrupts (combined with EXTI 28) */
    CEC_IRQn = 30,                    /*!< CEC Interrupt(combined with EXTI 27)                               */
} IRQn_Type;

#define USART3_IRQn USART3_4_LPUART1_IRQn
#define ADC1_2_IRQn ADC1_COMP_IRQn

#include <core_cm0plus.h>

#endif /* SRC_MICROHAL_PORTS_STM32G0XX_NVIC_H_ */