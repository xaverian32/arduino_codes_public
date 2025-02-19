#include <DHT.h>


#define SENSOR_PIN  18 // ESP32 pin GPIO18 connected to the sensor's SIGNAL pin of touch sensor

// Define the type of sensor and its pin
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the ESP32's pin as aninput
  pinMode(SENSOR_PIN, INPUT);

    Serial.println("DHT11 test");

  // Initialize the DHT sensor
  dht.begin();
}
 
void loop() {
  
  // Read humidity
  float humidity = dht.readHumidity();

  // Read temperature in Celsius (the default)
  float temperatureC = dht.readTemperature();

  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print humidity and temperature readings
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperatureC);
  Serial.println("°C");
  // read the state of the the input pin:
  int state = digitalRead(SENSOR_PIN);

  // print state to Serial Monitor
  Serial.println(state);
}
