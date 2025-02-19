#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>  // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library

#define LCD_ADDRESS 0x27

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// GPIO Pins
const int PIR_PIN = 25;
const int LDR_PIN = 34;
const int LED_PIN = 26;

void setup() {
  Serial.begin(115200);

  // Initialize GPIO pins
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi (optional)
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  lcd.init();

  // Turn on the backlight (if available on your module)
  lcd.backlight();

  // Print a message to the LCD
  lcd.setCursor(0, 0);  // Set cursor to first column and first row
  lcd.print("WELCOME");
}

void loop() {
  int pirState = digitalRead(PIR_PIN); // Read the PIR sensor state
  int ldrValue = analogRead(LDR_PIN);  // Read the LDR value (0 to 4095)
  int brightness = calculateBrightness(pirState, ldrValue);


  if (pirState > 0 && ldrValue < 4000)
  {
    lcd.setCursor(0, 0);  // Set cursor to first column and first row
    lcd.print("LIGHTS");

    lcd.setCursor(0, 1);  // Set cursor to first column and first row
    lcd.print("ON");
    lcd.clear();

  }

  else
  {
    lcd.setCursor(0, 0);  // Set cursor to first column and first row
    lcd.print("LIGHTS");

    lcd.setCursor(0, 1);  // Set cursor to first column and first row
    lcd.print("OFF");
    lcd.clear();



  }

  if (pirState > 0 && ldrValue < 4000) {


    // Set the LED brightness using PWM
    analogWrite(LED_PIN, brightness);
  }

  // Optional: Send data to a server or log it
  sendDataToCloud(pirState, ldrValue, brightness);

  delay(1000); // Loop delay (adjust as needed)
}


int calculateBrightness(int presence, int light) {
  int baseBrightness = 255; // Default to maximum brightness

  // Adjust brightness based on the ambient light and presence
  if (presence == 1) { // If presence is detected
    if (light < 1000) { // Dark room
      baseBrightness = 255; // Full brightness
    } else if (light < 3000) { // Dim light
      baseBrightness = 128; // Medium brightness
    } else { // Bright room
      baseBrightness = 50; // Low brightness
    }
  } else {
    baseBrightness = 0; // Turn off lights if no one is present
  }

  return baseBrightness; // Return calculated brightness
}

void sendDataToCloud(int presence, int light, int brightness) {
  // Placeholder for sending data to a cloud server or logging it
  // This could involve HTTP POST requests or MQTT messages
  // Example:
  // Serial.printf("Presence: %d, Light: %d, Brightness: %d\n", presence, light, brightness);
}
