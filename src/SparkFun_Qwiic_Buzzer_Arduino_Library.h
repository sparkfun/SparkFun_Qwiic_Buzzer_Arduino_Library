/******************************************************************************
SparkFun_Qwiic_Buzzer_Arduino_Library.h
SparkFun Qwiic Buzzer Library header file

by Pete Lewis @SparkFun Electronics
Jan 2024

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

#ifndef __SparkFun_Qwiic_Buzzer_H__
#define __SparkFun_Qwiic_Buzzer_H__

#include <Wire.h>
#include <Arduino.h>
#include "registers.h"
#include "buzzer_pitches.h"

#define SFE_QWIIC_BUZZER_DEFAULT_ADDRESS 0x34 //default I2C address of the buzzer
#define SFE_QWIIC_BUZZER_DEV_ID 0x5D          //device ID of the Qwiic Buzzer

class QwiicBuzzer
{
private:
    TwoWire *_i2cPort;      //Generic connection to user's chosen I2C port
    uint8_t _deviceAddress; //I2C address of the buzzer

public:
    //Device status
    bool begin(uint8_t address = SFE_QWIIC_BUZZER_DEFAULT_ADDRESS, TwoWire &wirePort = Wire); //Sets device I2C address to a user-specified address, over whatever port the user specifies.
    bool isConnected();                                                      //Returns true if the device will acknowledge over I2C, and false otherwise
    uint8_t deviceID();                                                      //Return the 8-bit device ID of the attached device.
    bool checkDeviceID();                                                    //Returns true if the device ID matches that of the buzzer
    uint8_t getDeviceType();                                                 //Returns 1 if a buzzer is attached, 2 if a switch is attached. Returns 0 if there is no device attached.
    uint16_t getFirmwareVersion();                                           //Returns the firmware version of the attached device as a 16-bit integer. The leftmost (high) byte is the major revision number, and the rightmost (low) byte is the minor revision number.
    bool setI2Caddress(uint8_t address);                                     //Configures the attached device to attach to the I2C bus using the specified address
    uint8_t getI2Caddress();                                                 //Returns the I2C address of the device.

    //Buzzer configuration
    bool BUZZERconfig(uint16_t toneFrequency, uint16_t duration, 
                   uint8_t volume); //Configures the LED with the given max brightness, granularity (1 is fine for most applications), cycle time, and off time.
    bool on(uint16_t toneFrequency = 2730, uint16_t duration = 0, uint8_t volume = 4);
    bool off();
    bool saveSettings(); // store settings to EEPROM
    bool setBuzzerActiveReg();
    bool clearBuzzerActiveReg();

    void playSoundEffect(uint8_t soundEffectNumber, uint8_t volume);
    void soundEffect0(uint8_t volume);
    void soundEffect1(uint8_t volume);
    void soundEffect2(uint8_t volume);
    void soundEffect3(uint8_t volume);
    void soundEffect4(uint8_t volume);
    void soundEffect5(uint8_t volume);
    void soundEffect6(uint8_t volume);
    void soundEffect7(uint8_t volume);
    void soundEffect8(uint8_t volume);
    void soundEffect9(uint8_t volume);

    //Internal I2C Abstraction
    uint8_t readSingleRegister(Qwiic_Buzzer_Register reg);                              //Reads a single 8-bit register.
    uint16_t readDoubleRegister(Qwiic_Buzzer_Register reg);                             //Reads a 16-bit register (little endian).
    unsigned long readQuadRegister(Qwiic_Buzzer_Register reg);                          //Reads a 32-bit register (little endian).
    bool writeSingleRegister(Qwiic_Buzzer_Register reg, uint8_t data);                  //Attempts to write data into a single 8-bit register. Does not check to make sure it was written successfully. Returns 0 if there wasn't an error on I2C transmission, and 1 otherwise.
    bool writeDoubleRegister(Qwiic_Buzzer_Register reg, uint16_t data);                 //Attempts to write data into a double (two 8-bit) registers. Does not check to make sure it was written successfully. Returns 0 if there wasn't an error on I2C transmission, and 1 otherwise.
    uint8_t writeSingleRegisterWithReadback(Qwiic_Buzzer_Register reg, uint8_t data);   //Writes data into a single 8-bit register, and checks to make sure that the data was written successfully. Returns 0 on no error, 1 on I2C write fail, and 2 if the register doesn't read back the same value that was written.
    uint16_t writeDoubleRegisterWithReadback(Qwiic_Buzzer_Register reg, uint16_t data); //Writes data into a double (two 8-bit) registers, and checks to make sure that the data was written successfully. Returns 0 on no error, 1 on I2C write fail, and 2 if the register doesn't read back the same value that was written.
};
#endif
