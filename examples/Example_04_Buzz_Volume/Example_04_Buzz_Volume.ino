/******************************************************************************
  Example_04_Buzz_Volume

  This example shows how to control the buzzer to sound at different volumes.

  Note, the "on()" function accepts three arguments, and you must send all three
  in order to access the volume control.

  on(frequency, duration, volume);

  It turns the buzzer on and off.
  Much like the classic "blink LED sketch" this will buzz
  the buzzer once every second at a different volumes.

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
  Serial.println("Qwiic Buzzer Example_04_Buzz_Volume");
  Wire.begin(); //Join I2C bus

  //check if buzzer will connect over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer connected.");
}

void loop() {
  Serial.println("Volume: Quietest (1)");
  buzzer.on(2730, 100, 1); // frequency: 2.73KHz, duration: 100ms, volume: 1
  delay(1000);

  Serial.println("Volume: Mid-low (2)");
  buzzer.on(2730, 100, 2); // frequency: 2.73KHz, duration: 100ms, volume: 2
  delay(1000);

  Serial.println("Volume: Mid-high (3)");
  buzzer.on(2730, 100, 3); // frequency: 2.73KHz, duration: 100ms, volume: 3
  delay(1000);

  Serial.println("Volume: Loudest (4)");
  buzzer.on(2730, 100, 4); // frequency: 2.73KHz, duration: 100ms, volume: 4
  delay(1000);

  // Note, we dont' have to use buzzer.off(), because it will automatically turn
  // off after the duration of each tone is completed.
}
