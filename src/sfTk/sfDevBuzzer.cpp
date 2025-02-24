/**
 * @file    sfDevBuzzer.cpp
 * @brief   Implementation file for SparkFun Qwiic Buzzer Library
 * @author  Pete Lewis \@SparkFun Electronics
 * @date    January 2024
 *
 * @note    Based on original source code by Fischer Moseley @ SparkFun Electronics
 *          Original Creation Date: July 24, 2019
 *
 * @details This file contains the implementation of the sfDevBuzzer class, which
 *          provides control functionality for the SparkFun Qwiic Buzzer hardware.
 *
 * @copyright Copyright (c) 2023-2025 SparkFun Electronics. This project is released under the MIT License.
 * @license   SPDX-License-Identifier: MIT
 *
 * Distributed as-is; no warranty is given.
 */

#include "sfDevBuzzer.h"

sfTkError_t sfDevBuzzer::begin(sfTkII2C *theBus)
{
    // Nullptr check
    if (theBus == nullptr)
        return ksfTkErrFail;

    // Set bus pointer
    _theBus = theBus;

    sfTkError_t err;
    err = isConnected();
    // Check whether the ping was successful
    if (err != ksfTkErrOk)
        return err;

    uint8_t readDeviceId;
    err = deviceId(readDeviceId);
    // Check whether the read was successful
    if (err != ksfTkErrOk)
        return err;

    // check that device ID matches
    if (readDeviceId != SFE_QWIIC_BUZZER_DEVICE_ID)
        return ksfTkErrFail;

    // Done!
    return ksfTkErrOk;
}

sfTkError_t sfDevBuzzer::isConnected()
{
    // Just ping the device address
    return _theBus->ping();
}

sfTkError_t sfDevBuzzer::deviceId(uint8_t &deviceId)
{
    return _theBus->readRegister(kSfeQwiicBuzzerRegId, deviceId);
}

bool sfDevBuzzer::firmwareVersionMajor(uint8_t &versionMajor)
{
    sfTkError_t err;
    err = _theBus->readRegister(kSfeQwiicBuzzerRegFirmwareMajor, versionMajor);
    if (err == ksfTkErrOk)
        return true;
    else
        return false;
}

bool sfDevBuzzer::firmwareVersionMinor(uint8_t &versionMinor)
{
    sfTkError_t err;
    err = _theBus->readRegister(kSfeQwiicBuzzerRegFirmwareMinor, versionMinor);
    if (err == ksfTkErrOk)
        return true;
    else
        return false;
}

sfTkError_t sfDevBuzzer::configureBuzzer(const uint16_t toneFrequency, const uint16_t duration, const uint8_t volume)
{
    // All of the necessary configuration register addresses are in sequential order,
    // starting at "kSfeQwiicBuzzerRegToneFrequencyMsb".
    // We can write all of them in a single use of "writeRegisterRegion()".

    // kSfeQwiicBuzzerRegToneFrequencyMsb = 0x03,
    // kSfeQwiicBuzzerRegToneFrequencyLsb = 0x04,
    // kSfeQwiicBuzzerRegVolume = 0x05,
    // kSfeQwiicBuzzerRegDurationMsb = 0x06,
    // kSfeQwiicBuzzerRegDurationLsb = 0x07,

    // extract MSBs and LSBs from user passed in arguments
    uint8_t toneFrequencyMSB = ((toneFrequency & 0xFF00) >> 8);
    uint8_t toneFrequencyLSB = (toneFrequency & 0x00FF);
    uint8_t durationMSB = ((duration & 0xFF00) >> 8);
    uint8_t durationLSB = (duration & 0x00FF);

    size_t dataLength = 5;
    uint8_t data[dataLength];

    data[0] = toneFrequencyMSB; // kSfeQwiicBuzzerRegToneFrequencyMsb
    data[1] = toneFrequencyLSB; // kSfeQwiicBuzzerRegToneFrequencyLsb
    data[2] = volume;           // kSfeQwiicBuzzerRegVolume
    data[3] = durationMSB;      // kSfeQwiicBuzzerRegDurationMsb
    data[4] = durationLSB;      // kSfeQwiicBuzzerRegDurationLsb

    return _theBus->writeRegister(kSfeQwiicBuzzerRegToneFrequencyMsb, data, dataLength);
}

sfTkError_t sfDevBuzzer::on()
{
    return _theBus->writeRegisterUInt8(kSfeQwiicBuzzerRegActive, 1);
}

sfTkError_t sfDevBuzzer::off()
{
    return _theBus->writeRegisterUInt8(kSfeQwiicBuzzerRegActive, 0);
}

sfTkError_t sfDevBuzzer::saveSettings()
{
    return _theBus->writeRegisterUInt8(kSfeQwiicBuzzerRegSaveSettings, 1);
}

sfTkError_t sfDevBuzzer::setAddress(const uint8_t &address)
{
    if (address < 0x08 || address > 0x77)
    {
        return ksfTkErrFail; // error immediately if the address is out of legal range
    }

    sfTkError_t err = _theBus->writeRegister(kSfeQwiicBuzzerRegI2cAddress, address);

    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;

    // Update the address in the bus
    _theBus->setAddress(address);

    // Done!
    return ksfTkErrOk;
}

uint8_t sfDevBuzzer::address()
{
    return _theBus->address();
}

bool sfDevBuzzer::playSoundEffect(const uint8_t soundEffectNumber, const uint8_t volume)
{
    sfTkError_t err;

    switch (soundEffectNumber)
    {
    case 0:
        err = soundEffect0(volume);
        break;
    case 1:
        err = soundEffect1(volume);
        break;
    case 2:
        err = soundEffect2(volume);
        break;
    case 3:
        err = soundEffect3(volume);
        break;
    case 4:
        err = soundEffect4(volume);
        break;
    case 5:
        err = soundEffect5(volume);
        break;
    case 6:
        err = soundEffect6(volume);
        break;
    case 7:
        err = soundEffect7(volume);
        break;
    case 8:
        err = soundEffect8(volume);
        break;
    case 9:
        err = soundEffect9(volume);
        break;
    default:
        err = ksfTkErrFail;
    }

    if (err == ksfTkErrOk)
        return true;
    else
        return false;
}

sfTkError_t sfDevBuzzer::soundEffect0(const uint8_t volume)
{
    sfTkError_t err;
    for (int note = 150; note < 4000; note += 150)
    {
        err = configureBuzzer(note, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    for (int note = 4000; note > 150; note -= 150)
    {
        err = configureBuzzer(note, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect1(const uint8_t volume)
{
    sfTkError_t err;
    for (int i = 0; i <= 2; i++)
    {
        for (int note = 150; note < 4000; note += 150)
        {
            err = configureBuzzer(note, 0, volume);
            // Check whether the write was successful
            if (err != ksfTkErrOk)
                return err;

            err = on();
            // Check whether the write was successful
            if (err != ksfTkErrOk)
                return err;

            sftk_delay_ms(2);
        }
        for (int note = 4000; note > 150; note -= 150)
        {
            err = configureBuzzer(note, 0, volume);
            // Check whether the write was successful
            if (err != ksfTkErrOk)
                return err;

            err = on();
            // Check whether the write was successful
            if (err != ksfTkErrOk)
                return err;

            sftk_delay_ms(2);
        }
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect2(const uint8_t volume)
{
    sfTkError_t err;
    for (int note = 150; note < 4000; note += 150)
    {
        err = configureBuzzer(note, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(40);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect3(const uint8_t volume)
{
    sfTkError_t err;
    for (int note = 150; note < 4000; note += 150)
    {
        err = configureBuzzer(note, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect4(const uint8_t volume)
{
    sfTkError_t err;
    for (int note = 4000; note > 150; note -= 150)
    {
        err = configureBuzzer(note, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(40);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect5(const uint8_t volume)
{
    sfTkError_t err;
    for (int note = 4000; note > 150; note -= 150)
    {
        err = configureBuzzer(note, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect6(const uint8_t volume)
{
    sfTkError_t err;
    int laughdelay = 400;
    int laughstep = 10;
    uint16_t i;

    for (i = 1538; i < 1905; i += laughstep) // vary up //1538, 1905
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;

    sftk_delay_ms(laughdelay);

    for (i = 1250; i < 1515; i += laughstep) // 1250, 1515
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(laughdelay);

    for (i = 1111; i < 1342; i += laughstep) // 1111, 1342
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(laughdelay);

    for (i = 1010; i < 1176; i += laughstep) // 1010, 1176
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect7(const uint8_t volume)
{
    sfTkError_t err;
    int laughdelay = 200;
    int laughstep = 15;
    uint16_t i;

    for (i = 1538; i < 1905; i += laughstep) // vary up //1538, 1905
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(laughdelay);

    for (i = 1250; i < 1515; i += laughstep) // 1250, 1515
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(laughdelay);

    for (i = 1111; i < 1342; i += laughstep) // 1111, 1342
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(laughdelay);

    for (i = 1010; i < 1176; i += laughstep) // 1010, 1176
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect8(const uint8_t volume)
{
    sfTkError_t err;
    int crydelay = 500;
    int step = 10;
    uint16_t i;

    for (i = 2000; i > 1429; i -= step) // vary down //2000, 1429
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(crydelay);

    for (i = 1667; i > 1250; i -= step) // 1667, 1250
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(crydelay);

    for (i = 1429; i > 1053; i -= step) // 1429, 1053
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    return off();
}

sfTkError_t sfDevBuzzer::soundEffect9(const uint8_t volume)
{
    sfTkError_t err;
    int crydelay = 200;
    int step = 20;
    uint16_t i;

    for (i = 2000; i > 1429; i -= step) // vary down //2000, 1429
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;

    sftk_delay_ms(crydelay);

    for (i = 1667; i > 1250; i -= step) // 1667, 1250
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    err = off();
    // Check whether the write was successful
    if (err != ksfTkErrOk)
        return err;
    sftk_delay_ms(crydelay);

    for (i = 1429; i > 1053; i -= step) // 1429, 1053
    {
        err = configureBuzzer(i, 0, volume);
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        err = on();
        // Check whether the write was successful
        if (err != ksfTkErrOk)
            return err;

        sftk_delay_ms(10);
    }
    return off();
}