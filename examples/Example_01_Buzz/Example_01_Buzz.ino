/******************************************************************************
  Example_01_Buzz

  This example shows how to turn the buzzer on and off.
  Much like the classic "blink LED sketch" this will buzz
  the buzzer once every second.

  By Pete Lewis @ SparkFun Electronics
  December 2023

  Based on code orginally written by Fischer Moseley @ SparkFun Electronics
  Original Creation Date: June 28, 2019

  This code is Lemonadeware; if you see me (or any other SparkFun employee) at the
  local, and you've found our code helpful, please buy us a round!

  Hardware Connections:
  Connect QWIIC cable from Arduino to Qwiic Buzzer

  Distributed as-is; no warranty is given.
******************************************************************************/

#include <SparkFun_Qwiic_Buzzer_Arduino_Library.h>
QwiicBuzzer buzzer;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer Example_01_Buzz");
  Wire.begin(); //Join I2C bus

  //check if button will acknowledge over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Buzzer acknowledged.");

  buzzer.on(2730);
  
  delay(100);
  
  buzzer.off();
  
  delay(100);

    buzzer.on(1000);
  
  delay(100);
  
  buzzer.off();
  
  delay(100);

}

void loop() {

}
