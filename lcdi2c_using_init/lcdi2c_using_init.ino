#include <Wire.h>  // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library

// Set the LCD address (you may need to adjust this depending on your module)
#define LCD_ADDRESS 0x3F

// Set the LCD dimensions (16x2 or 20x4, etc.)
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Create an instance of the LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight (if available on your module)
  lcd.backlight();

  // Print a message to the LCD
  lcd.setCursor(0, 0);  // Set cursor to first column and first row
  lcd.print("Hello, World!");
}

void loop() {
  // Nothing needed here unless you want to continuously update the display
}
