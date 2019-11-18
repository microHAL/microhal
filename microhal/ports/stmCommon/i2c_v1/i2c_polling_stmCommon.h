/*
 * i2c_pulling_stm32f4xx.h
 *
 *  Created on: 17 kwi 2014
 *      Author: pawel
 */

#ifndef _MICROHAL_I2C_POLLING_STM32F4XX_H_
#define _MICROHAL_I2C_POLLING_STM32F4XX_H_
/* ************************************************************************************************
 * INCLUDES
 */
#include <cstdint>
#include "../clockManager/i2cClock.h"
#include "i2c_stmCommon.h"

namespace microhal {
namespace _MICROHAL_ACTIVE_PORT_NAMESPACE {
/* ************************************************************************************************
 * CLASS
 */
class I2C_polling : public _MICROHAL_ACTIVE_PORT_NAMESPACE::I2C {
 public:
//---------------------------------------- variables ----------------------------------------//
#ifdef MICROHAL_USE_I2C1_POLLING
    static I2C_polling i2c1;
#endif
#ifdef MICROHAL_USE_I2C2_POLLING
    static I2C_polling i2c2;
#endif
#ifdef MICROHAL_USE_I2C3_POLLING
    static I2C_polling i2c3;
#endif
 private:
    //---------------------------------------- constructors ---------------------------------------
    I2C_polling(registers::I2C *i2c) : I2C(i2c) { ClockManager::enableI2C(getI2CNumber(), ClockManager::PowerMode::Normal); }
    //---------------------------------------- functions ----------------------------------------//
    Error writeRead(DeviceAddress address, const uint8_t *write, size_t write_size, uint8_t *read, size_t read_size) noexcept final;

    Error write(DeviceAddress deviceAddress, const uint8_t *write, size_t write_size) noexcept final;
    Error write(DeviceAddress deviceAddress, const uint8_t *write_data, size_t write_data_size, const uint8_t *write_dataB,
                size_t write_data_sizeB) noexcept final;

    Error read(DeviceAddress deviceAddress, uint8_t *data, size_t dataLength) noexcept final {
        return read_implementation(deviceAddress, nullptr, 0, data, dataLength);
    }
    Error read(DeviceAddress deviceAddress, uint8_t *data, size_t dataLength, uint8_t *dataB, size_t dataBLength) noexcept final {
        return read_implementation(deviceAddress, data, dataLength, dataB, dataBLength);
    }

    inline Error write(uint8_t data);
    Error write_implementation(DeviceAddress deviceAddress, const void *write_data, size_t write_data_size, const void *write_dataB,
                               size_t write_data_sizeB);
    Error read_implementation(DeviceAddress deviceAddress, uint8_t *data, size_t dataLength, uint8_t *dataB, size_t dataBLength) noexcept;
};

}  // namespace _MICROHAL_ACTIVE_PORT_NAMESPACE
}  // namespace microhal

#endif  // _MICROHAL_I2C_POLLING_STM32F4XX_H_
