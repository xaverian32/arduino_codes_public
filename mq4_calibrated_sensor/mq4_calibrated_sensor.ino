//***********************************calibrated to cleanairvalue MQ4 sensor***********************************************






// Define the analog pin where the MQ4 sensor is connected
const int sensorPin = A0;

// Variables for calibration
int cleanAirValue = 500; // Replace with your sensor's clean air value
int gasValue; // Variable to store raw sensor value

void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  pinMode(sensorPin, INPUT); // Set the sensor pin as an input
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(sensorPin);
  
  // Subtract the clean air value to get the gas value
  gasValue = sensorValue - cleanAirValue;
  
  // Print the gas value (you should calibrate this for specific gases)
  Serial.print("Gas Value: ");
  Serial.println(gasValue);
  
  delay(1000); // Delay for 1 second before next reading
}
