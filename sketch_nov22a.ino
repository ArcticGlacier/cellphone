#include <Wire.h>

void setup() {
  Serial.begin(9600);

  Serial.println("\nI2C Scanner");
  Serial.println("Scanning...");
  byte device_count = 0;

  Wire.begin();
  for (byte address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
     // Serial.print ("Found address: ");
      Serial.print("I2C device found at address 0x");
      Serial.print(address, HEX);
      Serial.println("  !");
      device_count++;
      delay(1);
    }
  }
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (device_count);
  Serial.println (" device(s).");
}

void loop() {}