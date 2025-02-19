const int buttonPin = 4;    // Pin connected to the button
const int pulsePin = 5;    // Pin connected to where the pulse will be sent (e.g., an LED)
int buttonState = 0;        // Variable for reading the button status
int lastButtonState = 0;    // Variable to store the last button state
bool pulseGenerated = false; // Flag to ensure only one pulse is generated

void setup() {
  pinMode(buttonPin, INPUT);    // Set button pin as input
  pinMode(pulsePin, OUTPUT);    // Set pulse pin as output (LED, for example)
  digitalWrite(pulsePin, LOW);  // Initially, keep the pulse pin low
}

void loop() {
  // Read the current state of the button
  buttonState = digitalRead(buttonPin);

  // Check if the button was just pressed (transition from LOW to HIGH)
  if (buttonState == HIGH && lastButtonState == LOW && !pulseGenerated) {
    // Generate a pulse
    digitalWrite(pulsePin, HIGH);  // Send the pulse
    delay(10);                     // Pulse duration (10 ms)
    digitalWrite(pulsePin, LOW);   // End the pulse
    
    pulseGenerated = true;         // Set flag to prevent multiple pulses
  }

  // Reset the pulse generation flag when the button is released
  if (buttonState == LOW && lastButtonState == HIGH) {
    pulseGenerated = false;        // Reset the flag when button is released
  }

  // Store the current button state for the next loop
  lastButtonState = buttonState;
}
