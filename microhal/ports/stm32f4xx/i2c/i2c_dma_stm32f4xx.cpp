/* =========================================================================================== */ /**
 @file        i2cSTM32F4xx.cpp
 @authors     Pawel Okas
 @version     $Id$
 @package
 @brief       I2C implementation for STM32F4xx microcontroler
 @hardware    STM32F4xx
 @copyright   $Copyright$
 @details
 */ /* ============================================================================================
                                                                                                          */
/* ************************************************************************************************
 * INCLUDES
 */
#include "i2c_dma_stm32f4xx.h"

namespace microhal {
namespace stm32f4xx {
/* ************************************************************************************************
 *                                   STATIC VARIABLES
 * ***********************************************************************************************/
#ifdef MICROHAL_USE_I2C1_DMA
#if MICROHAL_I2C1_DMA_RX_STREAM != 0 && MICROHAL_I2C1_DMA_RX_STREAM != 5
#error I2C RX DMA channel can be confugured as 0 or 5 only
#endif
#if MICROHAL_I2C1_DMA_TX_STREAM != 6 && MICROHAL_I2C1_DMA_TX_STREAM != 7
#error I2C TX DMA channel can be confugured as 6 or 7 only
#endif
I2C_dma I2C_dma::i2c1(*I2C1, DMA::dma1->stream[MICROHAL_I2C1_DMA_RX_STREAM], DMA::dma1->stream[MICROHAL_I2C1_DMA_TX_STREAM]);
I2C &I2C::i2c1 = I2C_dma::i2c1;
#endif
#ifdef MICROHAL_USE_I2C2_DMA
#if MICROHAL_I2C2_DMA_RX_STREAM != 2 && MICROHAL_I2C2_DMA_RX_STREAM != 3
#error I2C RX DMA channel can be confugured as 2 or 3 only
#endif
I2C_dma I2C_dma::i2c2(*I2C2, DMA::dma1->stream[MICROHAL_I2C2_DMA_RX_STREAM], DMA::dma1->stream[7]);
I2C &I2C::i2c2 = I2C_dma::i2c2;
#endif
#ifdef MICROHAL_USE_I2C3_DMA
I2C_dma I2C_dma::i2c3(*I2C3, DMA::dma1->stream[2], DMA::dma1->stream[4]);
I2C &I2C::i2c3 = I2C_dma::i2c3;
#endif
/* ************************************************************************************************
 *                                   Functions prototypes
 * ***********************************************************************************************/
static DMA::Stream::Channel getChannalNumber(I2C_TypeDef &i2c);

/* ************************************************************************************************
 *                                  	 Constructors
 * ***********************************************************************************************/

/* ************************************************************************************************
 *                                 		  Functions
 * ***********************************************************************************************/
I2C::Error I2C_dma::write(DeviceAddress deviceAddress, const uint8_t * write_data, size_t write_data_size) {
    transfer.mode = Mode::Transmit;
    transfer.deviceAddress = deviceAddress;
    transfer.txLength = write_data_size;

    txStream.setNumberOfItemsToTransfer(write_data_size);
    txStream.setMemoryBank0(write_data);
    txStream.enable();

    errorSemaphore = UnknownError;

    while (i2c.SR1 & I2C_SR1_BTF) {
    }
    i2c.CR2 &= ~I2C_CR2_DMAEN & ~I2C_CR2_LAST;
    i2c.CR1 |= I2C_CR1_START;

    while (errorSemaphore == UnknownError) {
    }

    return errorSemaphore;
}

I2C::Error I2C_dma::write(DeviceAddress address, const void *dataA, size_t dataASize, const void *dataB, size_t dataBSize) noexcept {
	transfer.mode = Mode::Transmit;
	transfer.deviceAddress = address;
	transfer.txLength = dataASize;
	transfer.bufferB.ptr = const_cast<void*>(dataB);
	transfer.bufferB.length = dataBSize;

    txStream.setNumberOfItemsToTransfer(dataASize);
    txStream.setMemoryBank0(dataA);
//    txStream.setMemoryBank1(dataB);
    txStream.enable();

    errorSemaphore = UnknownError;

    while (i2c.SR1 & I2C_SR1_BTF) {
    }
    i2c.CR2 &= ~I2C_CR2_DMAEN & ~I2C_CR2_LAST;
    i2c.CR1 |= I2C_CR1_START;

    while (errorSemaphore == UnknownError) {
    }

    return errorSemaphore;
};
/**
 *
 * @param deviceAddress
 * @param registerAddress
 * @param data
 * @param length
 * @return
 */
I2C::Error I2C_dma::read(DeviceAddress deviceAddress, uint8_t * read_data, size_t read_data_size) {
    transfer.mode = Mode::Receive;
    transfer.deviceAddress = deviceAddress;
    transfer.rxLength = read_data_size;
    transfer.bufferB.length = read_data_size;

    rxStream.setNumberOfItemsToTransfer(read_data_size);
    rxStream.setMemoryBank0(read_data);
    txStream.disable();
    rxStream.enable();


    errorSemaphore = UnknownError;

//    while (i2c.SR1 & I2C_SR1_BTF) {
//    }
	//   i2c.CR1 |= I2C_CR1_ACK;
	//        i2c.CR2 |= I2C_CR2_DMAEN | I2C_CR2_LAST;
    i2c.CR2 &= ~I2C_CR2_DMAEN & ~I2C_CR2_LAST & ~I2C_CR2_ITBUFEN;
    i2c.CR1 |= I2C_CR1_START | I2C_CR1_ACK; // | I2C_CR1_PE;
    //i2c.CR1 |= I2C_CR1_ACK;
    i2c.CR2 |= I2C_CR2_DMAEN | I2C_CR2_LAST;

    while (errorSemaphore == UnknownError) {
    }

    return errorSemaphore;
}

I2C::Error I2C_dma::writeRead(DeviceAddress deviceAddress,
                              const void * write_data, size_t write_data_size,
                              void * read_data, size_t read_data_size) {
    transfer.mode = Mode::TransmitReceive;
    transfer.deviceAddress = deviceAddress;
    transfer.txLength = read_data_size;
    transfer.bufferB.length = read_data_size;

    txStream.setNumberOfItemsToTransfer(write_data_size);
    txStream.setMemoryBank0(write_data);
    txStream.enable();

    rxStream.setNumberOfItemsToTransfer(read_data_size);
    rxStream.setMemoryBank0(read_data);
//    rxStream.enable();

    errorSemaphore = UnknownError;

    while (i2c.SR1 & I2C_SR1_BTF) {
    }
    i2c.CR2 &= ~I2C_CR2_DMAEN & ~I2C_CR2_LAST;
    i2c.CR1 |= I2C_CR1_START;

    while (errorSemaphore == UnknownError) {
    }

    return errorSemaphore;
}

/**
 *
 */
void I2C_dma::init(void) {
	DMA::DMA &dma = *DMA::dma1;
    dma.clockEnable();

    // rx
    rxStream.deinit();
    rxStream.init(DMA::Stream::Channel::Channel7, DMA::Stream::MemoryBurst::SingleTransfer,
                DMA::Stream::PeripheralBurst::SingleTransfer,
                DMA::Stream::MemoryDataSize::Byte,
                DMA::Stream::PeripheralDataSize::Byte,
                DMA::Stream::MemoryIncrementMode::PointerIncremented,
                DMA::Stream::PeripheralIncrementMode::PointerFixed,
                DMA::Stream::TransmisionDirection::PerToMem);
    rxStream.setPeripheralAddress(&i2c.DR);
    rxStream.enableInterrupt(DMA::Stream::Interrupt::TransferComplete);

    // tx
    txStream.deinit();
    txStream.init(getChannalNumber(i2c), DMA::Stream::MemoryBurst::SingleTransfer,
                DMA::Stream::PeripheralBurst::SingleTransfer,
                DMA::Stream::MemoryDataSize::Byte,
                DMA::Stream::PeripheralDataSize::Byte,
                DMA::Stream::MemoryIncrementMode::PointerIncremented,
                DMA::Stream::PeripheralIncrementMode::PointerFixed,
                DMA::Stream::TransmisionDirection::MemToPer);
    txStream.setPeripheralAddress(&i2c.DR);
    txStream.enableInterrupt(DMA::Stream::Interrupt::TransferComplete);

//  IRQn_Type rxIRQ = DMA2_Stream0_IRQn, txIRQ = DMA2_Stream0_IRQn;
//  switch (reinterpret_cast<uint32_t>(&i2c)) {
//    case reinterpret_cast<uint32_t>(I2C1):
//#if MICROHAL_I2C1_DMA_RX_STREAM == 0
//      rxIRQ = DMA2_Stream0_IRQn;
//#elif MICROHAL_I2C1_DMA_RX_STREAM == 5
//      rxIRQ = DMA2_Stream5_IRQn;
//#endif
//#if MICROHAL_I2C1_DMA_TX_STREAM == 6
//      txIRQ = DMA2_Stream6_IRQn;
//#elif MICROHAL_I2C1_DMA_TX_STREAM == 7
//      txIRQ = DMA2_Stream7_IRQn;
//#endif
//      break;
//    case reinterpret_cast<uint32_t>(I2C2):
//#if MICROHAL_I2C2_DMA_RX_STREAM == 2
//      rxIRQ = DMA1_Stream2_IRQn;
//#elif MICROHAL_I2C2_DMA_RX_STREAM == 3
//      rxIRQ = DMA1_Stream3_IRQn;
//#endif
//      txIRQ = DMA1_Stream7_IRQn;
//      break;
//    case reinterpret_cast<uint32_t>(I2C3):
//      rxIRQ = DMA1_Stream2_IRQn;
//      txIRQ = DMA1_Stream4_IRQn;
//      break;
//  }

   // DMA::dma1->clearInterruptFlag(rxStream, DMA::Stream::Interrupt::TransferComplete);
   // NVIC_EnableIRQ(rxIRQ);
   // NVIC_SetPriority(rxIRQ, 0);

   // DMA::dma1->clearInterruptFlag(txStream, DMA::Stream::Interrupt::TransferComplete);
   // NVIC_EnableIRQ(txIRQ);
   // NVIC_SetPriority(txIRQ, 0);

    dma.clearInterruptFlag(txStream, DMA::Stream::Interrupt::TransferComplete);
    dma.clearInterruptFlag(rxStream, DMA::Stream::Interrupt::TransferComplete);
    dma.enableInterrupt(txStream, 6);
    dma.enableInterrupt(rxStream, 6);

    i2c.CR1 |= I2C_CR1_PE;
}
/**
 *
 * @param i2c
 * @return
 */
DMA::Stream::Channel getChannalNumber(I2C_TypeDef &i2c) {
    switch (reinterpret_cast<uint32_t>(&i2c)) {
        case reinterpret_cast<uint32_t>(I2C1):
            // in stream 0 and 5 the same channel
            return DMA::Stream::Channel::Channel1;
        case reinterpret_cast<uint32_t>(I2C2):
            // in stream 2 and 3 the same channel
            return DMA::Stream::Channel::Channel7;
        case reinterpret_cast<uint32_t>(I2C3):
            return DMA::Stream::Channel::Channel3;
    }
    // error
    while (1) {
    }
    // return for avoid warning
    return DMA::Stream::Channel::Channel0;
}
//***********************************************************************************************//
//                                     interrupt functions //
//***********************************************************************************************//
void I2C_dma::IRQFunction(I2C_dma &obj, I2C_TypeDef *i2c) {
    uint16_t sr1 = i2c->SR1;

    if (sr1 == I2C_SR1_SB) {  // sent start sequence
        i2c->DR = obj.transfer.deviceAddress | (static_cast<uint8_t>(obj.transfer.mode) & 0x01);
        i2c->CR1 |= I2C_CR1_ACK;
        i2c->CR2 |= I2C_CR2_DMAEN | I2C_CR2_LAST;
    } else if (sr1 & I2C_SR1_ADDR) {  // adres(MASTER MODE) was sent
    	 __attribute__((unused)) volatile uint16_t tmp =  i2c->SR2;  // to clear interrupt flag register SR2 read is necessarily


    	//i2c->CR1 |= I2C_CR1_ACK;
    	//i2c->CR2 |= I2C_CR2_DMAEN | I2C_CR2_LAST;
//      if (obj.transfer.mode == I2C_dma::Mode::Receive) {
//    	  if (obj.transfer.bufferB.length == 1) {
//    		  i2c->CR1 &= ~I2C_CR1_ACK;//(i2c->CR1 & (~I2C_CR1_ACK & ~I2C_CR1_POS));
//    	  } else {
//    		  i2c->CR1 |= I2C_CR1_ACK;// | I2C_CR1_POS;
//    		  //i2c->CR2 |= /*I2C_CR2_DMAEN |*/ I2C_CR2_LAST;
//    	  }
//      } else {
////    	  i2c->CR2 |= I2C_CR2_DMAEN;
//      }
      //__attribute__((unused)) volatile uint16_t tmp =  i2c->SR2;  // to clear interrupt flag register SR2 read is necessarily
    } else if (sr1 & (I2C_SR1_TXE | I2C_SR1_BTF)) {
        switch (obj.transfer.mode) {
            case I2C_dma::Mode::TransmitReceive:
            	i2c->CR2 &= ~I2C_CR2_DMAEN;
            	obj.transfer.mode = I2C_dma::Mode::Receive;
            	//obj.rxStream.enable();
                //if (obj.transfer.txLength == 1) {
                    //i2c->CR1 = /*(i2c->CR1 & (~I2C_CR1_ACK & ~I2C_CR1_POS)) | I2C_CR1_START;
                //} else {
                    i2c->CR1 |= /*I2C_CR1_ACK | I2C_CR1_POS | */I2C_CR1_START;
                //}
                break;
            case I2C_dma::Mode::Transmit:
                i2c->CR1 |= I2C_CR1_STOP;
                obj.errorSemaphore = I2C_dma::NoError;
                break;
        }
    }
}

void I2C_dma::IRQErrorFunction(I2C_dma &obj, I2C_TypeDef *i2c) {
    // Disable rx and tx DMA streams
    obj.rxStream.disable();
    obj.txStream.disable();
    // send stop signal to I2C data bus
    i2c->CR1 |= I2C_CR1_STOP;
    // read error and store it in variable
    obj.errorSemaphore = I2C::errorCheckAndClear(i2c, i2c->SR1);
}
//***********************************************************************************************//
//                                         DMA IRQHandlers //
//***********************************************************************************************//
#ifdef MICROHAL_USE_I2C1_DMA
//***********************************************************************************************//
#if MICROHAL_I2C1_DMA_RX_STREAM == 0
void DMA1_Stream0_IRQHandler(void) {
    // I2C rx
    I2C2->CR1 |= I2C_CR1_STOP;

    DMA1_Stream0->CR &= ~DMA_SxCR_EN;
    DMA1->LIFCR = DMA_LIFCR_CTCIF0;

    I2C_dma::i2c1.errorSemaphore = I2C_dma::NoError;
}
#endif
//***********************************************************************************************//
#if MICROHAL_I2C1_DMA_RX_STREAM == 5
void DMA1_Stream5_IRQHandler(void) {
    // I2C tx
    DMA1_Stream5->CR &= ~DMA_SxCR_EN;
    DMA1->HIFCR = DMA_LIFCR_HTCIF5;
}
#endif
//***********************************************************************************************//
#if MICROHAL_I2C1_DMA_TX_STREAM == 6
void DMA1_Stream6_IRQHandler(void) {
    // I2C rx
    DMA1_Stream6->CR &= ~DMA_SxCR_EN;
    DMA1->HIFCR = DMA_HIFCR_CTCIF6;

    I2C2->CR1 |= I2C_CR1_STOP;

    I2C_dma::i2c1.errorSemaphore = I2C_dma::NoError;
}
#endif
//***********************************************************************************************//
#if MICROHAL_I2C1_DMA_TX_STREAM == 6
void DMA1_Stream7_IRQHandler(void) {
    // I2C tx
    DMA1_Stream7->CR &= ~DMA_SxCR_EN;
    DMA1->HIFCR = DMA_LIFCR_HTCIF7;
}
#endif
#endif
#ifdef MICROHAL_USE_I2C2_DMA
//***********************************************************************************************//
#if MICROHAL_I2C2_DMA_RX_STREAM == 2
void DMA1_Stream2_IRQHandler(void) {
    I2C2->CR1 |= I2C_CR1_STOP;

    DMA1_Stream3->CR &= ~DMA_SxCR_EN;
    DMA1->LIFCR = DMA_LIFCR_CTCIF3;

    I2C_dma::i2c2.errorSemaphore = I2C_dma::NoError;
}
#endif
//***********************************************************************************************//
#if MICROHAL_I2C2_DMA_RX_STREAM == 3
void DMA1_Stream3_IRQHandler(void) {
	I2C2->CR1 |= I2C_CR1_STOP;

	DMA1_Stream3->CR &= ~DMA_SxCR_EN;
	DMA1->LIFCR = DMA_LIFCR_CTCIF3 | DMA_LIFCR_CTEIF3;

	I2C_dma::i2c2.errorSemaphore = I2C_dma::NoError;
}
#endif
//***********************************************************************************************//
void DMA1_Stream7_IRQHandler(void) { // tx
    DMA1_Stream7->CR &= ~DMA_SxCR_EN;
    DMA1->HIFCR = DMA_HIFCR_CTCIF7 | DMA_HIFCR_CTEIF7;
}
#endif
#ifdef MICROHAL_USE_I2C3_DMA
//***********************************************************************************************//
void DMA1_Stream2_IRQHandler(void) {
    // rx
    I2C2->CR1 |= I2C_CR1_STOP;

    DMA1_Stream2->CR &= ~DMA_SxCR_EN;
    DMA1->LIFCR = DMA_LIFCR_CTCIF2;

    I2C_dma::i2c3.errorSemaphore = I2C_dma::NoError;
}
//***********************************************************************************************//
void DMA1_Stream4_IRQHandler(void) {
    // tx
    DMA1_Stream4->CR &= ~DMA_SxCR_EN;
    DMA1->LIFCR = DMA_LIFCR_CTCIF4;
}
#endif
//***********************************************************************************************//
//                                          IRQHandlers //
//***********************************************************************************************//
#ifdef MICROHAL_USE_I2C1_DMA
void I2C2_EV_IRQHandler(void) {
    I2C_dma::IRQFunction(I2C_dma::i2c1, I2C1);
}
#endif
#ifdef MICROHAL_USE_I2C2_DMA
void I2C2_EV_IRQHandler(void) {
    I2C_dma::IRQFunction(I2C_dma::i2c2, I2C2);
}
#endif
#ifdef MICROHAL_USE_I2C3_DMA
void I2C3_EV_IRQHandler(void) {
    I2C_dma::IRQFunction(I2C_dma::i2c3, I2C3);
}
#endif
//***********************************************************************************************//
//                                       I2C error IRQHandlers //
//***********************************************************************************************//
#ifdef MICROHAL_USE_I2C1_DMA
void I2C1_ER_IRQHandler(void) {
    I2C_dma::IRQErrorFunction(I2C_dma::i2c1, I2C1);
}
#endif
#ifdef MICROHAL_USE_I2C2_DMA
void I2C2_ER_IRQHandler(void) {
    I2C_dma::IRQErrorFunction(I2C_dma::i2c2, I2C2);
}
#endif
#ifdef MICROHAL_USE_I2C3_DMA
void I2C3_ER_IRQHandler(void) {
    I2C_dma::IRQErrorFunction(I2C_dma::i2c3, I2C3);
}
#endif
}  // namespace stm32f4xx
}  // namespace microhal
