/******************************************************************************
  Example_02_Buzz_Frequency

  This example shows how to adjust the frequency of the buzzer.

  It turns the buzzer on and off.
  Much like the classic "blink LED sketch" this will buzz
  the buzzer once every second at a different frequency.

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
  Serial.println("Qwiic Buzzer Example_02_Buzz_Frequency");
  Wire.begin(); //Join I2C bus

  //check if buzzer will connect over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer connected.");
}

void loop() {
  // Configure with desired settings
  // Resonant frequency is 2.73KHz
  buzzer.configureBuzzer(SFE_QWIIC_BUZZER_RESONANT_FREQUENCY); 
  buzzer.on(); 
  delay(100);
  
  buzzer.off();
  delay(1000);

  buzzer.configureBuzzer(1000); // set frequency to 1KHz
  buzzer.on(); 
  delay(100);
  
  buzzer.off();
  delay(1000);
}
