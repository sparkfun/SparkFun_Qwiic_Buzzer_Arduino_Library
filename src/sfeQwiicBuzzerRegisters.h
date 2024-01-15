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

This code is Lemonadeware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

//Register Pointer Map
enum Qwiic_Buzzer_Register : uint8_t
{
    kSfeQwiicBuzzerRegId = 0x00,
    kSfeQwiicBuzzerRegFirmwareMinor = 0x01,
    kSfeQwiicBuzzerRegFirmwareMajor = 0x02,
    kSfeQwiicBuzzerRegToneFrequencyMsb = 0x03,   
    kSfeQwiicBuzzerRegToneFrequencyLsb = 0x04,       
    kSfeQwiicBuzzerRegVolume = 0x05, 
    kSfeQwiicBuzzerRegDurationMsb = 0x06, 
    kSfeQwiicBuzzerRegDurationLsb = 0x07, 
    kSfeQwiicBuzzerRegActive = 0x08, 
    kSfeQwiicBuzzerRegSaveSettings = 0x09, 
    kSfeQwiicBuzzerRegI2cAddress = 0x0A,
};