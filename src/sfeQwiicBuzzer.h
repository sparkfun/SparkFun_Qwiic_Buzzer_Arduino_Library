/******************************************************************************
    sfeQwiicBuzzer.h
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
#include <stdint.h>
#include <Arduino.h>
#include "sfeQwiicBuzzerRegisters.h"
#include "sfeQwiicBuzzerPitches.h"

const uint8_t kSfeQwiicBuzzerDefaultAddress = 0x34;
const uint16_t kSfeQwiicBuzzerResonantFrequency = 2730;
#define SFE_QWIIC_BUZZER_VOLUME_OFF = 0;
#define SFE_QWIIC_BUZZER_VOLUME_MIN = 1;
#define SFE_QWIIC_BUZZER_VOLUME_LOW = 2;
#define SFE_QWIIC_BUZZER_VOLUME_MID = 3;
#define SFE_QWIIC_BUZZER_VOLUME_MAX = 4;

class sfeQwiicBuzzer
{
    public:
        /// @brief Default constructor
        sfeQwiicBuzzer() : _theBus{nullptr}
        {
        }

        /// @brief Begins the Qwiic Buzzer
        /// @param theBus I2C bus to use for communication
        /// @return 0 for succuss, negative for errors, positive for warnings
        sfeTkError_t begin(sfeTkII2C *theBus = nullptr);

        /// @brief Checks if the Qwiic Buzzer is connected
        /// @return 0 for succuss, negative for errors, positive for warnings
        sfeTkError_t isConnected();

        /// @brief Configures the Qwiic Buzzer without causing the buzzer to buzz.
        /// This allows configuration in silence (before you may want to buzz).
        /// It is also useful in combination with saveSettings(), and then later 
        /// causing buzzing by using the physical TRIGGER pin.
        /// To start buzzing (via Qwiic) with your desired configuration, use this
        /// function, then call setBuzzerActiveReg().
        /// @param toneFrequency Frequency in Hz of buzzer tone
        /// @param duration Duration in milliseconds
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings
        sfeTkError_t configureBuzzer(const uint16_t toneFrequency, const uint16_t duration, const uint8_t volume);
        
        /// @brief Configures the Qwiic Buzzer with default values
        /// @param toneFrequency Frequency in Hz of buzzer tone
        /// @param duration Duration in milliseconds
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings
        sfeTkError_t on(const uint16_t toneFrequency = kSfeQwiicBuzzerResonantFrequency, const uint16_t duration = 0, const uint8_t volume = 4);

        /// @brief Turns off buzzer
        /// @return 0 for succuss, negative for errors, positive for warnings
        sfeTkError_t off();

        /// @brief Stores settings to EEPROM
        /// @return 0 for succuss, negative for errors, positive for warnings
        sfeTkError_t saveSettings();

        /// @brief Sets register to "command" Buzzer to buzz
        /// @return 0 for succuss, negative for errors, positive for warnings    
        sfeTkError_t setBuzzerActiveReg();

        /// @brief Clears register to "command" Buzzer to stop buzzing
        /// @return 0 for succuss, negative for errors, positive for warnings    
        sfeTkError_t clearBuzzerActiveReg();    

        /// @brief Changes the I2C address of the Qwiic Buzzer
        /// @param address New address, must be in the range 0x08 to 0x77
        /// @return 0 for succuss, negative for errors, positive for warnings
        sfeTkError_t setAddress(const uint8_t &address);

        /// @brief Gets the current I2C address of the Qwiic Buzzer
        /// @return The current I2C address, 7-bit unshifted
        uint8_t getAddress();

        /// @brief Plays one of the sound effects included in this library
        /// @param soundEffectNumber The sound effect you with to play
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t playSoundEffect(const uint8_t &soundEffectNumber, const uint8_t &volume);

    private:
        /// @brief Plays sound effect 0
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect0(const uint8_t &volume);

        /// @brief Plays sound effect 1
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect1(const uint8_t &volume);

        /// @brief Plays sound effect 2
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect2(const uint8_t &volume);

        /// @brief Plays sound effect 3
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect3(const uint8_t &volume);

        /// @brief Plays sound effect 4
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect4(const uint8_t &volume);

        /// @brief Plays sound effect 5
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect5(const uint8_t &volume);

        /// @brief Plays sound effect 6
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect6(const uint8_t &volume);

        /// @brief Plays sound effect 7
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect7(const uint8_t &volume);

        /// @brief Plays sound effect 8
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect8(const uint8_t &volume);

        /// @brief Plays sound effect 9
        /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
        /// @return 0 for succuss, negative for errors, positive for warnings        
        sfeTkError_t soundEffect9(const uint8_t &volume);    

    protected:
        sfeTkII2C *_theBus;
};