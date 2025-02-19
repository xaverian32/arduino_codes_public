#include <Servo.h>

// Create a Servo object
Servo servoMotor;

// Define the analog pin where the potentiometer is connected
const int potPin = A0;

void setup() {
  // Attach the servo motor to pin 9
  servoMotor.attach(9);
}

void loop() {
  // Read the value from the potentiometer (0-1023)
  int potValue = analogRead(potPin);
  
  // Map the potentiometer value (0-1023) to servo angle range (0-180)
  int servoAngle = map(potValue, 0, 1023, 0, 180);
  
  // Set the servo position based on the mapped angle
  servoMotor.write(servoAngle);
  
  delay(15); // Delay to allow servo to reach the position
}
