/******************************************************************************
  Example_04_Buzz_Volume

  This example shows how to control the buzzer to sound at different volumes.

  Note, the "configureBuzzer()" function accepts three arguments, and you must send all three
  in order to access the volume control.

  configureBuzzer(frequency, duration, volume);

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
  Serial.println("Volume: MIN (1)");
  buzzer.configureBuzzer(2730, 100, SFE_QWIIC_BUZZER_VOLUME_MIN); // frequency: 2.73KHz, duration: 100ms, volume: MIN
  buzzer.on();
  delay(1000);

  Serial.println("Volume: LOW (2)");
  buzzer.configureBuzzer(2730, 100, SFE_QWIIC_BUZZER_VOLUME_LOW); // frequency: 2.73KHz, duration: 100ms, volume: LOW
  buzzer.on();
  delay(1000);

  Serial.println("Volume: MID (3)");
  buzzer.configureBuzzer(2730, 100, SFE_QWIIC_BUZZER_VOLUME_MID); // frequency: 2.73KHz, duration: 100ms, volume: MID
  buzzer.on();
  delay(1000);

  Serial.println("Volume: MAX (4)");
  buzzer.configureBuzzer(2730, 100, SFE_QWIIC_BUZZER_VOLUME_MAX); // frequency: 2.73KHz, duration: 100ms, volume: MAX
  buzzer.on();
  delay(1000);

  // Note, we dont' have to use buzzer.off(), because it will automatically turn
  // off after the duration of each tone is completed.
}
