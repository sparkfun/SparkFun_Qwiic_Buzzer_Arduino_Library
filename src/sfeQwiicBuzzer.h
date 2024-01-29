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

#include "sfeQwiicBuzzerPitches.h"
#include "sfeQwiicBuzzerRegisters.h"
#include <SparkFun_Toolkit.h>
#include <stdint.h>

#define SFE_QWIIC_BUZZER_DEFAULT_ADDRESS 0x34
#define SFE_QWIIC_BUZZER_DEVICE_ID 0x5E
#define SFE_QWIIC_BUZZER_RESONANT_FREQUENCY 2730
#define SFE_QWIIC_BUZZER_VOLUME_OFF 0
#define SFE_QWIIC_BUZZER_VOLUME_MIN 1
#define SFE_QWIIC_BUZZER_VOLUME_LOW 2
#define SFE_QWIIC_BUZZER_VOLUME_MID 3
#define SFE_QWIIC_BUZZER_VOLUME_MAX 4

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

    /// @brief Reads the Device ID of the Qwiic Buzzer
    /// @param deviceId uint8_t variable where the read results will be stored
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t deviceId(uint8_t &deviceId);

    /// @brief Reads the Firmware Version Major of the Qwiic Buzzer
    /// @param versionMajor Variable where the read results will be stored
    /// @return 1 for succuss, 0 error
    bool firmwareVersionMajor(uint8_t &versionMajor);

    /// @brief Reads the Firmware Version Minor of the Qwiic Buzzer
    /// @param versionMinor Variable where the read results will be stored
    /// @return 1 for succuss, 0 error
    bool firmwareVersionMinor(uint8_t &versionMinor);

    /// @brief Configures the Qwiic Buzzer without causing the buzzer to buzz.
    /// This allows configuration in silence (before you may want to buzz).
    /// It is also useful in combination with saveSettings(), and then later
    /// causing buzzing by using the physical TRIGGER pin.
    /// To start buzzing (via Qwiic) with your desired configuration, use this
    /// function, then call on().
    /// @param toneFrequency Frequency in Hz of buzzer tone
    /// @param duration Duration in milliseconds (0 = forever)
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t configureBuzzer(const uint16_t toneFrequency = SFE_QWIIC_BUZZER_RESONANT_FREQUENCY,
                                 const uint16_t duration = 0, const uint8_t volume = 4);

    /// @brief Turns on buzzer
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t on();

    /// @brief Turns off buzzer
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t off();

    /// @brief Stores settings to EEPROM
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t saveSettings();

    /// @brief Changes the I2C address of the Qwiic Buzzer
    /// @param address New address, must be in the range 0x08 to 0x77
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t setAddress(const uint8_t &address);

    /// @brief Gets the current I2C address of the Qwiic Buzzer
    /// @return The current I2C address, 7-bit unshifted
    uint8_t address();

    /// @brief Plays one of the sound effects included in this library
    /// @param soundEffectNumber The sound effect you with to play
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 1 for succuss, 0 error
    bool playSoundEffect(const uint8_t soundEffectNumber, const uint8_t volume);

  private:
    /// @brief Plays sound effect 0 (aka "Siren")
    /// Intended to sound like a siren, starting at a low frequency, and then
    /// increasing rapidly up and then back down. This sound effect does a
    /// single "up and down" cycle.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect0(const uint8_t volume);

    /// @brief Plays sound effect 1 (aka "3 Fast Sirens")
    /// Intended to sound like a siren, starting at a low frequency, and then
    /// increasing rapidly up and then back down. This sound effect does this
    /// cycle of "up and down" three times rapidly.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect1(const uint8_t volume);

    /// @brief Plays sound effect 2 (aka "robot saying 'Yes'")
    /// Intended to sound like a robot saying the word "yes".
    /// It starts at a low frequency and quickly ramps up to a high frequency,
    /// then stops. This can be interpreted by most to be an affirmative
    /// sound to any question you may ask your buzzing robot.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect2(const uint8_t volume);

    /// @brief Plays sound effect 3 (aka "robot yelling 'YES!'" - faster)
    /// Intended to sound like a robot saying the word "yes".
    /// It starts at a low frequency and quickly ramps up to a high frequency,
    /// then stops. This can be interpreted by most to be an affirmative
    /// sound to any question you may ask your buzzing robot. As this sound
    /// is done more quickly, it can add enthusiasm to the buzzing sound.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect3(const uint8_t volume);

    /// @brief Plays sound effect 4 (aka "robot saying 'No'")
    /// Intended to sound like a robot saying the word "no".
    /// It starts at a high frequency and quickly ramps down to a low frequency,
    /// then stops. This can be interpreted by most to be an negative
    /// sound to any question you may ask your buzzing robot.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect4(const uint8_t volume);

    /// @brief Plays sound effect 5 (aka "robot yelling 'NO!'" - faster)
    /// Intended to sound like a robot saying the word "no".
    /// It starts at a high frequency and quickly ramps down to a low frequency,
    /// then stops. This can be interpreted by most to be an negative
    /// sound to any question you may ask your buzzing robot. As this sound
    /// is done more quickly, it can add enthusiasm to the buzzing sound.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect5(const uint8_t volume);

    /// @brief Plays sound effect 6 (aka "Laughing Robot")
    /// Intended to sound like your robot is laughing at you.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect6(const uint8_t volume);

    /// @brief Plays sound effect 7 (aka "Laughing Robot Faster")
    /// Intended to sound like your robot is laughing at you. As this sound
    /// is done more quickly, it can add enthusiasm to the buzzing sound.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect7(const uint8_t volume);

    /// @brief Plays sound effect 8 (aka "Crying Robot")
    /// Intended to sound like a robot is crying and sad.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect8(const uint8_t volume);

    /// @brief Plays sound effect 9 (aka "Crying Robot Faster")
    /// Intended to sound like a robot is crying and sad. As this sound
    /// is done more quickly, it can add enthusiasm to the buzzing sound.
    /// @param volume Volume (4 settings; 0=off, 1=quiet... 4=loudest)
    /// @return 0 for succuss, negative for errors, positive for warnings
    sfeTkError_t soundEffect9(const uint8_t volume);

  protected:
    sfeTkII2C *_theBus;
};