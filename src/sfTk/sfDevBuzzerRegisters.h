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

const uint8_t kSfeQwiicBuzzerRegId = 0x00;
const uint8_t kSfeQwiicBuzzerRegFirmwareMinor = 0x01;
const uint8_t kSfeQwiicBuzzerRegFirmwareMajor = 0x02;
const uint8_t kSfeQwiicBuzzerRegToneFrequencyMsb = 0x03;
const uint8_t kSfeQwiicBuzzerRegToneFrequencyLsb = 0x04;
const uint8_t kSfeQwiicBuzzerRegVolume = 0x05;
const uint8_t kSfeQwiicBuzzerRegDurationMsb = 0x06;
const uint8_t kSfeQwiicBuzzerRegDurationLsb = 0x07;
const uint8_t kSfeQwiicBuzzerRegActive = 0x08;
const uint8_t kSfeQwiicBuzzerRegSaveSettings = 0x09;
const uint8_t kSfeQwiicBuzzerRegI2cAddress = 0x0A;
