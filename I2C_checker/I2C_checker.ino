#include <Wire.h>

void setup() {
  Wire.begin(21, 22); // Use your SDA and SCL pins
  Serial.begin(115200);
  delay(10000);
  Serial.println("\nI2C Scanner");
  for (uint8_t address = 1; address < 1023; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
    }
  else{
    Serial.print("I2C device not found at address 0x");
      Serial.println(address, HEX);
  }
  }
}

void loop() {}
