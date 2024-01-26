/******************************************************************************
    sfeQwiicBuzzerRegisters.h

    by Pete Lewis @SparkFun Electronics
    January 2024

    Based on original source code written by
    Fischer Moseley @ SparkFun Electronics
    Original Creation Date: July 24, 2019

    This file defines the virtual memory map on the Qwiic Buzzer. The enum
    provides a set of pointers for the various registers on the Qwiic
    Buzzer.

    Development environment specifics:
    IDE: Arduino 2.2.1
    Hardware Platform: Arduino Uno/SparkFun Redboard
    Qwiic Buzzer Version: v10

    SPDX-License-Identifier: MIT

    Copyright (c) 2023 SparkFun Electronics

    Distributed as-is; no warranty is given.
******************************************************************************/

#pragma once

#include <stdint.h>

// Register Pointer Map
enum Qwiic_Buzzer_Register : uint8_t
{
    kSfeQwiicBuzzerRegId = 0x00,
    kSfeQwiicBuzzerRegFirmwareMinor,
    kSfeQwiicBuzzerRegFirmwareMajor,
    kSfeQwiicBuzzerRegToneFrequencyMsb,
    kSfeQwiicBuzzerRegToneFrequencyLsb,
    kSfeQwiicBuzzerRegVolume,
    kSfeQwiicBuzzerRegDurationMsb,
    kSfeQwiicBuzzerRegDurationLsb,
    kSfeQwiicBuzzerRegActive,
    kSfeQwiicBuzzerRegSaveSettings,
    kSfeQwiicBuzzerRegI2cAddress,
};