/*
 * serialPort_dma_stm32f3xx.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: pokas
 */

#include "serialPort_dma_stm32f3xx.h"

namespace microhal {
namespace stm32f3xx {

//***********************************************************************************************//
//                                   STATIC VARIABLES
//***********************************************************************************************//
#ifdef MICROHAL_USE_SERIAL_PORT1_DMA
static char txBufferData_1[MICROHAL_SERIAL_PORT1_TX_BUFFER_SIZE];
static char rxBufferData_1[MICROHAL_SERIAL_PORT1_RX_BUFFER_SIZE];
SerialPort_Dma SerialPort_Dma::Serial1(*USART1, rxBufferData_1, txBufferData_1, sizeof(rxBufferData_1), sizeof(txBufferData_1), *DMA::dma2,
                                       DMA::dma2->stream[3], DMA::dma2->stream[4]);
SerialPort &SerialPort::Serial1 = SerialPort_Dma::Serial1;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT2_DMA
static char txBufferData_2[MICROHAL_SERIAL_PORT2_TX_BUFFER_SIZE];
static char rxBufferData_2[MICROHAL_SERIAL_PORT2_RX_BUFFER_SIZE];
SerialPort_Dma SerialPort_Dma::Serial2(*USART2, rxBufferData_2, txBufferData_2, sizeof(rxBufferData_2), sizeof(txBufferData_2), *DMA::dma1,
                                       DMA::dma1->stream[6], DMA::dma1->stream[5]);
SerialPort &SerialPort::Serial2 = SerialPort_Dma::Serial2;
#endif
#ifdef MICROHAL_USE_SERIAL_PORT3_DMA
static char txBufferData_3[MICROHAL_SERIAL_PORT3_TX_BUFFER_SIZE];
static char rxBufferData_3[MICROHAL_SERIAL_PORT3_RX_BUFFER_SIZE];
SerialPort_Dma SerialPort_Dma::Serial3(*USART3, rxBufferData_3, txBufferData_3, sizeof(rxBufferData_3), sizeof(txBufferData_3), DMA::dma1->stream[1],
                                       DMA::dma1->stream[2]);
SerialPort &SerialPort::Serial3 = SerialPort_Dma::Serial3;
#endif

SerialPort_Dma::SerialPort_Dma(USART_TypeDef &usart, char *const rxData, char *const txData, size_t rxDataSize, size_t txDataSize,
                               DMA::Channel &txStream, DMA::Channel &rxStream)
    : SerialPort_BufferedBase(usart, rxData, rxDataSize, txData, txDataSize), txStream(txStream), rxStream(rxStream) {
    ClockManager::enable(usart);
    enableInterrupt(0);
    ///////////////////////////////////
    DMA::dma1->clockEnable();
    // tx
    txStream.deinit();
    txStream.init(DMA::Channel::MemoryDataSize::Byte, DMA::Channel::PeripheralDataSize::Byte, DMA::Channel::MemoryIncrementMode::PointerIncremented,
                  DMA::Channel::PeripheralIncrementMode::PointerFixed, DMA::Channel::TransmisionDirection::MemToPer);
    txStream.peripheralAddress(&usart.TDR);
    txStream.enableInterrupt(DMA::Channel::Interrupt::TransferComplete);
    // rx
    rxStream.deinit();
    rxStream.init(DMA::Channel::MemoryDataSize::Byte, DMA::Channel::PeripheralDataSize::Byte, DMA::Channel::MemoryIncrementMode::PointerIncremented,
                  DMA::Channel::PeripheralIncrementMode::PointerFixed, DMA::Channel::TransmisionDirection::PerToMem);
    rxStream.peripheralAddress(&usart.RDR);
    rxStream.enableInterrupt(DMA::Channel::Interrupt::TransferComplete);

    DMA::dma1->clearInterruptFlag(txStream, DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->clearInterruptFlag(rxStream, DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->enableInterrupt(txStream, 6);
    DMA::dma1->enableInterrupt(rxStream, 6);
}

bool SerialPort_Dma::open(OpenMode mode) noexcept {
    if (isOpen() || (mode > 0x03)) return false;
    usart.CR1 |= (mode << 2) | USART_CR1_UE;
    usart.CR3 |= USART_CR3_DMAT | USART_CR3_DMAR;
    prepareRxDmaTransfer();
    return true;
}

size_t SerialPort_Dma::prepareDmaTransfer() {
    const char *writePtr;
    size_t writeLen = txBuffer.getContinousPart(writePtr);
    if (writeLen) {
        transferInProgress = writeLen;
        // configure tx
        txStream.setNumberOfItemsToTransfer(writeLen);
        txStream.memoryAddress((void *)writePtr);
        txStream.enable();
    }
    return writeLen;
}

void SerialPort_Dma::prepareRxDmaTransfer(size_t bytesToReceive) {
    const char *readPtr = nullptr;
    size_t readLen = rxBuffer.getEmptyContinousPart(readPtr);
    if (readLen > bytesToReceive) readLen = bytesToReceive;
    if (readLen) {
        rxTransferInProgress = readLen;
        // configure tx
        rxStream.setNumberOfItemsToTransfer(readLen);
        rxStream.memoryAddress((void *)readPtr);
        rxStream.enable();
    } else {
    }
}
//***********************************************************************************************//
//                                     interrupt functions                                       //
//***********************************************************************************************//
inline void DMA_rx_function(SerialPort_Dma &serial, uint32_t DMA_Stream_NDTR) {
    // update rx buffer
    size_t receivedBytes = serial.rxTransferInProgress - DMA_Stream_NDTR;
    serial.rxBuffer.updateWritePointer(receivedBytes);

    if (serial.waitForBytes != 0) {
        // calculate number of bytes to received
        int32_t bytesForReceive = serial.waitForBytes - receivedBytes;
        serial.waitForBytes = bytesForReceive;
        if (bytesForReceive > 0) {
            serial.prepareRxDmaTransfer(bytesForReceive);
        } else {
            serial.prepareRxDmaTransfer();
            bool shouldYeld = serial.rxSemaphore.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
            portYIELD_FROM_ISR(shouldYeld);
#else
            (void)shouldYeld;
#endif
        }
    }
}

inline void DMA_tx_function(SerialPort_Dma &serial) {
    serial.txBuffer.updateReadPointer(serial.transferInProgress);
    serial.transferInProgress = 0;
    if (serial.prepareDmaTransfer() == 0 && serial.txWait) {
        serial.txWait = false;
        bool shouldYeld = serial.txFinish.giveFromISR();
#if defined(HAL_RTOS_FreeRTOS)
        portYIELD_FROM_ISR(shouldYeld);
#else
        (void)shouldYeld;
#endif
    }
}
//***********************************************************************************************//
//                                          IRQHandlers                                          //
//***********************************************************************************************//
// ---------------------------- serial port 1
#ifdef MICROHAL_USE_SERIAL_PORT1_DMA
void USART3_IRQHandler(void) {
    serialPort_interruptFunction(USART1, SerialPort_Dma::Serial1);
}
// RX
void DMA1_Channel5_IRQHandler(void) {
    DMA::dma1->clearInterruptFlag(DMA::dma1->stream[4], DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->stream[4].disable();

    DMA_rx_function(SerialPort_Dma::Serial1, DMA::dma1->stream[4].getNumberOfItemsInTransfer());
}
// TX
void DMA1_Channel4_IRQHandler(void) {
    DMA::dma1->clearInterruptFlag(DMA::dma1->stream[3], DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->stream[3].disable();

    DMA_tx_function(SerialPort_Dma::Serial1);
}
#endif
// ---------------------------- serial port 2
#ifdef MICROHAL_USE_SERIAL_PORT2_DMA
void USART3_IRQHandler(void) {
    serialPort_interruptFunction(USART2, SerialPort_Dma::Serial2);
}
// RX
void DMA1_Channel6_IRQHandler(void) {
    DMA::dma1->clearInterruptFlag(DMA::dma1->stream[5], DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->stream[5].disable();

    DMA_rx_function(SerialPort_Dma::Serial2, DMA::dma1->stream[5].getNumberOfItemsInTransfer());
}
// TX
void DMA1_Channel7_IRQHandler(void) {
    DMA::dma1->clearInterruptFlag(DMA::dma1->stream[6], DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->stream[6].disable();

    DMA_tx_function(SerialPort_Dma::Serial2);
}
#endif
// ---------------------------- serial port 3
#ifdef MICROHAL_USE_SERIAL_PORT3_DMA
void USART3_IRQHandler(void) {
    serialPort_interruptFunction(USART3, SerialPort_Dma::Serial3);
}
// RX
void DMA1_Channel3_IRQHandler(void) {
    DMA::dma1->clearInterruptFlag(DMA::dma1->stream[2], DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->stream[2].disable();

    DMA_rx_function(SerialPort_Dma::Serial3, DMA::dma1->stream[2].getNumberOfItemsInTransfer());
}
// TX
void DMA1_Channel2_IRQHandler(void) {
    DMA::dma1->clearInterruptFlag(DMA::dma1->stream[1], DMA::Channel::Interrupt::TransferComplete);
    DMA::dma1->stream[1].disable();

    DMA_tx_function(SerialPort_Dma::Serial3);
}
#endif

}  // namespace stm32f3xx
}  // namespace microhal