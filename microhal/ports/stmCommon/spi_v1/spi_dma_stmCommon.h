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
#ifdef MICROHAL_USE_SPI1_DMA
    static SPI_dma spi1;
#endif
#ifdef MICROHAL_USE_SPI2_DMA
    static SPI_dma spi2;
#endif
#ifdef MICROHAL_USE_SPI3_DMA
    static SPI_dma spi3;
#endif
#ifdef MICROHAL_USE_SPI4_DMA
    static SPI_dma spi4;
#endif
#ifdef MICROHAL_USE_SPI5_DMA
    static SPI_dma spi5;
#endif
#ifdef MICROHAL_USE_SPI6_DMA
    static SPI_dma spi6;
#endif
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
    //---------------------------------------- variables ----------------------------------------//
    os::Semaphore semaphore;
    DMA::DMA &dma;
    DMA::Stream &rxStream;
    DMA::Stream &txStream;

    //--------------------------------------- constructors --------------------------------------//
    SPI_dma(registers::SPI &spi, DMA::DMA &dma, DMA::Stream &rxStream, DMA::Stream &txStream, _MICROHAL_ACTIVE_PORT_NAMESPACE::IOPin misoPin)
        : SPI(spi, misoPin), semaphore(), dma(dma), rxStream(rxStream), txStream(txStream) {
#if defined(_MICROHAL_CLOCKMANAGER_HAS_POWERMODE) && _MICROHAL_CLOCKMANAGER_HAS_POWERMODE == 1
        ClockManager::enableSPI(getNumber, ClockManager::PowerMode::Normal);
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
