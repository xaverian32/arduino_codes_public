#include <DHT.h>

// Define the type of sensor and its pin
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

//initialize MQ2 pin
const int sensorPin2 = 32;

//initialize MQ4 pin
const int sensorPin4 = 34;

//initialize the MQ135
const int sensorPin135 = 33;


// stores MQ2 data
int gasValue2; // Variable to store raw sensor value

// stores MQ4 data
int gasValue4; // Variable to store raw sensor value

//stores MQ135 data
int gasValue135;



void setup() {
  Serial.begin(9600);
  pinMode(sensorPin2, INPUT); // Set the sensor pin as an input
    pinMode(sensorPin4, INPUT); // Set the sensor pin as an input
  pinMode(sensorPin135, INPUT); // Set the sensor pin as an input

  
  Serial.println("DHT22 test");


  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  //for MQ2 sensor reading

  int sensorValue2 = analogRead(sensorPin2);

  // for MQ4 sensor reading
  int sensorValue4 = analogRead(sensorPin4);

  // for MQ135 sensor reading
  int sensorValue135 = analogRead(sensorPin135);


  // Read humidity from DHT22
  float humidity = dht.readHumidity();

  // Read temperature in Celsius (the default) from DHT22
  float temperatureC = dht.readTemperature();

  // Read temperature in Fahrenheit from DHT22
  float temperatureF = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (optional)
  float heatIndexF = dht.computeHeatIndex(temperatureF, humidity);

  // Print humidity and temperature readings
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperatureC);
  Serial.print("°C / ");
  Serial.print(temperatureF);
  Serial.print("°F");

  // Print heat index
  Serial.print(" - Heat index: ");
  Serial.print(heatIndexF);
  Serial.println("°F");

  //printing the MQ2 sensor data
  Serial.print("Gas Value: ");
  Serial.println(sensorValue2);
  
  //printing the MQ4 sensor data
  Serial.print("Gas Value: ");
  Serial.println(sensorValue4);

  //printing the MQ135 sensor data
  Serial.println(sensorValue135);

}
