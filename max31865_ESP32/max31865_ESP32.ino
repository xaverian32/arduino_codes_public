/***************************************************
  Modified for ESP32-S3-Pico
  Adafruit PT100/P1000 RTD Sensor w/MAX31865
****************************************************/

#include <Adafruit_MAX31865.h>

// Define SPI pins for ESP32-S3-Pico
#define MAX_CS   10  // Chip Select (Adjust as per your setup)
#define MAX_MOSI 11  // MOSI (Data input to MAX31865)
#define MAX_MISO 12  // MISO (Data output from MAX31865)
#define MAX_SCK  13  // Serial Clock

// Ensure no conflicting declaration
#ifdef max
#undef max
#endif

// Initialize the MAX31865 sensor with software SPI
Adafruit_MAX31865 max31865 = Adafruit_MAX31865(MAX_CS, MAX_MOSI, MAX_MISO, MAX_SCK);

// The value of the reference resistor
#define RREF 430.0

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test on ESP32-S3-Pico!");

  max31865.begin(MAX31865_2WIRE);  // Set to 2-wire configuration
}

void loop() {
  uint16_t rtd = max31865.readRTD();

  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio, 8);
  Serial.print("Resistance = "); Serial.println(RREF * ratio, 8);
  Serial.print("Temperature = "); Serial.println(max31865.temperature(100, RREF));

  // Check and print any faults
  uint8_t fault = max31865.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    max31865.clearFault();
  }
  Serial.println();
  delay(1000);
}
