#ifndef SPI_POLLING_STM32F3XX_H_
#define SPI_POLLING_STM32F3XX_H_
/* ************************************************************************************************
 * INCLUDES
 */
#include "../clockManager.h"
#include "../spi_stm32f3xx.h"

namespace microhal {
namespace stm32f3xx {
/* ************************************************************************************************
 * CLASS
 */
class SPI_polling : public stm32f3xx::SPI {
 public:
//---------------------------------------- variables ----------------------------------------//
#ifdef MICROHAL_USE_SPI1_POLLING
    static SPI_polling spi1;
#endif
#ifdef MICROHAL_USE_SPI2_POLLING
    static SPI_polling spi2;
#endif
#ifdef MICROHAL_USE_SPI3_POLLING
    static SPI_polling spi3;
#endif
    //---------------------------------------- functions ----------------------------------------//
    SPI::Error write(const void *data, const size_t len, bool last) final {
        for (size_t i = 0; i < len; i++) {
            SPI::Error error = writeNoRead(((uint8_t *)(data))[i]);
            if (error != Error::None && error != Error::Overrun) return error;  // because we are don't reading data overrun error is normal
        }
        if (last) {
            while (spi.SR & SPI_SR_FTLVL_Msk) {
            }
            while (spi.SR & SPI_SR_BSY)
                ;
        }
        spi.SR &= ~SPI_SR_OVR;
        return Error::None;
    }
    SPI::Error read(void *data, size_t len, uint8_t write = 0x00) final {
        if (len == 0) return SPI::Error::None;
        uint32_t sr;
        while (spi.SR & SPI_SR_FTLVL_Msk) {
        }
        do {
            sr = spi.SR;
            SPI::Error error = errorCheck(sr);
            if (error != Error::None && error != Error::Overrun) return error;  // because we are don't reading data overrun error may occur
        } while (sr & SPI_SR_BSY);
        while (spi.SR & SPI_SR_FRLVL_Msk) {
            volatile uint16_t tmp __attribute__((unused)) = spi.DR;
        }
        SPI::Error error;
        for (size_t i = 0; i < len; i++) {
            error = writeRead(write, static_cast<uint8_t *>(data)[i]);
            if (error != Error::None) break;
        }
        return error;
    }
    SPI::Error writeRead(void *dataRead, const void *dataWrite, size_t readWriteLength) final;

 private:
    //---------------------------------------- constructors ---------------------------------------
    SPI_polling(SPI_TypeDef &spi, stm32f3xx::IOPin misoPin) : SPI(spi, misoPin) { ClockManager::enable(spi); }
    //---------------------------------------- functions ----------------------------------------//
    SPI::Error writeNoRead(const uint8_t data) {
        uint32_t sr;
        SPI::Error error = Error::None;

        do {
            sr = spi.SR;
            error = errorCheck(sr);
            if (error != Error::None && error != Error::Overrun) return error;
        } while (!(sr & SPI_SR_TXE));

        writeDR(data);

        return error;
    }
    SPI::Error writeRead(const uint8_t data, uint8_t &receivedData) {
        uint32_t sr;
        SPI::Error error;
        do {
            sr = spi.SR;
            error = errorCheck(sr);
            if (error != Error::None && error != Error::Overrun) return error;
        } while (!(sr & SPI_SR_TXE));

        writeDR(data);

        do {
            sr = spi.SR;
            error = errorCheck(sr);
            if (error != Error::None) return error;
        } while (!(spi.SR & SPI_SR_RXNE));

        receivedData = readDR();

        return error;
    }
};

}  // namespace stm32f3xx
}  // namespace microhal

#endif  // SPI_POLLING_STM32F3XX_H_
