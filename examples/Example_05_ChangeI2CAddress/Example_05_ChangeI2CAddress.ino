/******************************************************************************
  A configurator for changing the I2C address on the Qwiic Buzzer that walks
  the user through finding the address of their buzzer, and then changing it!

  Fischer Moseley @ SparkFun Electronics
  Original Creation Date: July 30, 2019

  SparkFun code, firmware, and software is released under the MIT License.
	Please see LICENSE.md for further details.

  Hardware Connections:
  Attach the Qwiic Buzzer to your Redboard via Qwiic Cable
  Open and interact with serial monitor at 115200 baud.

  Distributed as-is; no warranty is given.
******************************************************************************/

#include <SparkFun_Qwiic_Buzzer_Arduino_Library.h>
QwiicBuzzer buzzer;

// The default address is 0x34, change this if your buzzer currently has a different address!
uint8_t initialAddress = SFE_QWIIC_BUZZER_DEFAULT_ADDRESS;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic Buzzer example - I2C Address Change");
  Wire.begin(); //Join I2C bus

  //check if device will connect over I2C
  if (buzzer.begin(initialAddress) == false) {
    Serial.println("Device did not connect! Running scanner.");
  }
  else{
    Serial.println("Device connected!");
  
    Serial.println();
    Serial.println("Enter a new I2C address for the Qwiic Buzzer to use!");
    Serial.println("Don't use the 0x prefix. For instance, if you wanted to");
    Serial.println("change the address to 0x5B, you would enter 5B and press enter.");
    Serial.println();
    Serial.println("One more thing! Make sure your line ending is set to 'Both NL & CR'");
    Serial.println("in the Serial Monitor.");
    Serial.println();

    //Wait for serial data to be available
    while (Serial.available() == 0);
  
    if (Serial.available()) {
      uint8_t newAddress = 0;
      String stringBuffer = Serial.readString();
      char charBuffer[10];
      stringBuffer.toCharArray(charBuffer, 10);
      uint8_t success = sscanf(charBuffer, "%x", &newAddress);
  
      if (success) {
        if (newAddress > 0x08 && newAddress < 0x77) {
          Serial.println("Character received, and device address is valid!");
          Serial.print("Attempting to set device address to 0x");
          Serial.println(newAddress, HEX);
  
          if (buzzer.setAddress(newAddress) == true) {
            Serial.println("Device address set succeeded!");
          }
  
          else {
            Serial.println("Device address set failed!");
          }
  
          delay(100); //give the hardware time to do whatever configuration it needs to do
  
          if (buzzer.isConnected()) {
            Serial.println("Device will connect on new I2C address!");
          }
  
          else {
            Serial.println("Device will not connect on new I2C address.");
          }
        }
  
        else {
          Serial.println("Address out of range! Try an address between 0x08 and 0x77");
        }
      }
  
      else {
        Serial.print("Invalid Text! Try again.");
      }
    }
    delay(100);
  }
}

void loop() {
  //if no I2C device found or Qwiic Buzzer correctly set to new address, 
  //scan for available I2C devices
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmission to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan


}
