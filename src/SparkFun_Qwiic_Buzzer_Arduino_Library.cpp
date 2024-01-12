/******************************************************************************
SparkFun_Qwiic_Buzzer_Arduino_Library.cpp
SparkFun Qwiic Buzzer Library Source File

by Pete Lewis @SparkFun Electronics
Jan 2024

Based on original source code written by
Fischer Moseley @ SparkFun Electronics
Original Creation Date: July 24, 2019

Sound effects based on the following work:
    Jan 21st, 2020
    Snake In A Can Controller
    Written by: Pete Lewis, with contributions from Jeff Haas
    A collaboration with Mario the Maker Magician
    https://www.mariothemagician.com/

    January, 2021
    Cry, Laugh Functions were adapted from Adafruit animal sounds
    by Magician/hacker Jeff Haas. Thanks Jeff!!
    https://learn.adafruit.com/adafruit-trinket-modded-stuffed-animal/animal-sounds

This file implements the QwiicBuzzer class, prototyped in SparkFun_Qwiic_Buzzer_Arduino_Library.h

Development environment specifics:
	IDE: Arduino 2.2.1
	Hardware Platform: Arduino Uno/SparkFun Redboard
	Qwiic Buzzer Version: v10

This code is Lemonadeware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#include <Wire.h>
#include <SparkFun_Qwiic_Buzzer_Arduino_Library.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*-------------------------------- Device Status ------------------------*/

bool QwiicBuzzer::begin(uint8_t address, TwoWire &wirePort)
{
    _deviceAddress = address; //grab the address that the sensor is on
    _i2cPort = &wirePort;     //grab the port that the user wants to use

    //return true if the device is connected and the device ID is what we expect
    return (isConnected() && checkDeviceID());
}

bool QwiicBuzzer::isConnected()
{
    _i2cPort->beginTransmission(_deviceAddress);
    if (_i2cPort->endTransmission() == 0)
        return true;
    return false;
}

uint8_t QwiicBuzzer::deviceID()
{
    return readSingleRegister(SFE_QWIIC_BUZZER_ID); //read and return the value in the ID register
}

bool QwiicBuzzer::checkDeviceID()
{
    return (deviceID() == SFE_QWIIC_BUZZER_DEV_ID); //Return true if the device ID matches
}

uint8_t QwiicBuzzer::getDeviceType()
{
    if (isConnected())
    { //only try to get the device ID if the device will acknowledge
        uint8_t id = deviceID();
        if (id == SFE_QWIIC_BUZZER_DEV_ID)
            return 1;
    }
    return 0;
}

uint16_t QwiicBuzzer::getFirmwareVersion()
{
    uint16_t version = (readSingleRegister(SFE_QWIIC_BUZZER_FIRMWARE_MAJOR)) << 8;
    version |= readSingleRegister(SFE_QWIIC_BUZZER_FIRMWARE_MINOR);
    return version;
}

bool QwiicBuzzer::setI2Caddress(uint8_t address)
{
    if (address < 0x08 || address > 0x77)
    {
        Serial.println("Error1");
        return 1; //error immediately if the address is out of legal range
    }

    bool success = writeSingleRegister(SFE_QWIIC_BUZZER_I2C_ADDRESS, address);

    if (success == true)
    {
        _deviceAddress = address;
        return true;
    }

    else
    {
        Serial.println("Error2");
        return false;
    }
}

uint8_t QwiicBuzzer::getI2Caddress()
{
    return _deviceAddress;
}



/*------------------------ BUZZER Configuration ------------------------ */
bool QwiicBuzzer::BUZZERconfig(uint16_t toneFrequency, uint16_t duration, uint8_t volume)
{
    bool success = writeSingleRegister(SFE_QWIIC_BUZZER_VOLUME, volume);

    uint8_t toneFrequencyMSB = ((toneFrequency & 0xFF00) >> 8 );
    uint8_t toneFrequencyLSB = (toneFrequency & 0x00FF);
    success &= writeSingleRegister(SFE_QWIIC_BUZZER_TONE_FREQUENCY_MSB, toneFrequencyMSB);
    success &= writeSingleRegister(SFE_QWIIC_BUZZER_TONE_FREQUENCY_LSB, toneFrequencyLSB);

    uint8_t durationMSB = ((duration & 0xFF00) >> 8 );
    uint8_t durationLSB = (duration & 0x00FF);
    success &= writeSingleRegister(SFE_QWIIC_BUZZER_DURATION_MSB, durationMSB);
    success &= writeSingleRegister(SFE_QWIIC_BUZZER_DURATION_LSB, durationLSB);

    if(volume > 0)
    {
        success &= setBuzzerActiveReg();
    }
    else
    {
        success &= clearBuzzerActiveReg();
    }

    return success;
}

bool QwiicBuzzer::on(uint16_t toneFrequency, uint16_t duration, uint8_t volume)
{
    return BUZZERconfig(toneFrequency, duration, volume);
}

bool QwiicBuzzer::off()
{
    return clearBuzzerActiveReg();
}

bool QwiicBuzzer::saveSettings()
{
    return writeSingleRegister(SFE_QWIIC_BUZZER_SAVE_SETTINGS, 0x01);
}

bool QwiicBuzzer::setBuzzerActiveReg()
{
    return writeSingleRegister(SFE_QWIIC_BUZZER_ACTIVE, 0x01);
}

bool QwiicBuzzer::clearBuzzerActiveReg()
{
    return writeSingleRegister(SFE_QWIIC_BUZZER_ACTIVE, 0x00);
}

/*------------------------- Internal I2C Abstraction ---------------- */

uint8_t QwiicBuzzer::readSingleRegister(Qwiic_Buzzer_Register reg)
{
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->endTransmission();

    //typecasting the 1 parameter in requestFrom so that the compiler
    //doesn't give us a warning about multiple candidates
    if (_i2cPort->requestFrom(_deviceAddress, static_cast<uint8_t>(1)) != 0)
    {
        return _i2cPort->read();
    }
    return 0;
}

uint16_t QwiicBuzzer::readDoubleRegister(Qwiic_Buzzer_Register reg)
{ //little endian
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->endTransmission();

    //typecasting the 2 parameter in requestFrom so that the compiler
    //doesn't give us a warning about multiple candidates
    if (_i2cPort->requestFrom(_deviceAddress, static_cast<uint8_t>(2)) != 0)
    {
        uint16_t data = _i2cPort->read();
        data |= (_i2cPort->read() << 8);
        return data;
    }
    return 0;
}

unsigned long QwiicBuzzer::readQuadRegister(Qwiic_Buzzer_Register reg)
{
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->endTransmission();

    union databuffer {
        uint8_t array[4];
        unsigned long integer;
    };

    databuffer data;

    //typecasting the 4 parameter in requestFrom so that the compiler
    //doesn't give us a warning about multiple candidates
    if (_i2cPort->requestFrom(_deviceAddress, static_cast<uint8_t>(4)) != 0)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            data.array[i] = _i2cPort->read();
        }
    }
    return data.integer;
}

bool QwiicBuzzer::writeSingleRegister(Qwiic_Buzzer_Register reg, uint8_t data)
{
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->write(data);
    if (_i2cPort->endTransmission() == 0)
        return true;
    return false;
}

bool QwiicBuzzer::writeDoubleRegister(Qwiic_Buzzer_Register reg, uint16_t data)
{
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->write(lowByte(data));
    _i2cPort->write(highByte(data));
    if (_i2cPort->endTransmission() == 0)
        return true;
    return false;
}

uint8_t QwiicBuzzer::writeSingleRegisterWithReadback(Qwiic_Buzzer_Register reg, uint8_t data)
{
    if (writeSingleRegister(reg, data))
        return 1;
    if (readSingleRegister(reg) != data)
        return 2;
    return 0;
}

uint16_t QwiicBuzzer::writeDoubleRegisterWithReadback(Qwiic_Buzzer_Register reg, uint16_t data)
{
    if (writeDoubleRegister(reg, data))
        return 1;
    if (readDoubleRegister(reg) != data)
        return 2;
    return 0;
}

/*------------------------- Sound Effects ---------------- */

void QwiicBuzzer::playSoundEffect(uint8_t soundEffectNumber, uint8_t volume)
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
void QwiicBuzzer::soundEffect0(uint8_t volume)
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
    off();
}

// SIREN FAST X3
void QwiicBuzzer::soundEffect1(uint8_t volume)
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
    off();
}

// YES SLOW
void QwiicBuzzer::soundEffect2(uint8_t volume)
{
    for (int note = 150 ; note < 4000 ; note += 150)
    {
        on(note, 50, volume);
        delay(40);
    }
    off();
}

// YES FAST
void QwiicBuzzer::soundEffect3(uint8_t volume)
{
    for (int note = 150 ; note < 4000 ; note += 150)
    {
        on(note, 10, volume);
        delay(10);
    }
    off();
}

// NO SLOW
void QwiicBuzzer::soundEffect4(uint8_t volume)
{
    for (int note = 4000 ; note > 150 ; note -= 150)
    {
        on(note, 50, volume);
        delay(40);
    }
    off();
}

// NO FAST
void QwiicBuzzer::soundEffect5(uint8_t volume)
{
    for (int note = 4000 ; note > 150 ; note -= 150)
    {
        on(note, 10, volume);
        delay(10);
    }
    off();
}

// LAUGH
void QwiicBuzzer::soundEffect6(uint8_t volume)
{
    int laughdelay = 400;
    int laughstep = 10;
    uint16_t i;

    //for (i = 650; i > 525; i -= 3) // vary up //1538, 1905
    for (i = 1538; i < 1905; i += laughstep) // vary up //1538, 1905
    {
        on(i, 20, volume);
        delay(10);
    }
        
    delay(laughdelay);

    //for (i = 800; i > 660; i -= 3) // 1250, 1515
    for (i = 1250; i < 1515; i += laughstep) // 1250, 1515
    {
        on(i, 20, volume);
        delay(10);
    }
    delay(laughdelay);

    //for (i = 900; i > 745; i -= 3) // 1111, 1342
    for (i = 1111; i < 1342; i += laughstep) // 1111, 1342
    {
        on(i, 20, volume);
        delay(10);
    }
    delay(laughdelay);

    //for (i = 990; i > 850; i -= 3) // 1010, 1176
    for (i = 1010; i < 1176; i += laughstep) // 1010, 1176
    {
        on(i, 20, volume);
        delay(10);
    }
    off();
}

// LAUGH FAST
void QwiicBuzzer::soundEffect7(uint8_t volume)
{
    int laughdelay = 200;
    int laughstep = 15;
    uint16_t i;

    for (i = 1538; i < 1905; i += laughstep) // vary up //1538, 1905
    {
        on(i, 20, volume);
        delay(10);
    }
        
    delay(laughdelay);

    for (i = 1250; i < 1515; i += laughstep) // 1250, 1515
    {
        on(i, 20, volume);
        delay(10);
    }
    delay(laughdelay);

    for (i = 1111; i < 1342; i += laughstep) // 1111, 1342
    {
        on(i, 20, volume);
        delay(10);
    }
    delay(laughdelay);

    for (i = 1010; i < 1176; i += laughstep) // 1010, 1176
    {
        on(i, 20, volume);
        delay(10);
    }
    off();
}

// CRY SLOW
void QwiicBuzzer::soundEffect8(uint8_t volume)
{
    int crydelay = 500;
    int step = 10;
    uint16_t i;

    for (i = 2000; i > 1429; i -= step) // vary down //2000, 1429
    {
        on(i, 20, volume);
        delay(10);
    }
        
    delay(crydelay);

    for (i = 1667; i > 1250; i -= step) // 1667, 1250
    {
        on(i, 20, volume);
        delay(10);
    }
    delay(crydelay);

    //for (i = 900; i > 745; i -= 3) // 1111, 1342
    for (i = 1429; i > 1053; i -= step) // 1429, 1053
    {
        on(i, 20, volume);
        delay(10);
    }
    off();
}

// CRY FAST
void QwiicBuzzer::soundEffect9(uint8_t volume)
{
    int crydelay = 200;
    int step = 20;
    uint16_t i;

    for (i = 2000; i > 1429; i -= step) // vary down //2000, 1429
    {
        on(i, 20, volume);
        delay(10);
    }
        
    delay(crydelay);

    for (i = 1667; i > 1250; i -= step) // 1667, 1250
    {
        on(i, 20, volume);
        delay(10);
    }
    delay(crydelay);

    //for (i = 900; i > 745; i -= 3) // 1111, 1342
    for (i = 1429; i > 1053; i -= step) // 1429, 1053
    {
        on(i, 20, volume);
        delay(10);
    }
    off();
}