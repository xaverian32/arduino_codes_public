#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  // Initialize serial communication at 115200 baud rate for debugging
  Serial.begin(9600);

  // Initialize I2C communication on pins D18 (SCL) and D19 (SDA)
  Wire.begin(19, 18); // SDA on pin 19, SCL on pin 18

  // Try to initialize the MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  // Set up the accelerometer and gyro ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 initialized successfully!");
}

void loop() {
  // Get new sensor events with the MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print accelerometer values
  Serial.print("Accel X: "); Serial.print(a.acceleration.x);
  Serial.print("\tAccel Y: "); Serial.print(a.acceleration.y);
  Serial.print("\tAccel Z: "); Serial.print(a.acceleration.z);

  // Print gyroscope values
  Serial.print("\tGyro X: "); Serial.print(g.gyro.x);
  Serial.print("\tGyro Y: "); Serial.print(g.gyro.y);
  Serial.print("\tGyro Z: "); Serial.println(g.gyro.z);

  // Delay before the next reading
  delay(500);
}
