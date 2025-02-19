// Define the pins for the ultrasonic sensor
const int trigPin = 7;
const int echoPin = 6;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  pinMode(trigPin, OUTPUT); // Set the trigPin as an output
  pinMode(echoPin, INPUT); // Set the echoPin as an input
}

void loop() {
  long duration;
  int distance;

  // Clear the trigPin by setting it LOW for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds to send the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000); // Delay for 1 second before the next measurement
}
