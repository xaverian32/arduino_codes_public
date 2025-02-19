#include <Adafruit_MAX31865.h>
#include <SPI.h>

// Define GPIO pins for SPI interface on ESP32-C3
#define MAX31865_CS 5  // Chip Select (choose any GPIO pin)
#define MAX31865_MISO 4 // Master-In-Slave-Out
#define MAX31865_MOSI 7 // Master-Out-Slave-In
#define MAX31865_SCK 6  // Serial Clock

// Define RTD parameters
#define RREF 430.0      // Reference resistor value (ohms)
#define RNOMINAL 100.0  // Nominal resistance of Pt-100 at 0°C (ohms)

// Create an instance of the MAX31865 class
Adafruit_MAX31865 max31865 = Adafruit_MAX31865(MAX31865_CS);

void setup() {
  // Initialize Serial Monitor
  delay(10000);
  Serial.begin(115200);
  Serial.println("ESP32-C3 MAX31865 PT-100 Sensor Test");

  // Set up SPI
  
  SPI.begin(MAX31865_SCK, MAX31865_MISO, MAX31865_MOSI);

  // Initialize MAX31865
  if (!max31865.begin(MAX31865_2WIRE)) { // 2-wire configuration
    Serial.println("Failed to initialize MAX31865. Check connections!");
    //while (1); // Halt execution if initialization fails
  }
  else{
    Serial.println("MAX31865 initialized");
  }
}

void loop() {
  // Read temperature from the Pt-100 sensor
  float temperature = max31865.temperature(RNOMINAL, RREF);

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Delay for a second before the next reading
  delay(1000);
}
