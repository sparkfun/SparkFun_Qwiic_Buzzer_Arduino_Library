/******************************************************************************
  Example_08_Sound_Effects

  This example demos the sound effects included in this library.

  By Pete Lewis @ SparkFun Electronics
  December 2023

  Based on code originally written by Fischer Moseley @ SparkFun Electronics
  Original Creation Date: June 28, 2019

  Sound effects based on the following work:
    Jan 21st, 2020
    Snake In A Can Controller
    Written by: Pete Lewis, with contributions from Jeff Haas
    A collaboration with Mario the Maker Magician
    https://www.mariothemagician.com/

    January, 2021
    Cry, Laugh Functions were adapted from Adafruit animal sounds
    by Magician/hacker Jeff Haas. Thanks Jeff!!
    https://learn.adafruit.com/adafruit-trinket-modded-stuffed-animal/animal-sounds

  This code is Lemonadeware; if you see me (or any other SparkFun employee) at the
  local, and you've found our code helpful, please buy us a round!

  Hardware Connections:
  Connect QWIIC cable from Arduino to Qwiic Buzzer

  Distributed as-is; no warranty is given.
******************************************************************************/

#include <SparkFun_Qwiic_Buzzer_Arduino_Library.h>
QwiicBuzzer buzzer;

#define kBuzzerVolume 4 // loudest!!
//#define kBuzzerVolume 3 // pretty good volume for most things

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer Example_08_Sound_Effects");
  Wire.begin(); //Join I2C bus

  //check if buzzer will acknowledge over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Buzzer acknowledged.");

  for(int i = 0 ; i <= 9 ; i++)
  {
    Serial.print("Sound Effect: ");
    Serial.println(i);
    buzzer.playSoundEffect(i, kBuzzerVolume);
    delay(2000);
  }
}

void loop() {
  // do nothing
  // we play through all the available sound effects above in setup once.
}