#ifndef _MICROHAL_PERIPHERAL_REGISTER_RCC
#define _MICROHAL_PERIPHERAL_REGISTER_RCC

#include "ports/stmCommon/registers/registersBaseAddressDefinitions.h"
#include "utils/bitfield.h"
#include "utils/volatileRegister.h"

#undef RCC
#define _MICROHAL_CLOCKMANAGER_HAS_POWERMODE 1
#define _MICROHAL_REGISTERS_RCC_HAS_PLLCFGR
#define _MICROHAL_REGISTERS_RCC_CFGR_HAS_PPRE2

// Supported MCU: STM32F407, STM32F405
namespace microhal {
namespace registers {
/**
 *
 */
struct RCC {
    // clock control register
    union CR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> HSION;      /*!< Internal high-speed clock enable */
            microhal::Bitfield<uint32_t, 1, 1> HSIRDY;     /*!< Internal high-speed clock ready flag */
            microhal::Bitfield<uint32_t, 3, 5> HSITRIM;    /*!< Internal high-speed clock trimming */
            microhal::Bitfield<uint32_t, 8, 8> HSICAL;     /*!< Internal high-speed clock calibration */
            microhal::Bitfield<uint32_t, 16, 1> HSEON;     /*!< HSE clock enable */
            microhal::Bitfield<uint32_t, 17, 1> HSERDY;    /*!< HSE clock ready flag */
            microhal::Bitfield<uint32_t, 18, 1> HSEBYP;    /*!< HSE clock bypass */
            microhal::Bitfield<uint32_t, 19, 1> CSSON;     /*!< Clock security system enable */
            microhal::Bitfield<uint32_t, 24, 1> PLLON;     /*!< Main PLL (PLL) enable */
            microhal::Bitfield<uint32_t, 25, 1> PLLRDY;    /*!< Main PLL (PLL) clock ready flag */
            microhal::Bitfield<uint32_t, 26, 1> PLLI2SON;  /*!< PLLI2S enable */
            microhal::Bitfield<uint32_t, 27, 1> PLLI2SRDY; /*!< PLLI2S clock ready flag */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        CR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        CR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        CR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        CR operator&(uint32_t value) const {
            CR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        CR operator|(uint32_t value) const {
            CR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<CR, AccessType::ReadOnly>;
        friend class VolatileRegister<CR, AccessType::WriteOnly>;
        friend class VolatileRegister<CR, AccessType::ReadWrite>;
    };

    // PLL configuration register
    union PLLCFGR {
        union {
            microhal::Bitfield<uint32_t, 0, 6> PLLM;    /*!< Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock */
            microhal::Bitfield<uint32_t, 6, 9> PLLN;    /*!< Main PLL (PLL) multiplication factor for VCO */
            microhal::Bitfield<uint32_t, 16, 2> PLLP;   /*!< Main PLL (PLL) division factor for main system clock */
            microhal::Bitfield<uint32_t, 22, 1> PLLSRC; /*!< Main PLL(PLL) and audio PLL (PLLI2S) entry clock source */
            microhal::Bitfield<uint32_t, 24, 4> PLLQ;   /*!< Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        PLLCFGR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        PLLCFGR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        PLLCFGR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        PLLCFGR operator&(uint32_t value) const {
            PLLCFGR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        PLLCFGR operator|(uint32_t value) const {
            PLLCFGR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<PLLCFGR, AccessType::ReadOnly>;
        friend class VolatileRegister<PLLCFGR, AccessType::WriteOnly>;
        friend class VolatileRegister<PLLCFGR, AccessType::ReadWrite>;
    };

    // clock configuration register
    union CFGR {
        union {
            microhal::Bitfield<uint32_t, 0, 2> SW;       /*!< System clock switch */
            microhal::Bitfield<uint32_t, 2, 2> SWS;      /*!< System clock switch status */
            microhal::Bitfield<uint32_t, 4, 4> HPRE;     /*!< AHB prescaler */
            microhal::Bitfield<uint32_t, 10, 3> PPRE1;   /*!< APB Low speed prescaler (APB1) */
            microhal::Bitfield<uint32_t, 13, 3> PPRE2;   /*!< APB high-speed prescaler (APB2) */
            microhal::Bitfield<uint32_t, 16, 5> RTCPRE;  /*!< HSE division factor for RTC clock */
            microhal::Bitfield<uint32_t, 21, 2> MCO1;    /*!< Microcontroller clock output 1 */
            microhal::Bitfield<uint32_t, 23, 1> I2SSRC;  /*!< I2S clock selection */
            microhal::Bitfield<uint32_t, 24, 3> MCO1PRE; /*!< MCO1 prescaler */
            microhal::Bitfield<uint32_t, 27, 3> MCO2PRE; /*!< MCO2 prescaler */
            microhal::Bitfield<uint32_t, 30, 2> MCO2;    /*!< Microcontroller clock output 2 */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        CFGR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        CFGR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        CFGR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        CFGR operator&(uint32_t value) const {
            CFGR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        CFGR operator|(uint32_t value) const {
            CFGR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<CFGR, AccessType::ReadOnly>;
        friend class VolatileRegister<CFGR, AccessType::WriteOnly>;
        friend class VolatileRegister<CFGR, AccessType::ReadWrite>;
    };

    // clock interrupt register
    union CIR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> LSIRDYF;      /*!< LSI ready interrupt flag */
            microhal::Bitfield<uint32_t, 1, 1> LSERDYF;      /*!< LSE ready interrupt flag */
            microhal::Bitfield<uint32_t, 2, 1> HSIRDYF;      /*!< HSI ready interrupt flag */
            microhal::Bitfield<uint32_t, 3, 1> HSERDYF;      /*!< HSE ready interrupt flag */
            microhal::Bitfield<uint32_t, 4, 1> PLLRDYF;      /*!< Main PLL (PLL) ready interrupt flag */
            microhal::Bitfield<uint32_t, 5, 1> PLLI2SRDYF;   /*!< PLLI2S ready interrupt flag */
            microhal::Bitfield<uint32_t, 7, 1> CSSF;         /*!< Clock security system interrupt flag */
            microhal::Bitfield<uint32_t, 8, 1> LSIRDYIE;     /*!< LSI ready interrupt enable */
            microhal::Bitfield<uint32_t, 9, 1> LSERDYIE;     /*!< LSE ready interrupt enable */
            microhal::Bitfield<uint32_t, 10, 1> HSIRDYIE;    /*!< HSI ready interrupt enable */
            microhal::Bitfield<uint32_t, 11, 1> HSERDYIE;    /*!< HSE ready interrupt enable */
            microhal::Bitfield<uint32_t, 12, 1> PLLRDYIE;    /*!< Main PLL (PLL) ready interrupt enable */
            microhal::Bitfield<uint32_t, 13, 1> PLLI2SRDYIE; /*!< PLLI2S ready interrupt enable */
            microhal::Bitfield<uint32_t, 16, 1> LSIRDYC;     /*!< LSI ready interrupt clear */
            microhal::Bitfield<uint32_t, 17, 1> LSERDYC;     /*!< LSE ready interrupt clear */
            microhal::Bitfield<uint32_t, 18, 1> HSIRDYC;     /*!< HSI ready interrupt clear */
            microhal::Bitfield<uint32_t, 19, 1> HSERDYC;     /*!< HSE ready interrupt clear */
            microhal::Bitfield<uint32_t, 20, 1> PLLRDYC;     /*!< Main PLL(PLL) ready interrupt clear */
            microhal::Bitfield<uint32_t, 21, 1> PLLI2SRDYC;  /*!< PLLI2S ready interrupt clear */
            microhal::Bitfield<uint32_t, 23, 1> CSSC;        /*!< Clock security system interrupt clear */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        CIR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        CIR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        CIR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        CIR operator&(uint32_t value) const {
            CIR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        CIR operator|(uint32_t value) const {
            CIR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<CIR, AccessType::ReadOnly>;
        friend class VolatileRegister<CIR, AccessType::WriteOnly>;
        friend class VolatileRegister<CIR, AccessType::ReadWrite>;
    };

    // AHB1 peripheral reset register
    union AHB1RSTR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> GPIOARST;   /*!< IO port A reset */
            microhal::Bitfield<uint32_t, 1, 1> GPIOBRST;   /*!< IO port B reset */
            microhal::Bitfield<uint32_t, 2, 1> GPIOCRST;   /*!< IO port C reset */
            microhal::Bitfield<uint32_t, 3, 1> GPIODRST;   /*!< IO port D reset */
            microhal::Bitfield<uint32_t, 4, 1> GPIOERST;   /*!< IO port E reset */
            microhal::Bitfield<uint32_t, 5, 1> GPIOFRST;   /*!< IO port F reset */
            microhal::Bitfield<uint32_t, 6, 1> GPIOGRST;   /*!< IO port G reset */
            microhal::Bitfield<uint32_t, 7, 1> GPIOHRST;   /*!< IO port H reset */
            microhal::Bitfield<uint32_t, 8, 1> GPIOIRST;   /*!< IO port I reset */
            microhal::Bitfield<uint32_t, 9, 1> GPIOJRST;   /*!< IO port J reset */
            microhal::Bitfield<uint32_t, 10, 1> GPIOKRST;  /*!< IO port K reset */
            microhal::Bitfield<uint32_t, 12, 1> CRCRST;    /*!< CRC reset */
            microhal::Bitfield<uint32_t, 21, 1> DMA1RST;   /*!< DMA2 reset */
            microhal::Bitfield<uint32_t, 22, 1> DMA2RST;   /*!< DMA2 reset */
            microhal::Bitfield<uint32_t, 25, 1> ETHMACRST; /*!< Ethernet MAC reset */
            microhal::Bitfield<uint32_t, 29, 1> OTGHSRST;  /*!< USB OTG HS module reset */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB1RSTR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB1RSTR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB1RSTR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB1RSTR operator&(uint32_t value) const {
            AHB1RSTR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB1RSTR operator|(uint32_t value) const {
            AHB1RSTR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB1RSTR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB1RSTR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB1RSTR, AccessType::ReadWrite>;
    };

    // AHB2 peripheral reset register
    union AHB2RSTR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> DCMIRST;  /*!< Camera interface reset */
            microhal::Bitfield<uint32_t, 6, 1> RNGRST;   /*!< Random number generator module reset */
            microhal::Bitfield<uint32_t, 7, 1> OTGFSRST; /*!< USB OTG FS module reset */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB2RSTR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB2RSTR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB2RSTR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB2RSTR operator&(uint32_t value) const {
            AHB2RSTR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB2RSTR operator|(uint32_t value) const {
            AHB2RSTR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB2RSTR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB2RSTR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB2RSTR, AccessType::ReadWrite>;
    };

    // AHB3 peripheral reset register
    union AHB3RSTR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> FSMCRST; /*!< Flexible static memory controller module reset */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB3RSTR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB3RSTR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB3RSTR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB3RSTR operator&(uint32_t value) const {
            AHB3RSTR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB3RSTR operator|(uint32_t value) const {
            AHB3RSTR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB3RSTR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB3RSTR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB3RSTR, AccessType::ReadWrite>;
    };

    // APB1 peripheral reset register
    union APB1RSTR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> TIM2RST;   /*!< TIM2 reset */
            microhal::Bitfield<uint32_t, 1, 1> TIM3RST;   /*!< TIM3 reset */
            microhal::Bitfield<uint32_t, 2, 1> TIM4RST;   /*!< TIM4 reset */
            microhal::Bitfield<uint32_t, 3, 1> TIM5RST;   /*!< TIM5 reset */
            microhal::Bitfield<uint32_t, 4, 1> TIM6RST;   /*!< TIM6 reset */
            microhal::Bitfield<uint32_t, 5, 1> TIM7RST;   /*!< TIM7 reset */
            microhal::Bitfield<uint32_t, 6, 1> TIM12RST;  /*!< TIM12 reset */
            microhal::Bitfield<uint32_t, 7, 1> TIM13RST;  /*!< TIM13 reset */
            microhal::Bitfield<uint32_t, 8, 1> TIM14RST;  /*!< TIM14 reset */
            microhal::Bitfield<uint32_t, 11, 1> WWDGRST;  /*!< Window watchdog reset */
            microhal::Bitfield<uint32_t, 14, 1> SPI2RST;  /*!< SPI 2 reset */
            microhal::Bitfield<uint32_t, 15, 1> SPI3RST;  /*!< SPI 3 reset */
            microhal::Bitfield<uint32_t, 17, 1> UART2RST; /*!< USART 2 reset */
            microhal::Bitfield<uint32_t, 18, 1> UART3RST; /*!< USART 3 reset */
            microhal::Bitfield<uint32_t, 19, 1> UART4RST; /*!< USART 4 reset */
            microhal::Bitfield<uint32_t, 20, 1> UART5RST; /*!< USART 5 reset */
            microhal::Bitfield<uint32_t, 21, 1> I2C1RST;  /*!< I2C 1 reset */
            microhal::Bitfield<uint32_t, 22, 1> I2C2RST;  /*!< I2C 2 reset */
            microhal::Bitfield<uint32_t, 23, 1> I2C3RST;  /*!< I2C3 reset */
            microhal::Bitfield<uint32_t, 25, 1> CAN1RST;  /*!< CAN1 reset */
            microhal::Bitfield<uint32_t, 26, 1> CAN2RST;  /*!< CAN2 reset */
            microhal::Bitfield<uint32_t, 28, 1> PWRRST;   /*!< Power interface reset */
            microhal::Bitfield<uint32_t, 29, 1> DACRST;   /*!< DAC reset */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        APB1RSTR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        APB1RSTR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        APB1RSTR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        APB1RSTR operator&(uint32_t value) const {
            APB1RSTR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        APB1RSTR operator|(uint32_t value) const {
            APB1RSTR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<APB1RSTR, AccessType::ReadOnly>;
        friend class VolatileRegister<APB1RSTR, AccessType::WriteOnly>;
        friend class VolatileRegister<APB1RSTR, AccessType::ReadWrite>;
    };

    // APB2 peripheral reset register
    union APB2RSTR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> TIM1RST;    /*!< TIM1 reset */
            microhal::Bitfield<uint32_t, 1, 1> TIM8RST;    /*!< TIM8 reset */
            microhal::Bitfield<uint32_t, 4, 1> USART1RST;  /*!< USART1 reset */
            microhal::Bitfield<uint32_t, 5, 1> USART6RST;  /*!< USART6 reset */
            microhal::Bitfield<uint32_t, 8, 1> ADCRST;     /*!< ADC interface reset (common to all ADCs) */
            microhal::Bitfield<uint32_t, 11, 1> SDIORST;   /*!< SDIO reset */
            microhal::Bitfield<uint32_t, 12, 1> SPI1RST;   /*!< SPI 1 reset */
            microhal::Bitfield<uint32_t, 14, 1> SYSCFGRST; /*!< System configuration controller reset */
            microhal::Bitfield<uint32_t, 16, 1> TIM9RST;   /*!< TIM9 reset */
            microhal::Bitfield<uint32_t, 17, 1> TIM10RST;  /*!< TIM10 reset */
            microhal::Bitfield<uint32_t, 18, 1> TIM11RST;  /*!< TIM11 reset */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        APB2RSTR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        APB2RSTR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        APB2RSTR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        APB2RSTR operator&(uint32_t value) const {
            APB2RSTR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        APB2RSTR operator|(uint32_t value) const {
            APB2RSTR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<APB2RSTR, AccessType::ReadOnly>;
        friend class VolatileRegister<APB2RSTR, AccessType::WriteOnly>;
        friend class VolatileRegister<APB2RSTR, AccessType::ReadWrite>;
    };

    // AHB1 peripheral clock register
    union AHB1ENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> GPIOAEN;      /*!< IO port A clock enable */
            microhal::Bitfield<uint32_t, 1, 1> GPIOBEN;      /*!< IO port B clock enable */
            microhal::Bitfield<uint32_t, 2, 1> GPIOCEN;      /*!< IO port C clock enable */
            microhal::Bitfield<uint32_t, 3, 1> GPIODEN;      /*!< IO port D clock enable */
            microhal::Bitfield<uint32_t, 4, 1> GPIOEEN;      /*!< IO port E clock enable */
            microhal::Bitfield<uint32_t, 5, 1> GPIOFEN;      /*!< IO port F clock enable */
            microhal::Bitfield<uint32_t, 6, 1> GPIOGEN;      /*!< IO port G clock enable */
            microhal::Bitfield<uint32_t, 7, 1> GPIOHEN;      /*!< IO port H clock enable */
            microhal::Bitfield<uint32_t, 8, 1> GPIOIEN;      /*!< IO port I clock enable */
            microhal::Bitfield<uint32_t, 9, 1> GPIOJEN;      /*!< IO port J clock enable */
            microhal::Bitfield<uint32_t, 10, 1> GPIOKEN;     /*!< IO port K clock enable */
            microhal::Bitfield<uint32_t, 12, 1> CRCEN;       /*!< CRC clock enable */
            microhal::Bitfield<uint32_t, 18, 1> BKPSRAMEN;   /*!< Backup SRAM interface clock enable */
            microhal::Bitfield<uint32_t, 21, 1> DMA1EN;      /*!< DMA1 clock enable */
            microhal::Bitfield<uint32_t, 22, 1> DMA2EN;      /*!< DMA2 clock enable */
            microhal::Bitfield<uint32_t, 25, 1> ETHMACEN;    /*!< Ethernet MAC clock enable */
            microhal::Bitfield<uint32_t, 26, 1> ETHMACTXEN;  /*!< Ethernet Transmission clock enable */
            microhal::Bitfield<uint32_t, 27, 1> ETHMACRXEN;  /*!< Ethernet Reception clock enable */
            microhal::Bitfield<uint32_t, 28, 1> ETHMACPTPEN; /*!< Ethernet PTP clock enable */
            microhal::Bitfield<uint32_t, 29, 1> OTGHSEN;     /*!< USB OTG HS clock enable */
            microhal::Bitfield<uint32_t, 30, 1> OTGHSULPIEN; /*!< USB OTG HSULPI clock enable */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB1ENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB1ENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB1ENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB1ENR operator&(uint32_t value) const {
            AHB1ENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB1ENR operator|(uint32_t value) const {
            AHB1ENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB1ENR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB1ENR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB1ENR, AccessType::ReadWrite>;
    };

    // AHB2 peripheral clock enable register
    union AHB2ENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> DCMIEN;  /*!< Camera interface enable */
            microhal::Bitfield<uint32_t, 6, 1> RNGEN;   /*!< Random number generator clock enable */
            microhal::Bitfield<uint32_t, 7, 1> OTGFSEN; /*!< USB OTG FS clock enable */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB2ENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB2ENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB2ENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB2ENR operator&(uint32_t value) const {
            AHB2ENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB2ENR operator|(uint32_t value) const {
            AHB2ENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB2ENR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB2ENR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB2ENR, AccessType::ReadWrite>;
    };

    // AHB3 peripheral clock enable register
    union AHB3ENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> FSMCEN; /*!< Flexible static memory controller module clock enable */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB3ENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB3ENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB3ENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB3ENR operator&(uint32_t value) const {
            AHB3ENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB3ENR operator|(uint32_t value) const {
            AHB3ENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB3ENR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB3ENR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB3ENR, AccessType::ReadWrite>;
    };

    // APB1 peripheral clock enable register
    union APB1ENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> TIM2EN;    /*!< TIM2 clock enable */
            microhal::Bitfield<uint32_t, 1, 1> TIM3EN;    /*!< TIM3 clock enable */
            microhal::Bitfield<uint32_t, 2, 1> TIM4EN;    /*!< TIM4 clock enable */
            microhal::Bitfield<uint32_t, 3, 1> TIM5EN;    /*!< TIM5 clock enable */
            microhal::Bitfield<uint32_t, 4, 1> TIM6EN;    /*!< TIM6 clock enable */
            microhal::Bitfield<uint32_t, 5, 1> TIM7EN;    /*!< TIM7 clock enable */
            microhal::Bitfield<uint32_t, 6, 1> TIM12EN;   /*!< TIM12 clock enable */
            microhal::Bitfield<uint32_t, 7, 1> TIM13EN;   /*!< TIM13 clock enable */
            microhal::Bitfield<uint32_t, 8, 1> TIM14EN;   /*!< TIM14 clock enable */
            microhal::Bitfield<uint32_t, 11, 1> WWDGEN;   /*!< Window watchdog clock enable */
            microhal::Bitfield<uint32_t, 14, 1> SPI2EN;   /*!< SPI2 clock enable */
            microhal::Bitfield<uint32_t, 15, 1> SPI3EN;   /*!< SPI3 clock enable */
            microhal::Bitfield<uint32_t, 17, 1> USART2EN; /*!< USART 2 clock enable */
            microhal::Bitfield<uint32_t, 18, 1> USART3EN; /*!< USART3 clock enable */
            microhal::Bitfield<uint32_t, 19, 1> UART4EN;  /*!< UART4 clock enable */
            microhal::Bitfield<uint32_t, 20, 1> UART5EN;  /*!< UART5 clock enable */
            microhal::Bitfield<uint32_t, 21, 1> I2C1EN;   /*!< I2C1 clock enable */
            microhal::Bitfield<uint32_t, 22, 1> I2C2EN;   /*!< I2C2 clock enable */
            microhal::Bitfield<uint32_t, 23, 1> I2C3EN;   /*!< I2C3 clock enable */
            microhal::Bitfield<uint32_t, 25, 1> CAN1EN;   /*!< CAN 1 clock enable */
            microhal::Bitfield<uint32_t, 26, 1> CAN2EN;   /*!< CAN 2 clock enable */
            microhal::Bitfield<uint32_t, 28, 1> PWREN;    /*!< Power interface clock enable */
            microhal::Bitfield<uint32_t, 29, 1> DACEN;    /*!< DAC interface clock enable */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        APB1ENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        APB1ENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        APB1ENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        APB1ENR operator&(uint32_t value) const {
            APB1ENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        APB1ENR operator|(uint32_t value) const {
            APB1ENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<APB1ENR, AccessType::ReadOnly>;
        friend class VolatileRegister<APB1ENR, AccessType::WriteOnly>;
        friend class VolatileRegister<APB1ENR, AccessType::ReadWrite>;
    };

    // APB2 peripheral clock enable register
    union APB2ENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> TIM1EN;    /*!< TIM1 clock enable */
            microhal::Bitfield<uint32_t, 1, 1> TIM8EN;    /*!< TIM8 clock enable */
            microhal::Bitfield<uint32_t, 4, 1> USART1EN;  /*!< USART1 clock enable */
            microhal::Bitfield<uint32_t, 5, 1> USART6EN;  /*!< USART6 clock enable */
            microhal::Bitfield<uint32_t, 8, 1> ADC1EN;    /*!< ADC1 clock enable */
            microhal::Bitfield<uint32_t, 9, 1> ADC2EN;    /*!< ADC2 clock enable */
            microhal::Bitfield<uint32_t, 10, 1> ADC3EN;   /*!< ADC3 clock enable */
            microhal::Bitfield<uint32_t, 11, 1> SDIOEN;   /*!< SDIO clock enable */
            microhal::Bitfield<uint32_t, 12, 1> SPI1EN;   /*!< SPI1 clock enable */
            microhal::Bitfield<uint32_t, 14, 1> SYSCFGEN; /*!< System configuration controller clock enable */
            microhal::Bitfield<uint32_t, 16, 1> TIM9EN;   /*!< TIM9 clock enable */
            microhal::Bitfield<uint32_t, 17, 1> TIM10EN;  /*!< TIM10 clock enable */
            microhal::Bitfield<uint32_t, 18, 1> TIM11EN;  /*!< TIM11 clock enable */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        APB2ENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        APB2ENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        APB2ENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        APB2ENR operator&(uint32_t value) const {
            APB2ENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        APB2ENR operator|(uint32_t value) const {
            APB2ENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<APB2ENR, AccessType::ReadOnly>;
        friend class VolatileRegister<APB2ENR, AccessType::WriteOnly>;
        friend class VolatileRegister<APB2ENR, AccessType::ReadWrite>;
    };

    // AHB1 peripheral clock enable in low power mode register
    union AHB1LPENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> GPIOALPEN;      /*!< IO port A clock enable during sleep mode */
            microhal::Bitfield<uint32_t, 1, 1> GPIOBLPEN;      /*!< IO port B clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 2, 1> GPIOCLPEN;      /*!< IO port C clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 3, 1> GPIODLPEN;      /*!< IO port D clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 4, 1> GPIOELPEN;      /*!< IO port E clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 5, 1> GPIOFLPEN;      /*!< IO port F clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 6, 1> GPIOGLPEN;      /*!< IO port G clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 7, 1> GPIOHLPEN;      /*!< IO port H clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 8, 1> GPIOILPEN;      /*!< IO port I clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 9, 1> GPIOJLPEN;      /*!< IO port J clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 10, 1> GPIOKLPEN;     /*!< IO port K clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 12, 1> CRCLPEN;       /*!< CRC clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 15, 1> FLITFLPEN;     /*!< Flash interface clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 16, 1> SRAM1LPEN;     /*!< SRAM 1interface clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 17, 1> SRAM2LPEN;     /*!< SRAM 2 interface clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 18, 1> BKPSRAMLPEN;   /*!< Backup SRAM interface clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 21, 1> DMA1LPEN;      /*!< DMA1 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 22, 1> DMA2LPEN;      /*!< DMA2 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 25, 1> ETHMACLPEN;    /*!< Ethernet MAC clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 26, 1> ETHMACTXLPEN;  /*!< Ethernet transmission clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 27, 1> ETHMACRXLPEN;  /*!< Ethernet reception clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 28, 1> ETHMACPTPLPEN; /*!< Ethernet PTP clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 29, 1> OTGHSLPEN;     /*!< USB OTG HS clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 30, 1> OTGHSULPILPEN; /*!< USB OTG HS ULPI clock enable during Sleep mode */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB1LPENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB1LPENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB1LPENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB1LPENR operator&(uint32_t value) const {
            AHB1LPENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB1LPENR operator|(uint32_t value) const {
            AHB1LPENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB1LPENR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB1LPENR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB1LPENR, AccessType::ReadWrite>;
    };

    // AHB2 peripheral clock enable in low power mode register
    union AHB2LPENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> DCMILPEN;  /*!< Camera interface enable during Sleep mode */
            microhal::Bitfield<uint32_t, 6, 1> RNGLPEN;   /*!< Random number generator clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 7, 1> OTGFSLPEN; /*!< USB OTG FS clock enable during Sleep mode */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB2LPENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB2LPENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB2LPENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB2LPENR operator&(uint32_t value) const {
            AHB2LPENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB2LPENR operator|(uint32_t value) const {
            AHB2LPENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB2LPENR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB2LPENR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB2LPENR, AccessType::ReadWrite>;
    };

    // AHB3 peripheral clock enable in low power mode register
    union AHB3LPENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> FSMCLPEN; /*!< Flexible static memory controller module clock enable during Sleep mode */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        AHB3LPENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        AHB3LPENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        AHB3LPENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        AHB3LPENR operator&(uint32_t value) const {
            AHB3LPENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        AHB3LPENR operator|(uint32_t value) const {
            AHB3LPENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<AHB3LPENR, AccessType::ReadOnly>;
        friend class VolatileRegister<AHB3LPENR, AccessType::WriteOnly>;
        friend class VolatileRegister<AHB3LPENR, AccessType::ReadWrite>;
    };

    // APB1 peripheral clock enable in low power mode register
    union APB1LPENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> TIM2LPEN;    /*!< TIM2 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 1, 1> TIM3LPEN;    /*!< TIM3 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 2, 1> TIM4LPEN;    /*!< TIM4 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 3, 1> TIM5LPEN;    /*!< TIM5 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 4, 1> TIM6LPEN;    /*!< TIM6 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 5, 1> TIM7LPEN;    /*!< TIM7 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 6, 1> TIM12LPEN;   /*!< TIM12 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 7, 1> TIM13LPEN;   /*!< TIM13 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 8, 1> TIM14LPEN;   /*!< TIM14 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 11, 1> WWDGLPEN;   /*!< Window watchdog clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 14, 1> SPI2LPEN;   /*!< SPI2 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 15, 1> SPI3LPEN;   /*!< SPI3 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 17, 1> USART2LPEN; /*!< USART2 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 18, 1> USART3LPEN; /*!< USART3 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 19, 1> UART4LPEN;  /*!< UART4 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 20, 1> UART5LPEN;  /*!< UART5 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 21, 1> I2C1LPEN;   /*!< I2C1 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 22, 1> I2C2LPEN;   /*!< I2C2 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 23, 1> I2C3LPEN;   /*!< I2C3 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 25, 1> CAN1LPEN;   /*!< CAN 1 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 26, 1> CAN2LPEN;   /*!< CAN 2 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 28, 1> PWRLPEN;    /*!< Power interface clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 29, 1> DACLPEN;    /*!< DAC interface clock enable during Sleep mode */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        APB1LPENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        APB1LPENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        APB1LPENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        APB1LPENR operator&(uint32_t value) const {
            APB1LPENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        APB1LPENR operator|(uint32_t value) const {
            APB1LPENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<APB1LPENR, AccessType::ReadOnly>;
        friend class VolatileRegister<APB1LPENR, AccessType::WriteOnly>;
        friend class VolatileRegister<APB1LPENR, AccessType::ReadWrite>;
    };

    // APB2 peripheral clock enabled in low power mode register
    union APB2LPENR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> TIM1LPEN;    /*!< TIM1 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 1, 1> TIM8LPEN;    /*!< TIM8 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 4, 1> USART1LPEN;  /*!< USART1 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 5, 1> USART6LPEN;  /*!< USART6 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 8, 1> ADC1LPEN;    /*!< ADC1 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 9, 1> ADC2LPEN;    /*!< ADC2 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 10, 1> ADC3LPEN;   /*!< ADC 3 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 11, 1> SDIOLPEN;   /*!< SDIO clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 12, 1> SPI1LPEN;   /*!< SPI 1 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 14, 1> SYSCFGLPEN; /*!< System configuration controller clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 16, 1> TIM9LPEN;   /*!< TIM9 clock enable during sleep mode */
            microhal::Bitfield<uint32_t, 17, 1> TIM10LPEN;  /*!< TIM10 clock enable during Sleep mode */
            microhal::Bitfield<uint32_t, 18, 1> TIM11LPEN;  /*!< TIM11 clock enable during Sleep mode */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        APB2LPENR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        APB2LPENR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        APB2LPENR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        APB2LPENR operator&(uint32_t value) const {
            APB2LPENR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        APB2LPENR operator|(uint32_t value) const {
            APB2LPENR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<APB2LPENR, AccessType::ReadOnly>;
        friend class VolatileRegister<APB2LPENR, AccessType::WriteOnly>;
        friend class VolatileRegister<APB2LPENR, AccessType::ReadWrite>;
    };

    // Backup domain control register
    union BDCR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> LSEON;   /*!< External low-speed oscillator enable */
            microhal::Bitfield<uint32_t, 1, 1> LSERDY;  /*!< External low-speed oscillator ready */
            microhal::Bitfield<uint32_t, 2, 1> LSEBYP;  /*!< External low-speed oscillator bypass */
            microhal::Bitfield<uint32_t, 8, 1> RTCSEL0; /*!< RTC clock source selection */
            microhal::Bitfield<uint32_t, 9, 1> RTCSEL1; /*!< RTC clock source selection */
            microhal::Bitfield<uint32_t, 15, 1> RTCEN;  /*!< RTC clock enable */
            microhal::Bitfield<uint32_t, 16, 1> BDRST;  /*!< Backup domain software reset */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        BDCR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        BDCR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        BDCR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        BDCR operator&(uint32_t value) const {
            BDCR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        BDCR operator|(uint32_t value) const {
            BDCR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<BDCR, AccessType::ReadOnly>;
        friend class VolatileRegister<BDCR, AccessType::WriteOnly>;
        friend class VolatileRegister<BDCR, AccessType::ReadWrite>;
    };

    // clock control & status register
    union CSR {
        union {
            microhal::Bitfield<uint32_t, 0, 1> LSION;     /*!< Internal low-speed oscillator enable */
            microhal::Bitfield<uint32_t, 1, 1> LSIRDY;    /*!< Internal low-speed oscillator ready */
            microhal::Bitfield<uint32_t, 24, 1> RMVF;     /*!< Remove reset flag */
            microhal::Bitfield<uint32_t, 25, 1> BORRSTF;  /*!< BOR reset flag */
            microhal::Bitfield<uint32_t, 26, 1> PADRSTF;  /*!< PIN reset flag */
            microhal::Bitfield<uint32_t, 27, 1> PORRSTF;  /*!< POR/PDR reset flag */
            microhal::Bitfield<uint32_t, 28, 1> SFTRSTF;  /*!< Software reset flag */
            microhal::Bitfield<uint32_t, 29, 1> WDGRSTF;  /*!< Independent watchdog reset flag */
            microhal::Bitfield<uint32_t, 30, 1> WWDGRSTF; /*!< Window watchdog reset flag */
            microhal::Bitfield<uint32_t, 31, 1> LPWRRSTF; /*!< Low-power reset flag */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        CSR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        CSR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        CSR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        CSR operator&(uint32_t value) const {
            CSR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        CSR operator|(uint32_t value) const {
            CSR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<CSR, AccessType::ReadOnly>;
        friend class VolatileRegister<CSR, AccessType::WriteOnly>;
        friend class VolatileRegister<CSR, AccessType::ReadWrite>;
    };

    // spread spectrum clock generation register
    union SSCGR {
        union {
            microhal::Bitfield<uint32_t, 0, 13> MODPER;    /*!< Modulation period */
            microhal::Bitfield<uint32_t, 13, 15> INCSTEP;  /*!< Incrementation step */
            microhal::Bitfield<uint32_t, 30, 1> SPREADSEL; /*!< Spread Select */
            microhal::Bitfield<uint32_t, 31, 1> SSCGEN;    /*!< Spread spectrum modulation enable */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        SSCGR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        SSCGR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        SSCGR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        SSCGR operator&(uint32_t value) const {
            SSCGR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        SSCGR operator|(uint32_t value) const {
            SSCGR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<SSCGR, AccessType::ReadOnly>;
        friend class VolatileRegister<SSCGR, AccessType::WriteOnly>;
        friend class VolatileRegister<SSCGR, AccessType::ReadWrite>;
    };

    // PLLI2S configuration register
    union PLLI2SCFGR {
        union {
            microhal::Bitfield<uint32_t, 6, 9> PLLI2SNx;  /*!< PLLI2S multiplication factor for VCO */
            microhal::Bitfield<uint32_t, 28, 3> PLLI2SRx; /*!< PLLI2S division factor for I2S clocks */
        };

        operator uint32_t() const { return raw; }
        operator bool() const { return raw; }

        PLLI2SCFGR &operator=(uint32_t value) {
            raw = value;
            return *this;
        }
        PLLI2SCFGR &operator|=(uint32_t value) {
            raw |= value;
            return *this;
        }
        PLLI2SCFGR &operator&=(uint32_t value) {
            raw &= value;
            return *this;
        }

        bool operator==(uint32_t value) const { return raw == value; }
        bool operator!=(uint32_t value) const { return raw != value; }
        bool operator>(uint32_t value) const { return raw > value; }
        bool operator<(uint32_t value) const { return raw < value; }
        bool operator>=(uint32_t value) const { return raw >= value; }
        bool operator<=(uint32_t value) const { return raw <= value; }
        PLLI2SCFGR operator&(uint32_t value) const {
            PLLI2SCFGR tmp;
            tmp.raw = raw & value;
            return tmp;
        }
        PLLI2SCFGR operator|(uint32_t value) const {
            PLLI2SCFGR tmp;
            tmp.raw = raw | value;
            return tmp;
        }

     private:
        uint32_t raw;
        friend class VolatileRegister<PLLI2SCFGR, AccessType::ReadOnly>;
        friend class VolatileRegister<PLLI2SCFGR, AccessType::WriteOnly>;
        friend class VolatileRegister<PLLI2SCFGR, AccessType::ReadWrite>;
    };

    VolatileRegister<CR, AccessType::ReadWrite> cr;               /*!< clock control register	Address offset: 0x0 */
    VolatileRegister<PLLCFGR, AccessType::ReadWrite> pllcfgr;     /*!< PLL configuration register	Address offset: 0x4 */
    VolatileRegister<CFGR, AccessType::ReadWrite> cfgr;           /*!< clock configuration register	Address offset: 0x8 */
    VolatileRegister<CIR, AccessType::ReadWrite> cir;             /*!< clock interrupt register	Address offset: 0xC */
    VolatileRegister<AHB1RSTR, AccessType::ReadWrite> ahb1rstr;   /*!< AHB1 peripheral reset register	Address offset: 0x10 */
    VolatileRegister<AHB2RSTR, AccessType::ReadWrite> ahb2rstr;   /*!< AHB2 peripheral reset register	Address offset: 0x14 */
    VolatileRegister<AHB3RSTR, AccessType::ReadWrite> ahb3rstr;   /*!< AHB3 peripheral reset register	Address offset: 0x18 */
    uint32_t reserved0[1];                                        /*!< Reserved register	Address offset: 0x1c */
    VolatileRegister<APB1RSTR, AccessType::ReadWrite> apb1rstr;   /*!< APB1 peripheral reset register	Address offset: 0x20 */
    VolatileRegister<APB2RSTR, AccessType::ReadWrite> apb2rstr;   /*!< APB2 peripheral reset register	Address offset: 0x24 */
    uint32_t reserved1[2];                                        /*!< Reserved register	Address offset: 0x28 */
    VolatileRegister<AHB1ENR, AccessType::ReadWrite> ahb1enr;     /*!< AHB1 peripheral clock register	Address offset: 0x30 */
    VolatileRegister<AHB2ENR, AccessType::ReadWrite> ahb2enr;     /*!< AHB2 peripheral clock enable register	Address offset: 0x34 */
    VolatileRegister<AHB3ENR, AccessType::ReadWrite> ahb3enr;     /*!< AHB3 peripheral clock enable register	Address offset: 0x38 */
    uint32_t reserved2[1];                                        /*!< Reserved register	Address offset: 0x3c */
    VolatileRegister<APB1ENR, AccessType::ReadWrite> apb1enr;     /*!< APB1 peripheral clock enable register	Address offset: 0x40 */
    VolatileRegister<APB2ENR, AccessType::ReadWrite> apb2enr;     /*!< APB2 peripheral clock enable register	Address offset: 0x44 */
    uint32_t reserved3[2];                                        /*!< Reserved register	Address offset: 0x48 */
    VolatileRegister<AHB1LPENR, AccessType::ReadWrite> ahb1lpenr; /*!< AHB1 peripheral clock enable in low power mode register	Address offset: 0x50
                                                                   */
    VolatileRegister<AHB2LPENR, AccessType::ReadWrite> ahb2lpenr; /*!< AHB2 peripheral clock enable in low power mode register	Address offset: 0x54
                                                                   */
    VolatileRegister<AHB3LPENR, AccessType::ReadWrite> ahb3lpenr; /*!< AHB3 peripheral clock enable in low power mode register	Address offset: 0x58
                                                                   */
    uint32_t reserved4[1];                                        /*!< Reserved register	Address offset: 0x5c */
    VolatileRegister<APB1LPENR, AccessType::ReadWrite> apb1lpenr; /*!< APB1 peripheral clock enable in low power mode register	Address offset: 0x60
                                                                   */
    VolatileRegister<APB2LPENR, AccessType::ReadWrite>
        apb2lpenr;                                        /*!< APB2 peripheral clock enabled in low power mode register	Address offset: 0x64 */
    uint32_t reserved5[2];                                /*!< Reserved register	Address offset: 0x68 */
    VolatileRegister<BDCR, AccessType::ReadWrite> bdcr;   /*!< Backup domain control register	Address offset: 0x70 */
    VolatileRegister<CSR, AccessType::ReadWrite> csr;     /*!< clock control & status register	Address offset: 0x74 */
    uint32_t reserved6[2];                                /*!< Reserved register	Address offset: 0x78 */
    VolatileRegister<SSCGR, AccessType::ReadWrite> sscgr; /*!< spread spectrum clock generation register	Address offset: 0x80 */
    VolatileRegister<PLLI2SCFGR, AccessType::ReadWrite> plli2scfgr; /*!< PLLI2S configuration register	Address offset: 0x84 */
};

[[maybe_unused]] static RCC *const rcc = reinterpret_cast<RCC *>(_MICROHAL_RCC_BASE_ADDRESS);
}  // namespace registers
}  // namespace microhal
#endif  // _MICROHAL_PERIPHERAL_REGISTER_RCC