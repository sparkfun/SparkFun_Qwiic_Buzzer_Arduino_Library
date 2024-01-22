/******************************************************************************
  Example_06_SaveSettings

  This example shows how to save settings to the buzzer.

  It buzzes the buzzer once, and then commands it to save the settings.

  It then does nothing more in the main loop. It is up to you to trigger using
  the TRIGGER header pin.

  NOTE, TRIGGER PIN does utilize frequency, duration and volume. This means you can 
  set it up to be a "momentary" trigger button, or a "one-shot" button.

  When Duration=0, trigger is "momentary" trigger button.

  When Duration>0, trigger will fire a "one-shot" buzz of duration length.

  Note, this is most practically used when planning to trigger the buzzer using
  only the TRIGGER header pin.

  This is useful if you want to set the frequency, duration, volume to your 
  desired settings, and then have it remember them for next time you power your 
  Qwiic buzzer up. Then you can use the TRIGGER header to cause the buzzer to 
  buzz at your saved settings.

  Note, the "configureBuzzer()" function accepts three arguments:
  configureBuzzer(frequency, duration, volume);

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
  Serial.println("Qwiic Buzzer Example_06_SaveSettings");
  Wire.begin(); //Join I2C bus

  //check if buzzer will connect over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer connected.");

  Serial.println("Buzzing at 1K, volume 3");

  // Comment/Un-Comment the following "buzzer.on()" example lines to try different settings:
  
  // "MOMENTARY" SETUP
  buzzer.configureBuzzer(1000, 0, SFE_QWIIC_BUZZER_VOLUME_MID); // frequency: 1KHz, duration: 0 (aka forever), volume: MID

  // "ONE-SHOT" Setup (aka adding in a duration amount).
  // buzzer.configureBuzzer(1000, 100, SFE_QWIIC_BUZZER_VOLUME_MID); // frequency: 1KHz, duration: 100ms, volume: MID

  buzzer.on();
  delay(1000);

  Serial.println("Buzzer OFF");
  buzzer.off();

  Serial.println("Saving settings now...");
  buzzer.saveSettings();

  Serial.println("Goodbye.");
}

void loop() {
  // nothing here
  // use the TRIGGER header pin to cause the buzzer to make sounds
}
