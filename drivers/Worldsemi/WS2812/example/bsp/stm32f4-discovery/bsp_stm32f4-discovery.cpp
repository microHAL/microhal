/*
 * stm32f4_discovery.cpp
 *
 *  Created on: 16 kwi 2014
 *      Author: pawel
 */
#include "microhal.h"
#include "bsp.h"
#include "SPIDevice/SPIDevice.h"

using namespace microhal;
using namespace stm32f4xx;
using namespace diagnostic;

void hardwareConfig(void) {
	(void)bsp::wsSpi;
    Core::pll_start(8000000, 102400000);
    Core::fpu_enable();

    IOManager::routeSerial<3, Txd, stm32f4xx::GPIO::PortD, 8>();
    IOManager::routeSerial<3, Rxd, stm32f4xx::GPIO::PortD, 9>();

    bsp::debugPort.setDataBits(stm32f4xx::SerialPort::Data8);
    bsp::debugPort.setStopBits(stm32f4xx::SerialPort::OneStop);
    bsp::debugPort.setParity(stm32f4xx::SerialPort::NoParity);
    bsp::debugPort.open(stm32f4xx::SerialPort::ReadWrite);
    bsp::debugPort.setBaudRate(stm32f4xx::SerialPort::Baud115200);
    diagChannel.setOutputDevice(bsp::debugPort);


//    IOManager::routeSPI<Spi1, SCK, stm32f4xx::GPIO::PortA, 5>();
//    IOManager::routeSPI<Spi1, MISO, stm32f4xx::GPIO::PortA, 6>();
    IOManager::routeSPI<1, MOSI, stm32f4xx::GPIO::PortA, 7>();

    stm32f4xx::SPI::spi1.init(stm32f4xx::SPI::Mode1, stm32f4xx::SPI::PRESCALER_8);
    stm32f4xx::SPI::spi1.enable();

    diagChannel << Notice << "SPI frequency: " << stm32f4xx::SPI::spi1.frequency() << endl;

    SysTick_Config(102400000/1000);
}

uint64_t SysTick_time = 0;

extern "C" void SysTick_Handler(void) {
	SysTick_time++;
}
