#include <Adafruit_SSD1306.h>

void initOled(Adafruit_SSD1306 &oled) {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  oled.setTextColor(WHITE);
  oled.clearDisplay(); 
  oled.display(); 
}