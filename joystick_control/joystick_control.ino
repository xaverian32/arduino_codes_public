const int xPin = A0;    // Joystick X-axis connected to analog pin A0
const int yPin = A1;    // Joystick Y-axis connected to analog pin A1
const int buttonPin = 2; // Joystick button connected to digital pin 2

int xValue = 0;  // Variable to store X-axis value
int yValue = 0;  // Variable to store Y-axis value
int buttonState = 0;  // Variable to store button state

void setup() {
  Serial.begin(9600);          // Initialize serial communication at 9600 baud
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with internal pull-up
}

void loop() {
  // Read the X and Y values from the analog pins
  xValue = analogRead(xPin);  
  yValue = analogRead(yPin);
  
  // Read the state of the button (LOW when pressed, HIGH when not pressed)
  buttonState = digitalRead(buttonPin);

  // Print the values to the serial monitor
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");
  
  if (buttonState == LOW) {
    Serial.println("Pressed");
  } else {
    Serial.println("Not Pressed");
  }

  delay(100);  // Delay to avoid flooding the serial monitor
}
