#include <BleGamepad.h>  // BLE Gamepad library for ESP32

// Pin definitions for joystick and buttons
const int xPin = 34;    // Joystick X-axis connected to GPIO 36 (Analog Input)
const int yPin = 35;    // Joystick Y-axis connected to GPIO 39 (Analog Input)
const int buttonPin1 = 12;  // Button 1 connected to GPIO 12
const int buttonPin2 = 14;  // Button 2 connected to GPIO 14
const int buttonPin3 = 13; // Button 3 connected to GPIO 13

// Variables to store joystick and button states
int xValue = 0;
int yValue = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

// Create BLE Gamepad object
BleGamepad bleGamepad("Gamepad_v1.0", "Dingo", 100);

void setup() {
  Serial.begin(115200); // Start serial communication for debugging
  
  // Initialize the pins
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);

  // Start BLE gamepad
  bleGamepad.begin();
}

void loop() {
  if (bleGamepad.isConnected()) {
    // Read joystick values (12-bit resolution on ESP32)
    xValue = analogRead(xPin);
    yValue = analogRead(yPin);

    // Map joystick values to gamepad range (-32767 to 32767)
    int joystickX = map(xValue, 0, 4095, -32767, 32767);
    int joystickY = map(yValue, 0, 4095, -32767, 32767);

    // Send joystick values to the BLE gamepad
    bleGamepad.setAxes(joystickX, joystickY);

    // Read the button states
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);

    // Send button states to the BLE gamepad
    if (buttonState1 == LOW) {
      bleGamepad.press(1); // Button 1 pressed
    } else {
      bleGamepad.release(1); // Button 1 released
    }

    if (buttonState2 == LOW) {
      bleGamepad.press(2); // Button 2 pressed
    } else {
      bleGamepad.release(2); // Button 2 released
    }

    if (buttonState3 == LOW) {
      bleGamepad.press(3); // Button 3 pressed
    } else {
      bleGamepad.release(3); // Button 3 released
    }

    // Send the updated gamepad state
    bleGamepad.sendReport();
  }

  delay(20);  // Delay to reduce CPU usage and avoid flooding the BLE channel
}
