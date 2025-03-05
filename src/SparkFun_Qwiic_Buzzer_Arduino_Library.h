/**
 * @file    SparkFun_Qwiic_Buzzer_Arduino_Library.h
 * @brief   SparkFun Qwiic Buzzer Library header file
 * @author  Pete Lewis \@SparkFun Electronics
 * @date    January 2024
 *
 * @note    Based on original source code written by Fischer Moseley \@ SparkFun Electronics
 *          Original Creation Date: July 24, 2019
 *
 * @details This file implements the QwiicBuzzer class, prototyped in SparkFun_Qwiic_Buzzer_Arduino_Library.h
 *
 * @copyright Copyright (c) 2024 SparkFun Electronics. This project is released under the MIT License.
 * @license   SPDX-License-Identifier: MIT
 *
 */

#pragma once

// clang-format off
#include <SparkFun_Toolkit.h>
#include "sfTk/sfDevBuzzer.h"
// clang-format on
class QwiicBuzzer : public sfDevBuzzer
{
  public:
    /// @brief Begins the Qwiic Buzzer
    /// @param address I2C device address to use for the sensor
    /// @param wirePort Wire port to use for I2C communication
    /// @return True if successful, false otherwise
    bool begin(const uint8_t address = SFE_QWIIC_BUZZER_DEFAULT_ADDRESS, TwoWire &wirePort = Wire)
    {
        // Setup Arudino I2C bus
        _theI2CBus.init(wirePort, address);

        // Begin the sensor
        return sfDevBuzzer::begin(&_theI2CBus) == ksfTkErrOk;
    }

    /// @brief Checks if the Qwiic Buzzer is connected
    /// @return True if the sensor is connected, false otherwise
    bool isConnected()
    {
        return sfDevBuzzer::isConnected() == ksfTkErrOk;
    }

  private:
    sfTkArdI2C _theI2CBus;
};
