#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Create TinyGPS++ object
TinyGPSPlus gps;

// Initialize serial ports for GPS and debugging
HardwareSerial gpsSerial(1); // Use UART1 for GPS

#define analog_pin 4
float sensor_value; 

void setup() {
  Serial.begin(115200);        // Debugging serial port
  gpsSerial.begin(115200, SERIAL_8N1, 16, 17); // GPS serial port (Baud rate 9600, RX=16, TX=17)

  Serial.println("GPS Location Extractor");

   Serial.println("MQ3 is warming up");
  delay(120000);  //2 min warm up time
}

void loop() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    // Feed data into the GPS parser
    if (gps.encode(c)) {
      // Display location if valid data is available
      if (gps.location.isUpdated()) {
        Serial.print("Location: ");
        Serial.print(gps.location.lat(), 2);// 2 decimal places for precision
        Serial.print(",");
        Serial.println(gps.location.lng(), 2);
      }
    }
  }

  // Display a message if no data has been received for a while
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS data received: Check wiring and GPS signal.");
  }

    sensor_value = analogRead(analog_pin); 
  Serial.print("Sensor Value: ");
  Serial.println(sensor_value);
  delay(200); 
}
