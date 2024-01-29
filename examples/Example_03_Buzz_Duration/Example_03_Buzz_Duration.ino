/******************************************************************************
  Example_03_Buzz_Duration

  This example shows how to control the buzzer using frequency and duration.

  It turns the buzzer on and off.
  Much like the classic "blink LED sketch" this will buzz
  the buzzer once every second at a different frequency and duration.

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

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer Example_03_Buzz_Duration");
  Wire.begin(); //Join I2C bus

  //check if buzzer will connect over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer connected.");
}

void loop() {
  buzzer.configureBuzzer(2730, 100); // frequency: 2.73KHz, duration: 100ms
  buzzer.on();
  delay(1000);

  buzzer.configureBuzzer(1000, 500); // frequency: 1K, duration: 500ms
  buzzer.on();
  delay(1000);

  // Note, we dont' have to call buzzer.off(), because it will automatically turn
  // off after the duration of each tone is completed.
}
