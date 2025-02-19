#include <DHT.h>

// Define the type of sensor and its pin
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 test");

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read humidity
  float humidity = dht.readHumidity();

  // Read temperature in Celsius (the default)
  float temperatureC = dht.readTemperature();

  // Read temperature in Fahrenheit
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

}
