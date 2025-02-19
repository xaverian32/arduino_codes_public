#include <Arduino.h>
#include <WiFi.h>

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// GPIO Pins
const int PIR_PIN = 25;
const int LDR_PIN = 34;
const int LED_PIN = 26;

void setup() {
  Serial.begin(115200);

  // Initialize GPIO pins
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int pirState = digitalRead(PIR_PIN); // 0 or 1 based on presence
  int ldrValue = analogRead(LDR_PIN);  // Raw value from 0 to 4095
  int brightness = calculateBrightness(pirState, ldrValue);

  // Adjust the LED brightness
  analogWrite(LED_PIN, brightness);

  // Optional: Send data to server or cloud for logging/analysis
  sendDataToCloud(pirState, ldrValue, brightness);

  delay(1000); // Adjust as needed
}

int calculateBrightness(int presence, int light) {
  int baseBrightness = 255;

  // Simple decision-making based on presence and ambient light
  if (presence == 1) {
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

  return baseBrightness;
}

void sendDataToCloud(int presence, int light, int brightness) {
  // Implement cloud data transmission logic here
  // For example, send data via HTTP POST request to a server
  // This is a placeholder function
}
