#include <Arduino.h>
#include <WiFi.h>

// Wi-Fi credentials
const char* ssid = "Redmi K50i";
const char* password = "soham1809";

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
}

void loop() {
  int pirState = digitalRead(PIR_PIN); // Read the PIR sensor state
  int ldrValue = analogRead(LDR_PIN);  // Read the LDR value (0 to 4095)
  int brightness = calculateBrightness(pirState, ldrValue);

  // Set the LED brightness using PWM
  analogWrite(LED_PIN, brightness);

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
