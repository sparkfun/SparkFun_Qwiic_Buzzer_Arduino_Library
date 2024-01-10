/******************************************************************************
SparkFun_Qwiic_Button.cpp
SparkFun Qwiic Button/Switch Library Source File
Fischer Moseley @ SparkFun Electronics
Original Creation Date: July 24, 2019

This file implements the QwiicButton class, prototyped in SparkFun_Qwiic_Button.h

Development environment specifics:
	IDE: Arduino 1.8.9
	Hardware Platform: Arduino Uno/SparkFun Redboard
	Qwiic Button Version: 1.0.0
    Qwiic Switch Version: 1.0.0

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
    return readSingleRegister(SFE_QWIIC_BUTTON_ID); //read and return the value in the ID register
}

bool QwiicBuzzer::checkDeviceID()
{
    return (deviceID() == SFE_QWIIC_BUTTON_DEV_ID); //Return true if the device ID matches
}

uint8_t QwiicBuzzer::getDeviceType()
{
    if (isConnected())
    { //only try to get the device ID if the device will acknowledge
        uint8_t id = deviceID();
        if (id == SFE_QWIIC_BUTTON_DEV_ID)
            return 1;
    }
    return 0;
}

uint16_t QwiicBuzzer::getFirmwareVersion()
{
    uint16_t version = (readSingleRegister(SFE_QWIIC_BUTTON_FIRMWARE_MAJOR)) << 8;
    version |= readSingleRegister(SFE_QWIIC_BUTTON_FIRMWARE_MINOR);
    return version;
}

bool QwiicBuzzer::setI2Caddress(uint8_t address)
{
    if (address < 0x08 || address > 0x77)
    {
        Serial.println("Error1");
        return 1; //error immediately if the address is out of legal range
    }

    bool success = writeSingleRegister(SFE_QWIIC_BUTTON_I2C_ADDRESS, address);

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

    return success;
}

bool QwiicBuzzer::LEDoff()
{
    return BUZZERconfig(0, 0, 0);
}

bool QwiicBuzzer::LEDon(uint8_t brightness)
{
    return BUZZERconfig(brightness, 0, 0);
}

bool QwiicBuzzer::on(uint16_t toneFrequency, uint16_t duration, uint8_t volume)
{
    return BUZZERconfig(toneFrequency, duration, volume);
}

bool QwiicBuzzer::off()
{
    return BUZZERconfig(0, 0, 0);
}

bool QwiicBuzzer::saveSettings()
{
    return writeSingleRegister(SFE_QWIIC_BUZZER_SAVE_SETTINGS, 0x01);
}

/*------------------------- Internal I2C Abstraction ---------------- */

uint8_t QwiicBuzzer::readSingleRegister(Qwiic_Button_Register reg)
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

uint16_t QwiicBuzzer::readDoubleRegister(Qwiic_Button_Register reg)
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

unsigned long QwiicBuzzer::readQuadRegister(Qwiic_Button_Register reg)
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

bool QwiicBuzzer::writeSingleRegister(Qwiic_Button_Register reg, uint8_t data)
{
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->write(data);
    if (_i2cPort->endTransmission() == 0)
        return true;
    return false;
}

bool QwiicBuzzer::writeDoubleRegister(Qwiic_Button_Register reg, uint16_t data)
{
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->write(lowByte(data));
    _i2cPort->write(highByte(data));
    if (_i2cPort->endTransmission() == 0)
        return true;
    return false;
}

uint8_t QwiicBuzzer::writeSingleRegisterWithReadback(Qwiic_Button_Register reg, uint8_t data)
{
    if (writeSingleRegister(reg, data))
        return 1;
    if (readSingleRegister(reg) != data)
        return 2;
    return 0;
}

uint16_t QwiicBuzzer::writeDoubleRegisterWithReadback(Qwiic_Button_Register reg, uint16_t data)
{
    if (writeDoubleRegister(reg, data))
        return 1;
    if (readDoubleRegister(reg) != data)
        return 2;
    return 0;
}