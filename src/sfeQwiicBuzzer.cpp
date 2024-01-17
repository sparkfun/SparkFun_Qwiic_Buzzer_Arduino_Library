/******************************************************************************
    sfeQwiicBuzzer.h
    SparkFun Qwiic Buzzer Library header file

    by Pete Lewis @SparkFun Electronics
    January 2024

    Based on original source code written by
    Fischer Moseley @ SparkFun Electronics
    Original Creation Date: July 24, 2019

    Development environment specifics:
    IDE: Arduino 2.2.1
    Hardware Platform: Arduino Uno/SparkFun Redboard
    Qwiic Buzzer Version: v10

    SPDX-License-Identifier: MIT

    Copyright (c) 2023 SparkFun Electronics

    Distributed as-is; no warranty is given.
******************************************************************************/

#include "sfeQwiicBuzzer.h"

sfeTkError_t sfeQwiicBuzzerArdI2C::begin(sfeTkII2C *theBus)
{
    // Nullptr check
    if (theBus == nullptr)
        return kSTkErrFail;

    // Set bus pointer
    _theBus = theBus;

    // Just check if the device is connected, no other setup is needed
    return isConnected();
}

sfeTkError_t sfeQwiicBuzzerArdI2C::isConnected()
{
    // Just ping the device address
    return _theBus->ping();
}

sfeTkError_t sfeQwiicBuzzerArdI2C::changeAddress(const uint8_t &address)
{
    if (address < 0x08 || address > 0x77)
    {
        Serial.println("Address out of legal range");
        return kSTkErrFail; //error immediately if the address is out of legal range
    }

    sfeTkError_t err = _theBus->writeRegisterByte(kSfeQwiicBuzzerRegI2cAddress, address);

    // Check whether the write was successful
    if (err != kSTkErrOk)
        return err;

    // Update the address in the bus
    _theBus->setAddress(address);

    // Done!
    return kSTkErrOk;
}

uint8_t sfeQwiicBuzzerArdI2C::getAddress()
{
    return _theBus->address();
}

sfeTkError_t sfeQwiicBuzzerArdI2C::buzzerConfig(uint16_t toneFrequency, uint16_t duration, uint8_t volume)
{
    // All of the necessary configuration register address are in sequencial order
    // starting at "kSfeQwiicBuzzerRegToneFrequencyMsb":
    // We can write all of them in a single use of "writeRegisterRegion()".

    // kSfeQwiicBuzzerRegToneFrequencyMsb = 0x03,   
    // kSfeQwiicBuzzerRegToneFrequencyLsb = 0x04,       
    // kSfeQwiicBuzzerRegVolume = 0x05, 
    // kSfeQwiicBuzzerRegDurationMsb = 0x06, 
    // kSfeQwiicBuzzerRegDurationLsb = 0x07, 
    // kSfeQwiicBuzzerRegActive = 0x08, 

    // extract MSBs and LSBs from user passed in arguments
    uint8_t toneFrequencyMSB = ((toneFrequency & 0xFF00) >> 8 );
    uint8_t toneFrequencyLSB = (toneFrequency & 0x00FF);
    uint8_t durationMSB = ((duration & 0xFF00) >> 8 );
    uint8_t durationLSB = (duration & 0x00FF);

    uint8_t data[5];
    size_t dataLength = 5;

    data[0] = toneFrequencyMSB; // kSfeQwiicBuzzerRegToneFrequencyMsb
    data[1] = toneFrequencyLSB; // kSfeQwiicBuzzerRegToneFrequencyLsb
    data[2] = volume; // kSfeQwiicBuzzerRegVolume
    data[3] = durationMSB; // kSfeQwiicBuzzerRegDurationMsb
    data[4] = durationLSB; // kSfeQwiicBuzzerRegDurationLsb

    sfeTkError_t err = _theBus->writeRegisterRegion(kSfeQwiicBuzzerRegToneFrequencyMsb, data, dataLength);
    if (err != kSTkErrOk) // Check whether the write was successful
        return err;

    // Done!
    return kSTkErrOk;  
}

sfeTkError_t sfeQwiicBuzzerArdI2C::setBuzzerActiveReg()
{
    sfeTkError_t err = _theBus->writeRegisterByte(kSfeQwiicBuzzerRegActive, 0x01);
    if (err != kSTkErrOk) // Check whether the write was successful
        return err;
    
    // Done!
    return kSTkErrOk;    
}

sfeTkError_t sfeQwiicBuzzerArdI2C::clearBuzzerActiveReg()
{
    sfeTkError_t err = _theBus->writeRegisterByte(kSfeQwiicBuzzerRegActive, 0x00);
    if (err != kSTkErrOk) // Check whether the write was successful
        return err;
    
    // Done!
    return kSTkErrOk;     
}

sfeTkError_t sfeQwiicBuzzerArdI2C::on(uint16_t toneFrequency, uint16_t duration, uint8_t volume)
{
    sfeTkError_t err = buzzerConfig(toneFrequency, duration, volume);
    if (err != kSTkErrOk) // Check whether the write was successful
        return err;

    err = setBuzzerActiveReg();
    if (err != kSTkErrOk) // Check whether the write was successful
        return err;        
    
    // Done!
    return kSTkErrOk;     
}

sfeTkError_t sfeQwiicBuzzerArdI2C::off()
{
    return clearBuzzerActiveReg();
}

sfeTkError_t sfeQwiicBuzzerArdI2C::saveSettings()
{
    sfeTkError_t err = _theBus->writeRegisterByte(kSfeQwiicBuzzerRegSaveSettings, 0x01);
    if (err != kSTkErrOk) // Check whether the write was successful
        return err;
    
    // Done!
    return kSTkErrOk;      
}

/*------------------------- Sound Effects ---------------- */

void sfeQwiicBuzzerArdI2C::playSoundEffect(uint8_t soundEffectNumber, uint8_t volume)
{
    switch (soundEffectNumber) {
        case 0:
            soundEffect0(volume);
            break;
        case 1:
            soundEffect1(volume);
            break;
        case 2:
            soundEffect2(volume);
            break;
        case 3:
            soundEffect3(volume);
            break;
        case 4:
            soundEffect4(volume);
            break;
        case 5:
            soundEffect5(volume);
            break;
        case 6:
            soundEffect6(volume);
            break;
        case 7:
            soundEffect7(volume);
            break;   
        case 8:
            soundEffect8(volume);
            break; 
        case 9:
            soundEffect9(volume);
            break;                                  
    }
}

// SIREN SLOW X1
void sfeQwiicBuzzerArdI2C::soundEffect0(uint8_t volume)
{
    for (int note = 150 ; note < 4000 ; note += 150)
    {
        on(note, 10, volume);
        delay(10);
    }
    for (int note = 4000 ; note > 150 ; note -= 150)
    {
        on(note, 10, volume);
        delay(10);
    }
}

// SIREN FAST X3
void sfeQwiicBuzzerArdI2C::soundEffect1(uint8_t volume)
{
    for (int i = 0 ; i <= 2 ; i++)
    {
        for (int note = 150 ; note < 4000 ; note += 150)
        {
            on(note, 2, volume);
            delay(2);
        }
        for (int note = 4000 ; note > 150 ; note -= 150)
        {
            on(note, 2, volume);
            delay(2);
        }
    }
}

// YES SLOW
void sfeQwiicBuzzerArdI2C::soundEffect2(uint8_t volume)
{
    for (int note = 150 ; note < 4000 ; note += 150)
    {
        on(note, 40, volume);
        delay(40);
    }
}

// YES FAST
void sfeQwiicBuzzerArdI2C::soundEffect3(uint8_t volume)
{
    for (int note = 150 ; note < 4000 ; note += 150)
    {
        on(note, 10, volume);
        delay(10);
    }
}

// NO SLOW
void sfeQwiicBuzzerArdI2C::soundEffect4(uint8_t volume)
{
    for (int note = 4000 ; note > 150 ; note -= 150)
    {
        on(note, 40, volume);
        delay(40);
    }
}

// NO FAST
void sfeQwiicBuzzerArdI2C::soundEffect5(uint8_t volume)
{
    for (int note = 4000 ; note > 150 ; note -= 150)
    {
        on(note, 10, volume);
        delay(10);
    }
}

// LAUGH
void sfeQwiicBuzzerArdI2C::soundEffect6(uint8_t volume)
{
    int laughdelay = 400;
    int laughstep = 10;
    uint16_t i;

    //for (i = 650; i > 525; i -= 3) // vary up //1538, 1905
    for (i = 1538; i < 1905; i += laughstep) // vary up //1538, 1905
    {
        on(i, 10, volume);
        delay(10);
    }
        
    delay(laughdelay);

    //for (i = 800; i > 660; i -= 3) // 1250, 1515
    for (i = 1250; i < 1515; i += laughstep) // 1250, 1515
    {
        on(i, 10, volume);
        delay(10);
    }
    delay(laughdelay);

    //for (i = 900; i > 745; i -= 3) // 1111, 1342
    for (i = 1111; i < 1342; i += laughstep) // 1111, 1342
    {
        on(i, 10, volume);
        delay(10);
    }
    delay(laughdelay);

    //for (i = 990; i > 850; i -= 3) // 1010, 1176
    for (i = 1010; i < 1176; i += laughstep) // 1010, 1176
    {
        on(i, 10, volume);
        delay(10);
    }
}

// LAUGH FAST
void sfeQwiicBuzzerArdI2C::soundEffect7(uint8_t volume)
{
    int laughdelay = 200;
    int laughstep = 15;
    uint16_t i;

    for (i = 1538; i < 1905; i += laughstep) // vary up //1538, 1905
    {
        on(i, 10, volume);
        delay(10);
    }
        
    delay(laughdelay);

    for (i = 1250; i < 1515; i += laughstep) // 1250, 1515
    {
        on(i, 10, volume);
        delay(10);
    }
    delay(laughdelay);

    for (i = 1111; i < 1342; i += laughstep) // 1111, 1342
    {
        on(i, 10, volume);
        delay(10);
    }
    delay(laughdelay);

    for (i = 1010; i < 1176; i += laughstep) // 1010, 1176
    {
        on(i, 10, volume);
        delay(10);
    }
}

// CRY SLOW
void sfeQwiicBuzzerArdI2C::soundEffect8(uint8_t volume)
{
    int crydelay = 500;
    int step = 10;
    uint16_t i;

    for (i = 2000; i > 1429; i -= step) // vary down //2000, 1429
    {
        on(i, 10, volume);
        delay(10);
    }
        
    delay(crydelay);

    for (i = 1667; i > 1250; i -= step) // 1667, 1250
    {
        on(i, 10, volume);
        delay(10);
    }
    delay(crydelay);

    //for (i = 900; i > 745; i -= 3) // 1111, 1342
    for (i = 1429; i > 1053; i -= step) // 1429, 1053
    {
        on(i, 10, volume);
        delay(10);
    }
}

// CRY FAST
void sfeQwiicBuzzerArdI2C::soundEffect9(uint8_t volume)
{
    int crydelay = 200;
    int step = 20;
    uint16_t i;

    for (i = 2000; i > 1429; i -= step) // vary down //2000, 1429
    {
        on(i, 10, volume);
        delay(10);
    }
        
    delay(crydelay);

    for (i = 1667; i > 1250; i -= step) // 1667, 1250
    {
        on(i, 10, volume);
        delay(10);
    }
    delay(crydelay);

    //for (i = 900; i > 745; i -= 3) // 1111, 1342
    for (i = 1429; i > 1053; i -= step) // 1429, 1053
    {
        on(i, 10, volume);
        delay(10);
    }
}