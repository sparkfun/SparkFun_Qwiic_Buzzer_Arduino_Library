/******************************************************************************
  Example_10_Buzz_Multiple

  This example shows how to control multiple buzzers.
  
  Note, you must use the ChangeI2CAddress example to change the address of your
  second (or third, etc.) buzzers. Here, we are using "0x5B" for the address
  of buzzer2.
  
  It turns each buzzer on and off with their own unique frequencies in a 
  unique pattern.

  By Pete Lewis @ SparkFun Electronics
  February 2024

  Based on code originally written by Fischer Moseley @ SparkFun Electronics
  Original Creation Date: June 28, 2019

  SparkFun code, firmware, and software is released under the MIT License.
	Please see LICENSE.md for further details.

  Hardware Connections:
  Connect QWIIC cable from Arduino to Qwiic Buzzers

  Distributed as-is; no warranty is given.
******************************************************************************/

#include <SparkFun_Qwiic_Buzzer_Arduino_Library.h>
QwiicBuzzer buzzer1;
QwiicBuzzer buzzer2; // create a second buzzer

#define BUZZER_1_ADDRESS SFE_QWIIC_BUZZER_DEFAULT_ADDRESS // default is 0x34
#define BUZZER_2_ADDRESS 0x5B

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer Example_10_Buzz_Multiple");
  Wire.begin(); //Join I2C bus

  //check if buzzer 1 will connect over I2C
  if (buzzer1.begin(BUZZER_1_ADDRESS) == false) {
    Serial.println("Device 1 did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer 1 connected.");

  //check if buzzer 2 will connect over I2C
  if (buzzer2.begin(BUZZER_2_ADDRESS) == false) {
    Serial.println("Device 2 did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer 2 connected.");
}

void loop() {
  buzzer1.configureBuzzer(SFE_QWIIC_BUZZER_NOTE_C4);
  buzzer1.on();

  delay(1000);

  buzzer2.configureBuzzer(SFE_QWIIC_BUZZER_NOTE_E6);
  buzzer2.on();
  
  delay(1000);
  
  buzzer1.off();

  delay(1000);

  buzzer2.off();
  
  delay(1000);
}
