/*
 * SPI_dma_stm32f4xx.h
 *
 *  Created on: 17 kwi 2014
 *      Author: pawel
 */

#ifndef _MICROHAL_SPI_DMA_STMCOMMON_H_
#define _MICROHAL_SPI_DMA_STMCOMMON_H_
/* ************************************************************************************************
 * INCLUDES
 */
#include "microhal_semaphore.h"
#include "spi_stmCommon.h"
#include _MICROHAL_INCLUDE_PORT_clockManager
#include _MICROHAL_INCLUDE_PORT_DMA
#include _MICROHAL_INCLUDE_PORT_CONFIG
#include _MICROHAL_INCLUDE_PORT_IOMANAGER

#if !defined(MICROHAL_USE_SPI1_DMA)
#define MICROHAL_USE_SPI1_DMA 0
#endif
#if !defined(MICROHAL_USE_SPI2_DMA)
#define MICROHAL_USE_SPI2_DMA 0
#endif
#if !defined(MICROHAL_USE_SPI3_DMA)
#define MICROHAL_USE_SPI3_DMA 0
#endif
#if !defined(MICROHAL_USE_SPI4_DMA)
#define MICROHAL_USE_SPI4_DMA 0
#endif
#if !defined(MICROHAL_USE_SPI5_DMA)
#define MICROHAL_USE_SPI5_DMA 0
#endif
#if !defined(MICROHAL_USE_SPI6_DMA)
#define MICROHAL_USE_SPI6_DMA 0
#endif

namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {
extern "C" {
void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);

void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
}
/* ************************************************************************************************
 * CLASS
 */
class SPI_dma : public _MICROHAL_ACTIVE_PORT_NAMESPACE::SPI {
 public:
    //---------------------------------------- variables ----------------------------------------//
    template <int number, IOPin::Port misoPort, IOPin::Pin misoPin, IOPin::Port mosiPort, IOPin::Pin mosiPin, IOPin::Port sckPort, IOPin::Pin sckPin>
    static SPI_dma &create(GPIO::OutputType mosiType = GPIO::PushPull, GPIO::OutputType sckType = GPIO::PushPull) {
        constexpr IOPin miso(misoPort, misoPin);
        constexpr IOPin mosi(mosiPort, mosiPin);
        constexpr IOPin sck(sckPort, sckPin);

        static_assert(IOManager::spiPinAssert(number, miso, mosi, sck), "Incorrect SPI Pin configuration");
        IOManager::routeSpi<number>(miso, mosi, sck, mosiType, sckType);
        if constexpr (number == 1) {
            static_assert(MICROHAL_USE_SPI1_DMA == 1 && number == 1,
                          "You have to define 'MICROHAL_USE_SPI1_DMA 1' in microhalPortConfig_xxx.h file.");
#if MICROHAL_USE_SPI1_DMA == 1
            static SPI_dma _spi1(*microhal::registers::spi1, *DMA::dma2, DMA::dma2->stream[MICROHAL_SPI1_DMA_RX_STREAM],
                                 DMA::dma2->stream[MICROHAL_SPI1_DMA_TX_STREAM], miso);
            spi1 = &_spi1;
            return *spi1;
#endif
        }
        if constexpr (number == 2) {
            static_assert(MICROHAL_USE_SPI2_DMA == 1 && number == 2,
                          "You have to define 'MICROHAL_USE_SPI2_DMA 1' in microhalPortConfig_xxx.h file.");
#if MICROHAL_USE_SPI2_DMA == 1
            static SPI_interrupt _spi2(*microhal::registers::spi2, *DMA::dma1, DMA::dma1->stream[3], DMA::dma1->stream[4], miso);
            spi2 = &_spi2;
            return *spi2;
#endif
        }
        if constexpr (number == 3) {
            static_assert(MICROHAL_USE_SPI3_DMA == 1 && number == 3,
                          "You have to define 'MICROHAL_USE_SPI3_DMA 1' in microhalPortConfig_xxx.h file.");
#if MICROHAL_USE_SPI3_DMA == 1
            static SPI_interrupt _spi3(*microhal::registers::spi3, *DMA::dma1, DMA::dma1->stream[MICROHAL_SPI3_DMA_RX_STREAM],
                                       DMA::dma1->stream[MICROHAL_SPI3_DMA_TX_STREAM], miso);
            spi3 = &_spi3;
            return *spi3;
#endif
        }
        if constexpr (number == 4) {
            static_assert(MICROHAL_USE_SPI4_DMA == 1 && number == 4,
                          "You have to define 'MICROHAL_USE_SPI4_DMA 1' in microhalPortConfig_xxx.h file.");
#if MICROHAL_USE_SPI4_DMA == 1
            static SPI_interrupt _spi4(*microhal::registers::spi4, *DMA::dma2, DMA::dma2->stream[MICROHAL_SPI4_DMA_RX_STREAM],
                                       DMA::dma2->stream[MICROHAL_SPI4_DMA_TX_STREAM], miso);
            spi4 = &_spi4;
            return *spi4;
#endif
        }
        if constexpr (number == 5) {
            static_assert(MICROHAL_USE_SPI5_DMA == 1 && number == 5,
                          "You have to define 'MICROHAL_USE_SPI5_DMA 1' in microhalPortConfig_xxx.h file.");
#if MICROHAL_USE_SPI5_DMA == 1
            static SPI_interrupt _spi5(*microhal::registers::spi5, *DMA::dma2, DMA::dma2->stream[MICROHAL_SPI5_DMA_RX_STREAM],
                                       DMA::dma2->stream[MICROHAL_SPI5_DMA_TX_STREAM], miso);
            spi5 = &_spi5;
            return *spi5;
#endif
        }
        if constexpr (number == 6) {
            static_assert(MICROHAL_USE_SPI6_DMA == 1 && number == 6,
                          "You have to define 'MICROHAL_USE_SPI3_DMA 1' in microhalPortConfig_xxx.h file.");
#if MICROHAL_USE_SPI6_DMA == 1
            static SPI_interrupt _spi6(*microhal::registers::spi6, *DMA::dma2, DMA::dma2->stream[5], DMA::dma2->stream[6], miso);
            spi6 = &_spi6;
            return *spi6;
#endif
        }
        std::terminate();
    }
    //---------------------------------------- functions ----------------------------------------//
    SPI::Error write(const void *data, size_t len, bool last) final;
    SPI::Error read(void *data, size_t len, uint8_t write = 0x00) final { return writeRead(&write, data, 1, len); }
    SPI::Error writeRead(void *dataRead, const void *dataWrite, size_t readWriteLength) final {
        return writeRead(dataWrite, dataRead, readWriteLength, readWriteLength);
    }

    void setDMAStreamPriority(DMA::Stream::Priority rxPriority, DMA::Stream::Priority txPriority) {
        rxStream.setPriority(rxPriority);
        txStream.setPriority(txPriority);
    }

 private:
#if defined(MICROHAL_USE_SPI1_DMA) && MICROHAL_USE_SPI1_DMA == 1
    static SPI_dma *spi1;
#endif
#if defined(MICROHAL_USE_SPI2_DMA) && MICROHAL_USE_SPI2_DMA == 1
    static SPI_dma *spi2;
#endif
#if defined(MICROHAL_USE_SPI3_DMA) && MICROHAL_USE_SPI3_DMA == 1
    static SPI_dma *spi3;
#endif
#if defined(MICROHAL_USE_SPI4_DMA) && MICROHAL_USE_SPI4_DMA == 1
    static SPI_dma *spi4;
#endif
#if defined(MICROHAL_USE_SPI5_DMA) && MICROHAL_USE_SPI5_DMA == 1
    static SPI_dma *spi5;
#endif
#if defined(MICROHAL_USE_SPI6_DMA) && MICROHAL_USE_SPI6_DMA == 1
    static SPI_dma *spi6;
#endif
    //---------------------------------------- variables ----------------------------------------//
    os::Semaphore semaphore;
    DMA::DMA &dma;
    DMA::Stream &rxStream;
    DMA::Stream &txStream;

    //--------------------------------------- constructors --------------------------------------//
    SPI_dma(registers::SPI &spi, DMA::DMA &dma, DMA::Stream &rxStream, DMA::Stream &txStream, _MICROHAL_ACTIVE_PORT_NAMESPACE::IOPin misoPin)
        : SPI(spi, misoPin), semaphore(), dma(dma), rxStream(rxStream), txStream(txStream) {
#if defined(_MICROHAL_CLOCKMANAGER_HAS_POWERMODE) && _MICROHAL_CLOCKMANAGER_HAS_POWERMODE == 1
        ClockManager::enableSPI(getNumber(), ClockManager::PowerMode::Normal);
#else
        ClockManager::enableSPI(getNumber());
#endif
#if defined(HAL_RTOS_FreeRTOS)
        enableGlobalInterrupt(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
#else
        enableGlobalInterrupt(0);
#endif
        init();
    }

    SPI::Error writeRead(const void *writePtr, void *readPtr, size_t writeLen, size_t readLen);

    //---------------------------------------- functions ----------------------------------------//
    void init();

    static inline void IRQfunction(SPI_dma &object, registers::SPI *spi);
    //----------------------------------------- friends -----------------------------------------//
    friend void DMA1_Stream0_IRQHandler(void);
    friend void DMA1_Stream2_IRQHandler(void);
    friend void DMA1_Stream3_IRQHandler(void);
    friend void DMA1_Stream4_IRQHandler(void);
    friend void DMA1_Stream5_IRQHandler(void);
    friend void DMA1_Stream7_IRQHandler(void);

    friend void DMA2_Stream2_IRQHandler(void);
    friend void DMA2_Stream3_IRQHandler(void);
    friend void DMA2_Stream5_IRQHandler(void);

    friend void SPI1_IRQHandler(void);
    friend void SPI2_IRQHandler(void);
    friend void SPI3_IRQHandler(void);
    friend void SPI4_IRQHandler(void);
    friend void SPI5_IRQHandler(void);
    friend void SPI6_IRQHandler(void);
};

}  // namespace _MICROHAL_ACTIVE_PORT_NAMESPACE
}  // namespace microhal

#endif /* _MICROHAL_SPI_DMA_STMCOMMON_H_ */
