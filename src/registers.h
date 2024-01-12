/******************************************************************************
registers.h
Fischer Moseley @ SparkFun Electronics
Original Creation Date: July 24, 2019

This file defines the virtual memory map on the Qwiic Buzzer. The enum
provides a set of pointers for the various registers on the Qwiic
Buzzer.

Development environment specifics:
	IDE: Arduino 2.2.1
	Hardware Platform: Arduino Uno/SparkFun Redboard
	Qwiic Buzzer Version: v10

This code is Lemonadeware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

//Register Pointer Map
enum Qwiic_Buzzer_Register : uint8_t
{
    SFE_QWIIC_BUZZER_ID = 0x00,
    SFE_QWIIC_BUZZER_FIRMWARE_MINOR = 0x01,
    SFE_QWIIC_BUZZER_FIRMWARE_MAJOR = 0x02,
    SFE_QWIIC_BUZZER_TONE_FREQUENCY_MSB = 0x03,   
    SFE_QWIIC_BUZZER_TONE_FREQUENCY_LSB = 0x04,       
    SFE_QWIIC_BUZZER_VOLUME = 0x05, 
    SFE_QWIIC_BUZZER_DURATION_MSB = 0x06, 
    SFE_QWIIC_BUZZER_DURATION_LSB = 0x07, 
    SFE_QWIIC_BUZZER_ACTIVE = 0x08, 
    SFE_QWIIC_BUZZER_SAVE_SETTINGS = 0x09, 
    SFE_QWIIC_BUZZER_I2C_ADDRESS = 0x0A,
};