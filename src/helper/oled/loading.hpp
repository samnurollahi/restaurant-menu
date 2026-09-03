#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

class OledLoader {
private:
    Adafruit_SSD1306 &oled;

    int centerX;
    int centerY;
    int radius;

    uint8_t step = 0;

public:
    OledLoader(
        Adafruit_SSD1306& display,
        int x = 64,
        int y = 28,
        int r = 18
    )
        : oled(display),
          centerX(x),
          centerY(y),
          radius(r) {}

    void update() {
        oled.clearDisplay();

    
        const int dots = 8;

        for (int i = 0; i < dots; i++) {

            float angle =
                (i * 2.0 * PI / dots) - (PI / 2);

            int x = centerX + cos(angle) * radius;
            int y = centerY + sin(angle) * radius;

            int distance = (i - step + dots) % dots;

            if (distance == 0) {
                oled.fillCircle(x, y, 4, SSD1306_WHITE);
            }
            else if (distance == 1) {
                oled.fillCircle(x, y, 3, SSD1306_WHITE);
            }
            else if (distance == 2) {
                oled.fillCircle(x, y, 2, SSD1306_WHITE);
            }
            else {
                oled.fillCircle(x, y, 1, SSD1306_WHITE);
            }
        }

        oled.setTextSize(1);
        oled.setTextColor(SSD1306_WHITE);

        oled.display();

        step++;

        if (step >= dots) {
            step = 0;
        }
        delay(100);
    }
};