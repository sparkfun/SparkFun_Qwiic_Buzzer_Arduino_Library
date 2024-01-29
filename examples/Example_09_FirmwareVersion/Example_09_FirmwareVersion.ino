/******************************************************************************
  Example_09_FirmwareVersion

  This example shows how to read the firmware version from the Qwiic Buzzer

  By Pete Lewis @ SparkFun Electronics
  December 2023

  Based on code originally written by Fischer Moseley @ SparkFun Electronics
  Original Creation Date: June 28, 2019

  SparkFun code, firmware, and software is released under the MIT License.
	Please see LICENSE.md for further details.

  Hardware Connections:
  Connect QWIIC cable from Arduino to Qwiic Buzzer

  Distributed as-is; no warranty is given.
******************************************************************************/

#include <SparkFun_Qwiic_Buzzer_Arduino_Library.h>
QwiicBuzzer buzzer;

// variables to store the firmware version (major and Minor), 
// read back from the Qwiic Buzzer
uint8_t firmwareVersionMajor;
uint8_t firmwareVersionMinor;

bool err; // used for checking for errors

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer Example_09_FirmwareVersion");
  Wire.begin(); //Join I2C bus

  //check if buzzer will connect over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer connected.");

  err = buzzer.firmwareVersionMajor(firmwareVersionMajor);

  // Check whether the firmware read was successful
  if (err == false)
  {
    Serial.println("Could not read firmware version Major. Freezing.");
    while (1);
  }

  err = buzzer.firmwareVersionMinor(firmwareVersionMinor);

  // Check whether the firmware read was successful
  if (err == false)
  {
    Serial.println("Could not read firmware version Minor. Freezing.");
    while (1);
  }  
  
  Serial.println("Firmware Version read successfully!");

  Serial.print("Firmware Version Major: ");
  Serial.println(firmwareVersionMajor);
  Serial.print("Firmware Version Minor: ");
  Serial.println(firmwareVersionMinor);
}

void loop() {
// do nothing here
}
