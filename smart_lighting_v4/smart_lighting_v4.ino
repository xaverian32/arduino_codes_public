#define BLYNK_TEMPLATE_ID "TMPL35Bk-qvwJ"
#define BLYNK_TEMPLATE_NAME "JU PROJ"
#define BLYNK_AUTH_TOKEN "becc2SqlR-56o4nOz4ZI9ukxIHEhJoho"


#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>



char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "your_SSID";     // Replace with your WiFi SSID
char pass[] = "your_PASSWORD"; // Replace with your WiFi password

const int PIR_PIN = 25; // PIR sensor connected to GPIO 25
const int LDR_PIN = 34; // LDR connected to GPIO 34 (analog input)
const int LED_PIN = 26; // LED connected to GPIO 26 (PWM output)

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

BlynkTimer timer;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
   pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, sendSensorData);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME");
  delay(5000);
}

void loop() {
  Blynk.run();
  timer.run();

  int pirState = digitalRead(PIR_PIN); // Read the PIR sensor state
  int ldrValue = analogRead(LDR_PIN);  // Read the LDR value (0 to 4095)
  int brightness = calculateBrightness(pirState, ldrValue);

  analogWrite(LED_PIN, brightness);


  if (pirState > 0 && ldrValue < 3000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LIGHTS");
    lcd.setCursor(0, 1);
    lcd.print("ON");
    analogWrite(LED_PIN, brightness);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LIGHTS");
    lcd.setCursor(0, 1);
    lcd.print("OFF");
     analogWrite(LED_PIN, 0);
  }
}

void sendSensorData() {
  int pirState = digitalRead(PIR_PIN); // Read the PIR sensor state
  int ldrValue = analogRead(LDR_PIN);  // Read the LDR value (0 to 4095)
  int brightness = calculateBrightness(pirState, ldrValue);

  analogWrite(LED_PIN, brightness);

  Blynk.virtualWrite(V1, pirState);
  Blynk.virtualWrite(V2, ldrValue);
  Blynk.virtualWrite(V3, brightness);

  Serial.printf("PIR: %d, LDR: %d, Brightness: %d\n", pirState, ldrValue, brightness);


}
int calculateBrightness(int presence, int light) {
  int baseBrightness = 255;

  if (presence == HIGH) {
    if (light < 1000) {
      baseBrightness = 255;
    } else if (light < 3000) {
      baseBrightness = 128;
    } else {
      baseBrightness = 50;
    }
  } else {
    baseBrightness = 0;
  }

  return baseBrightness;
}

  BLYNK_WRITE(V0) {
    int pirState = digitalRead(PIR_PIN); // Read the PIR sensor state
  int ldrValue = analogRead(LDR_PIN);  // Read the LDR value (0 to 4095)
    int brightness = calculateBrightness(pirState, ldrValue);

  int buttonState = param.asInt(); // Get the value from the button
  Serial.print("Button state: ");
  Serial.println(buttonState);
  // Implement your logic here based on the button state
  if ( buttonState== 1){
   // do something when button is pressed;
       analogWrite(LED_PIN, brightness);
  } else if (buttonState == 0) {
   // do something when button is released;
       analogWrite(LED_PIN, 0);
  }
}
