/******************************************************************************
  Example_08_Sound_Effects

  This example demos the sound effects included in this library.

  This includes the following sound effects:
    0 (aka "Siren")
      Intended to sound like a siren, starting at a low frequency, and then
      increasing rapidly up and then back down. This sound effect does a
      single "up and down" cycle.

    1 (aka "3 Fast Sirens")
      Similar to the "Siren" sound effect, only faster and goes three times.

    2 (aka "robot saying 'Yes'")
      Intended to sound like a robot saying the word "yes".
      It starts at a low frequency and quickly ramps up to a high frequency, 
      then stops. This can be interpreted by most to be an affirmative
      sound to any question you may ask your buzzing robot.      

    3 (aka "robot yelling 'YES!'" - faster)
      Same as the "Yes" sound effect, only faster.
      When done more quickly, it can add enthusiasm to the buzzing sound.

    4 (aka "robot saying 'No'")
      Intended to sound like a robot saying the word "no".
      It starts at a high frequency and quickly ramps down to a low frequency, 
      then stops. This can be interpreted by most to be an negative
      sound to any question you may ask your buzzing robot. 

    5 (aka "robot yelling 'NO!'" - faster)
      Same as the "No" sound effect, only faster.
      When done more quickly, it can add enthusiasm to the buzzing sound.

    6 (aka "Laughing Robot")
      Intended to sound like your robot is laughing at you.

    7 (aka "Laughing Robot Faster")
      Same as the "Laugh" sound effect, only faster.
      When done more quickly, it can add enthusiasm to the buzzing sound.

    8 (aka "Crying Robot")
      Intended to sound like a robot is crying and sad.

    9 (aka "Crying Robot Faster")
      Same as the "Cry" sound effect, only faster.
      When done more quickly, it can add enthusiasm to the buzzing sound.

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

  SparkFun code, firmware, and software is released under the MIT License.
	Please see LICENSE.md for further details.

  Hardware Connections:
  Connect QWIIC cable from Arduino to Qwiic Buzzer

  Distributed as-is; no warranty is given.
******************************************************************************/

#include <SparkFun_Qwiic_Buzzer_Arduino_Library.h>
QwiicBuzzer buzzer;

#define BUZZER_VOLUME 4 // loudest!!     
//#define BUZZER_VOLUME 3 // pretty good volume for most things
bool err; // used for checking for errors

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer Example_08_Sound_Effects");
  Wire.begin(); //Join I2C bus
  Wire.setClock(400000); // sound effects require changing configuration quickly

  //check if buzzer will connect over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer connected.");

  for(int i = 0 ; i <= 9 ; i++)
  {
    Serial.print("Sound Effect: ");
    Serial.println(i);
    err = buzzer.playSoundEffect(i, BUZZER_VOLUME);

    // Check whether the playSoundEffect() was successful
    if (err == false)
    {
      Serial.println("error!");
      break;
    }
    delay(2000);
  }
}

void loop() {
  // do nothing
  // we play through all the available sound effects above in setup once.
}