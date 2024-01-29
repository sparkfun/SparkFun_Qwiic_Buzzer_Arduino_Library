/******************************************************************************
  Example_07_Buzz_Melody

  This example shows how to buzz a melody on the Qwiic Buzzer

  By Pete Lewis @ SparkFun Electronics
  December 2023

  Based on original source code written by Tom Igeo in Jan 2010:
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
  http://www.arduino.cc/en/Tutorial/Tone

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

// notes in the melody:
int melody[] = {
  SFE_QWIIC_BUZZER_NOTE_C4, 
  SFE_QWIIC_BUZZER_NOTE_G3, 
  SFE_QWIIC_BUZZER_NOTE_G3, 
  SFE_QWIIC_BUZZER_NOTE_A3, 
  SFE_QWIIC_BUZZER_NOTE_G3, 
  SFE_QWIIC_BUZZER_NOTE_REST,  // silence (aka "rest")
  SFE_QWIIC_BUZZER_NOTE_B3, 
  SFE_QWIIC_BUZZER_NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer Example_07_Buzz_Melody");
  Wire.begin(); //Join I2C bus

  //check if buzzer will connect over I2C
  if (buzzer.begin() == false) {
    Serial.println("Device did not connect! Freezing.");
    while (1);
  }
  Serial.println("Buzzer connected.");

  Serial.println("Buzzing Melody now...");
  play_melody();
}

void loop() {
  // do nothing here
  // we just play the melody once during setup above.
}

void play_melody()
{
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    buzzer.configureBuzzer(melody[thisNote], noteDuration, SFE_QWIIC_BUZZER_VOLUME_MAX);
    buzzer.on();

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}