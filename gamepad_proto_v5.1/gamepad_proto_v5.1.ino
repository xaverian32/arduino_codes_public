#include <BleGamepad.h>
#include <Wire.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;


BleGamepad bleGamepad("Gamepad_v1.0", "Dingo", 100);

////// TRIGGER BUTTONS
////#define LT 2
////#define RT 23
//
// LEFT-JOYSTICK
#define LH 34
#define LV 35
#define LS 25
//
////// RIGHT-JOYSTICK
////#define RH 39
////#define RV 36
////#define RS 19
//
// D-PAD-1
#define L1 14                          //HIGH
#define L2 12
#define L3 13
#define L4 26

//D-PAD-2
#define R1 23
#define R2 22
#define R3 21                          //   17
#define R4 4                           //   16

// BATTERY VOLTAGE
//#define ADC 4

//int buttons[12] = {32, 33, 27, 14, 18, 5, 17, 16, 15, 23, 2, 19};
//int buttons[9] = {32, 33, 27, 14, 18, 5, 19, 2, 15};
int buttons[9] = {25,23,21,22,4,14,12,13,26};
//int buttons[4] = {23,21,22,4};


int period = 10000;
unsigned long time_now = 0;

const int numberOfPotSamples = 5;     // Number of pot samples to take (to smooth the values)
const int delayBetweenSamples = 2;    // Delay in milliseconds between pot samples
const int delayBetweenHIDReports = 5; // Additional delay in milliseconds between HID reports
const int debounceDelay = 10;        // Delay in milliseconds between button press

void setup() {
  Serial.begin(115200);
//  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, 6);
//  FastLED.setBrightness(64);
  for (int i = 0; i < 9; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  bleGamepad.begin();
  //bleGamepad.setAutoReport(false); // to disable auto reporting, and then use bleGamepad.sendReport(); as needed
  Serial.println("Starting BLE work!");

//  leds[0] = CRGB::Red;
//  leds[5] = CRGB::Red;
//  FastLED.show();
//  delay(500);
//  leds[1] = CRGB::Green;
//  leds[4] = CRGB::Green;
//  FastLED.show();
//  delay(500);
//  leds[2] = CRGB::Blue;
//  leds[3] = CRGB::Blue;
//  FastLED.show();
//  delay(1000);
//  FastLED.clear();
//  FastLED.show();
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
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  if (bleGamepad.isConnected()) {  
    Serial.print("BLE connected");                         //  checking if the gamepad is connected to mobile or not
//    uncomment next lines to display the successful connection of gamepad to mobile via led
//    for (int i = 0; i < 6; i++) {
//      leds[i] = CHSV( HUE_GREEN, 255, 64);
//    }
//    FastLED.show();

//    while (millis() > time_now + period) {             //   printing the battery level
//      Serial.println("Checking Battery Level");
//      batteryLevel();
//      time_now = millis();
//    }

    if (a.acceleration.y >2.5) {                     //    taking and sending input from top left trigger
      Serial.println(F("Left Trigger"));
      bleGamepad.press(BUTTON_7);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_7);
      bleGamepad.sendReport();
    }
    if (a.acceleration.y <-2.5) {                     //    taking and sending input from top right trigger
      Serial.println(F("Right Trigger"));
      bleGamepad.press(BUTTON_8);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_8);
      bleGamepad.sendReport();
    }
    if (digitalRead(LS) == LOW) {                     //    taking and sending input from left joystick
      Serial.println(F("Left Joystick"));
      bleGamepad.press(BUTTON_14);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_14);
      bleGamepad.sendReport();
    }
////    if (digitalRead(RS) == LOW) {                     //    taking and sending input from right joystick
////      Serial.println(F("Right Joystick"));
////      Serial.println("Right Joystick");
////      bleGamepad.press(BUTTON_15);
////      bleGamepad.sendReport();
////      delay(debounceDelay);
////      bleGamepad.release(BUTTON_15);
////      bleGamepad.sendReport();
////    }

    if (digitalRead(R1) == LOW) {                     //    taking and sending input from right button 1
      Serial.println(F("Right Button 1"));
      bleGamepad.press(BUTTON_3);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_3);
      bleGamepad.sendReport();
    }
    if (digitalRead(R2) == LOW) {                     //    taking and sending input from right button 2
      Serial.println(F("Right Button 2"));
      bleGamepad.press(BUTTON_2);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_2);
      bleGamepad.sendReport();
    }
    if (digitalRead(R3) == LOW) {                     //    taking and sending input from right button 3
      Serial.println(F("Right Button 3"));
      bleGamepad.press(BUTTON_1);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_1);
      bleGamepad.sendReport();
    }
    if (digitalRead(R4) == LOW) {                     //    taking and sending input from right button 4
      Serial.println(F("Right Button 4"));
      bleGamepad.press(BUTTON_4);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_4);
      bleGamepad.sendReport();
    }

    if (digitalRead(L1) == LOW) {                     //    taking and sending input from left button 1
      Serial.println(F("Left Button 1"));
      bleGamepad.press(BUTTON_5);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_5);
      bleGamepad.sendReport();
    }
    if (digitalRead(L2) == LOW) {                       //    taking and sending input from left button 2
      bleGamepad.press(BUTTON_6);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_6);
      bleGamepad.sendReport();
    }
    if (digitalRead(L3) == LOW) {                       //    taking and sending input from left button 3
      Serial.println(F("Left Button 3"));
      bleGamepad.press(BUTTON_9);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_9);
      bleGamepad.sendReport();
    }
    if (digitalRead(L4) == LOW) {                         //    taking and sending input from left button 4
      Serial.println(F("Left Button 4"));
      bleGamepad.press(BUTTON_10);
      bleGamepad.sendReport();
    }
    else{
      bleGamepad.release(BUTTON_10);
      bleGamepad.sendReport();
    }


    // Map analog reading from 0 ~ 4095 to 32737 ~ -32737 for use as an axis reading
    int value1 = map(analogRead(LH), 0, 4095, 0, 39000);
    Serial.println(value1);
    int value2 = map(analogRead(LV), 0, 4095, 0, 39000);
    Serial.println(value2);
    bleGamepad.setLeftThumb(value1, value2);


//    int value3 = map(analogRead(RH), 0, 4095, 0, 65475);
//    int value4 = map(analogRead(RV), 0, 4095, 0, 65475);
//    bleGamepad.setRightThumb(value3, value4);

    //Send the gamepad report
    bleGamepad.sendReport();
    delay(1);
  }
  else {
//    for (int i = 0; i < 6; i++) {                 //to show that the gamepad is not connected
//      leds[i] = CHSV( 0, 0, 0);
//    }
//    FastLED.show();
    Serial.print("BLE not connected");
  }
}

//void batteryLevel() {                               //function for checking the battery level
//  int sensorValue = analogRead(ADC);
//  float voltage = sensorValue * (5.12 / 4095.0);
//  Serial.print(voltage);
//  Serial.print("V ||");
//  int percentage = (voltage / 4.2) * 100;
//  Serial.print(percentage);
//  Serial.println("%");
//  bleGamepad.setBatteryLevel(percentage);
////  if (percentage < 60) {                          //to show led if battery level is below 60%
////    Serial.println("LOW battery");
////    for (uint8_t i = 30; i < 220; i++) {
////      for (int j = 0; j < 6; j++) {
////        leds[j] = CHSV( HUE_RED, 255, i);
////      }
////      FastLED.show();
////      delay(15);
////    }
////    for (uint8_t i = 220; i > 30; i--) {          //to show led lights connected to the gamepad
////      for (int j = 0; j < 6; j++) {
////        leds[j] = CHSV( HUE_RED, 255, i);
////      }
////      FastLED.show();
////      delay(15);
////    }
