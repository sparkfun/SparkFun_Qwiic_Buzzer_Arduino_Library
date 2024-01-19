/******************************************************************************
    SparkFun_Qwiic_Buzzer_Arduino_Library.h
    SparkFun Qwiic Buzzer Library header file

    by Pete Lewis @SparkFun Electronics
    January 2024

    Based on original source code written by
        Fischer Moseley @ SparkFun Electronics
        Original Creation Date: July 24, 2019

    This file implements the QwiicBuzzer class, prototyped in SparkFun_Qwiic_Buzzer_Arduino_Library.h

    Development environment specifics:
    IDE: Arduino 2.2.1
    Hardware Platform: Arduino Uno/SparkFun Redboard
    Qwiic Buzzer Version: v10

    SPDX-License-Identifier: MIT

    Copyright (c) 2023 SparkFun Electronics

    Distributed as-is; no warranty is given.
******************************************************************************/

#pragma once

#include <SparkFun_Toolkit.h>
#include "sfeQwiicBuzzer.h"

class QwiicBuzzer : public sfeQwiicBuzzerArdI2C
{
    public:
        /// @brief Begins the Qwiic Buzzer
        /// @param address I2C device address to use for the sensor
        /// @param wirePort Wire port to use for I2C communication
        /// @return True if successful, false otherwise
        bool begin(uint8_t address = kQwiicBuzzerDefaultAddress, TwoWire &wirePort = Wire)
        {
            // Setup Arudino I2C bus
            _theI2CBus.init(wirePort, address);

            // Begin the sensor
            return sfeQwiicBuzzerArdI2C::begin(&_theI2CBus) == kSTkErrOk;
        }
        
        /// @brief Checks if the Qwiic Buzzer is connected
        /// @return True if the sensor is connected, false otherwise
        bool isConnected()
        {
            return sfeQwiicBuzzerArdI2C::isConnected() == kSTkErrOk;
        }

    private:
        sfeTkArdI2C _theI2CBus;
};
