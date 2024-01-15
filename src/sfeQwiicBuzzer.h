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

This code is Lemonadeware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#pragma once

#include "SparkFun_Toolkit.h"
#include <stdint.h>

const uint8_t kQwiicBuzzerDefaultAddress = 0x34;

class sfeQwiicBuzzer
{
  public:
    /// @brief Default constructor
    sfeQwiicBuzzer() : _theBus(nullptr)
    {
    }

    /// @brief Begins the Qwiic Buzzer
    /// @param theBus I2C bus to use for communication
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t begin(sfeTkII2C *theBus = nullptr);

    /// @brief Checks if the Qwiic Buzzer is connected
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t isConnected();

    /// @brief Configures the Qwiic Buzzer
    /// @param toneFrequency Frequency of buzzer tone
    /// @param duration Duration in milliseconds
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t buzzerConfig(uint16_t toneFrequency, uint16_t duration, uint8_t volume);
    
    /// @brief Configures the Qwiic Buzzer with default values
    /// @param toneFrequency Frequency of buzzer tone
    /// @param duration Duration in milliseconds
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t on(uint16_t toneFrequency = 2730, uint16_t duration = 0, uint8_t volume = 4);

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

    /// @brief Plays one of the sound effects included in this library
    /// @param soundEffectNumber The sound effect you with to play
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void playSoundEffect(uint8_t soundEffectNumber, uint8_t volume);

    /// @brief Plays sound effect 0
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect0(uint8_t volume);

    /// @brief Plays sound effect 1
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect1(uint8_t volume);

    /// @brief Plays sound effect 2
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect2(uint8_t volume);

    /// @brief Plays sound effect 3
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect3(uint8_t volume);

    /// @brief Plays sound effect 4
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect4(uint8_t volume);

    /// @brief Plays sound effect 5
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect5(uint8_t volume);

    /// @brief Plays sound effect 6
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect6(uint8_t volume);

    /// @brief Plays sound effect 7
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect7(uint8_t volume);

    /// @brief Plays sound effect 8
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect8(uint8_t volume);

    /// @brief Plays sound effect 9
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    void soundEffect9(uint8_t volume);    

    /// @brief Changes the I2C address of the Qwiic Buzzer
    /// @param address New address, must be in the range 0x20 to 0x2F
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t changeAddress(const uint8_t &address);

    /// @brief Gets the current I2C address of the Qwiic Buzzer
    /// @return The current I2C address, 7-bit unshifted
    uint8_t getAddress();

  protected:
    sfeTkII2C *_theBus;
};