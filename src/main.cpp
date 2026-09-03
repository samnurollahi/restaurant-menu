#include <Arduino.h>
#include <Wire.h> //* for I2C communication

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "helper/init.hpp"

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);

  initOled(oled); //* initialize the OLED display
}

void loop() {
} 
