#include <BleGamepad.h>  // Include the BLE gamepad library

BleGamepad bleGamepad;

void setup() {
  Serial.begin(115200);  // Start serial communication
  bleGamepad.begin();    // Initialize the BLE gamepad
}

void loop() {
  if(bleGamepad.isConnected()) {
    // Simulate a joystick moving left (X axis) and pressing a button
    bleGamepad.setAxes(32767, 0, 0, 0, 0, 0);  // X-axis to max positive (right), Y-axis neutral
    bleGamepad.press(BUTTON_1);  // Simulate pressing button 1
    bleGamepad.release(BUTTON_1);  // Simulate releasing button 1
    delay(500);  // Delay between actions

    // Simulate joystick moving right (X axis)
    bleGamepad.setAxes(-32767, 0, 0, 0, 0, 0);  // X-axis to max negative (left), Y-axis neutral
    bleGamepad.press(BUTTON_2);  // Simulate pressing button 2
    bleGamepad.release(BUTTON_2);  // Simulate releasing button 2
    delay(500);  // Delay between actions
  } else {
    Serial.println("Gamepad not connected");
  }
}
