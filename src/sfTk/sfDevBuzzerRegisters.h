/**
 * @file    sfDevBuzzerRegisters.h
 * @brief   Header file defining the virtual memory map for the Qwiic Buzzer
 * @author  Pete Lewis \@SparkFun Electronics
 * @date    January 2024
 *
 * @note    Based on original source code written by Fischer Moseley \@ SparkFun Electronics
 *          Original Creation Date: July 24, 2019
 *
 * @details This file defines the virtual memory map on the Qwiic Buzzer. The enum
 *          provides a set of pointers for the various registers on the Qwiic Buzzer.
 *
 *
 * @copyright Copyright (c) 2023 SparkFun Electronics. This project is released under the MIT License.
 * @license   SPDX-License-Identifier: MIT
 *
 */

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