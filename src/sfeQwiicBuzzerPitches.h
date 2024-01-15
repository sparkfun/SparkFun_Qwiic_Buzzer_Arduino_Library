/******************************************************************************
sfeQwiicBuzzerPitches.h
SparkFun Qwiic Buzzer Library header file
This file contains a list of commonly found notes on a piano.

by Pete Lewis @SparkFun Electronics
January 2024

Based on original source code written by Tom Igeo in Jan 2010:
https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
http://www.arduino.cc/en/Tutorial/Tone

This code is Lemonadeware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

/*************************************************
   Public Constants
 *************************************************/

#define kSfeQwiicBuzzerNoteB0 31
#define kSfeQwiicBuzzerNoteC1 33
#define kSfeQwiicBuzzerNoteCS1 35
#define kSfeQwiicBuzzerNoteD1 37
#define kSfeQwiicBuzzerNoteDS1 39
#define kSfeQwiicBuzzerNoteE1 41
#define kSfeQwiicBuzzerNoteF1 44
#define kSfeQwiicBuzzerNoteFS1 46
#define kSfeQwiicBuzzerNoteG1 49
#define kSfeQwiicBuzzerNoteGS1 52
#define kSfeQwiicBuzzerNoteA1 55
#define kSfeQwiicBuzzerNoteAS1 58
#define kSfeQwiicBuzzerNoteB1 62
#define kSfeQwiicBuzzerNoteC2 65
#define kSfeQwiicBuzzerNoteCS2 69
#define kSfeQwiicBuzzerNoteD2 73
#define kSfeQwiicBuzzerNoteDS2 78
#define kSfeQwiicBuzzerNoteE2 82
#define kSfeQwiicBuzzerNoteF2 87
#define kSfeQwiicBuzzerNoteFS2 93
#define kSfeQwiicBuzzerNoteG2 98
#define kSfeQwiicBuzzerNoteGS2 104
#define kSfeQwiicBuzzerNoteA2 110
#define kSfeQwiicBuzzerNoteAS2 117
#define kSfeQwiicBuzzerNoteB2 123
#define kSfeQwiicBuzzerNoteC3 131
#define kSfeQwiicBuzzerNoteCS3 139
#define kSfeQwiicBuzzerNoteD3 147
#define kSfeQwiicBuzzerNoteDS3 156
#define kSfeQwiicBuzzerNoteE3 165
#define kSfeQwiicBuzzerNoteF3 175
#define kSfeQwiicBuzzerNoteFS3 185
#define kSfeQwiicBuzzerNoteG3 196
#define kSfeQwiicBuzzerNoteGS3 208
#define kSfeQwiicBuzzerNoteA3 220
#define kSfeQwiicBuzzerNoteAS3 233
#define kSfeQwiicBuzzerNoteB3 247
#define kSfeQwiicBuzzerNoteC4 262
#define kSfeQwiicBuzzerNoteCS4 277
#define kSfeQwiicBuzzerNoteD4 294
#define kSfeQwiicBuzzerNoteDS4 311
#define kSfeQwiicBuzzerNoteE4 330
#define kSfeQwiicBuzzerNoteF4 349
#define kSfeQwiicBuzzerNoteFS4 370
#define kSfeQwiicBuzzerNoteG4 392
#define kSfeQwiicBuzzerNoteGS4 415
#define kSfeQwiicBuzzerNoteA4 440
#define kSfeQwiicBuzzerNoteAS4 466
#define kSfeQwiicBuzzerNoteB4 494
#define kSfeQwiicBuzzerNoteC5 523
#define kSfeQwiicBuzzerNoteCS5 554
#define kSfeQwiicBuzzerNoteD5 587
#define kSfeQwiicBuzzerNoteDS5 622
#define kSfeQwiicBuzzerNoteE5 659
#define kSfeQwiicBuzzerNoteF5 698
#define kSfeQwiicBuzzerNoteFS5 740
#define kSfeQwiicBuzzerNoteG5 784
#define kSfeQwiicBuzzerNoteGS5 831
#define kSfeQwiicBuzzerNoteA5 880
#define kSfeQwiicBuzzerNoteAS5 932
#define kSfeQwiicBuzzerNoteB5 988
#define kSfeQwiicBuzzerNoteC6 1047
#define kSfeQwiicBuzzerNoteCS6 1109
#define kSfeQwiicBuzzerNoteD6 1175
#define kSfeQwiicBuzzerNoteDS6 1245
#define kSfeQwiicBuzzerNoteE6 1319
#define kSfeQwiicBuzzerNoteF6 1397
#define kSfeQwiicBuzzerNoteFS6 1480
#define kSfeQwiicBuzzerNoteG6 1568
#define kSfeQwiicBuzzerNoteGS6 1661
#define kSfeQwiicBuzzerNoteA6 1760
#define kSfeQwiicBuzzerNoteAS6 1865
#define kSfeQwiicBuzzerNoteB6 1976
#define kSfeQwiicBuzzerNoteC7 2093
#define kSfeQwiicBuzzerNoteCS7 2217
#define kSfeQwiicBuzzerNoteD7 2349
#define kSfeQwiicBuzzerNoteDS7 2489
#define kSfeQwiicBuzzerNoteE7 2637
#define kSfeQwiicBuzzerNoteF7 2794
#define kSfeQwiicBuzzerNoteFS7 2960
#define kSfeQwiicBuzzerNoteG7 3136
#define kSfeQwiicBuzzerNoteGS7 3322
#define kSfeQwiicBuzzerNoteA7 3520
#define kSfeQwiicBuzzerNoteAS7 3729
#define kSfeQwiicBuzzerNoteB7 3951
#define kSfeQwiicBuzzerNoteC8 4186
#define kSfeQwiicBuzzerNoteCS8 4435
#define kSfeQwiicBuzzerNoteD8 4699
#define kSfeQwiicBuzzerNoteDS8 4978


// Backwards compatibility with original "pitches.h" file written by Tim Igeo, 2010.
#define NOTE_B0 kSfeQwiicBuzzerNoteB0
#define NOTE_C1 kSfeQwiicBuzzerNoteC1
#define NOTE_CS1 kSfeQwiicBuzzerNoteCS1
#define NOTE_D1 kSfeQwiicBuzzerNoteD1
#define NOTE_DS1 kSfeQwiicBuzzerNoteDS1
#define NOTE_E1 kSfeQwiicBuzzerNoteE1
#define NOTE_F1 kSfeQwiicBuzzerNoteF1
#define NOTE_FS1 kSfeQwiicBuzzerNoteFS1
#define NOTE_G1 kSfeQwiicBuzzerNoteG1
#define NOTE_GS1 kSfeQwiicBuzzerNoteGS1
#define NOTE_A1 kSfeQwiicBuzzerNoteA1
#define NOTE_AS1 kSfeQwiicBuzzerNoteAS1
#define NOTE_B1 kSfeQwiicBuzzerNoteB1
#define NOTE_C2 kSfeQwiicBuzzerNoteC2
#define NOTE_CS2 kSfeQwiicBuzzerNoteCS2
#define NOTE_D2 kSfeQwiicBuzzerNoteD2
#define NOTE_DS2 kSfeQwiicBuzzerNoteDS2
#define NOTE_E2 kSfeQwiicBuzzerNoteE2
#define NOTE_F2 kSfeQwiicBuzzerNoteF2
#define NOTE_FS2 kSfeQwiicBuzzerNoteFS2
#define NOTE_G2 kSfeQwiicBuzzerNoteG2
#define NOTE_GS2 kSfeQwiicBuzzerNoteGS2
#define NOTE_A2 kSfeQwiicBuzzerNoteA2
#define NOTE_AS2 kSfeQwiicBuzzerNoteAS2
#define NOTE_B2 kSfeQwiicBuzzerNoteB2
#define NOTE_C3 kSfeQwiicBuzzerNoteC3
#define NOTE_CS3 kSfeQwiicBuzzerNoteCS3
#define NOTE_D3 kSfeQwiicBuzzerNoteD3
#define NOTE_DS3 kSfeQwiicBuzzerNoteDS3
#define NOTE_E3 kSfeQwiicBuzzerNoteE3
#define NOTE_F3 kSfeQwiicBuzzerNoteF3
#define NOTE_FS3 kSfeQwiicBuzzerNoteFS3
#define NOTE_G3 kSfeQwiicBuzzerNoteG3
#define NOTE_GS3 kSfeQwiicBuzzerNoteGS3
#define NOTE_A3 kSfeQwiicBuzzerNoteA3
#define NOTE_AS3 kSfeQwiicBuzzerNoteAS3
#define NOTE_B3 kSfeQwiicBuzzerNoteB3
#define NOTE_C4 kSfeQwiicBuzzerNoteC4
#define NOTE_CS4 kSfeQwiicBuzzerNoteCS4
#define NOTE_D4 kSfeQwiicBuzzerNoteD4
#define NOTE_DS4 kSfeQwiicBuzzerNoteDS4
#define NOTE_E4 kSfeQwiicBuzzerNoteE4
#define NOTE_F4 kSfeQwiicBuzzerNoteF4
#define NOTE_FS4 kSfeQwiicBuzzerNoteFS4
#define NOTE_G4 kSfeQwiicBuzzerNoteG4
#define NOTE_GS4 kSfeQwiicBuzzerNoteGS4
#define NOTE_A4 kSfeQwiicBuzzerNoteA4
#define NOTE_AS4 kSfeQwiicBuzzerNoteAS4
#define NOTE_B4 kSfeQwiicBuzzerNoteB4
#define NOTE_C5 kSfeQwiicBuzzerNoteC5
#define NOTE_CS5 kSfeQwiicBuzzerNoteCS5
#define NOTE_D5 kSfeQwiicBuzzerNoteD5
#define NOTE_DS5 kSfeQwiicBuzzerNoteDS5
#define NOTE_E5 kSfeQwiicBuzzerNoteE5
#define NOTE_F5 kSfeQwiicBuzzerNoteF5
#define NOTE_FS5 kSfeQwiicBuzzerNoteFS5
#define NOTE_G5 kSfeQwiicBuzzerNoteG5
#define NOTE_GS5 kSfeQwiicBuzzerNoteGS5
#define NOTE_A5 kSfeQwiicBuzzerNoteA5
#define NOTE_AS5 kSfeQwiicBuzzerNoteAS5
#define NOTE_B5 kSfeQwiicBuzzerNoteB5
#define NOTE_C6 kSfeQwiicBuzzerNoteC6
#define NOTE_CS6 kSfeQwiicBuzzerNoteCS6
#define NOTE_D6 kSfeQwiicBuzzerNoteD6
#define NOTE_DS6 kSfeQwiicBuzzerNoteDS6
#define NOTE_E6 kSfeQwiicBuzzerNoteE6
#define NOTE_F6 kSfeQwiicBuzzerNoteF6
#define NOTE_FS6 kSfeQwiicBuzzerNoteFS6
#define NOTE_G6 kSfeQwiicBuzzerNoteG6
#define NOTE_GS6 kSfeQwiicBuzzerNoteGS6
#define NOTE_A6 kSfeQwiicBuzzerNoteA6
#define NOTE_AS6 kSfeQwiicBuzzerNoteAS6
#define NOTE_B6 kSfeQwiicBuzzerNoteB6
#define NOTE_C7 kSfeQwiicBuzzerNoteC7
#define NOTE_CS7 kSfeQwiicBuzzerNoteCS7
#define NOTE_D7 kSfeQwiicBuzzerNoteD7
#define NOTE_DS7 kSfeQwiicBuzzerNoteDS7
#define NOTE_E7 kSfeQwiicBuzzerNoteE7
#define NOTE_F7 kSfeQwiicBuzzerNoteF7
#define NOTE_FS7 kSfeQwiicBuzzerNoteFS7
#define NOTE_G7 kSfeQwiicBuzzerNoteG7
#define NOTE_GS7 kSfeQwiicBuzzerNoteGS7
#define NOTE_A7 kSfeQwiicBuzzerNoteA7
#define NOTE_AS7 kSfeQwiicBuzzerNoteAS7
#define NOTE_B7 kSfeQwiicBuzzerNoteB7
#define NOTE_C8 kSfeQwiicBuzzerNoteC8
#define NOTE_CS8 kSfeQwiicBuzzerNoteCS8
#define NOTE_D8 kSfeQwiicBuzzerNoteD8
#define NOTE_DS8 kSfeQwiicBuzzerNoteDS8