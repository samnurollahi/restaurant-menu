#include <Arduino.h>

#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "helper/init.hpp"
#include "helper/oled/loading.hpp"

#define ssid "samRes"
#define password "123456789"

bool isLoading = false;

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
WiFiServer server(3000);

OledLoader loader(oled);

void setup() {
    Serial.begin(9600);
    initOled(oled);

    loader.update();
    bool apStarted = WiFi.softAP(ssid, password);
    if (!apStarted) {
        Serial.println("SoftAP failed!");

        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setCursor(30, 30);
        oled.println("AP Failed");
        oled.display();

        return;
    }

    IPAddress myip = WiFi.softAPIP(); 
    server.begin();

    Serial.println("Server started!");
    Serial.print("AP IP address: ");
    Serial.println(myip);


    oled.clearDisplay();
    oled.setCursor(25, 20);
    oled.println("Server Ready");
    oled.setCursor(20, 35);
    oled.println(myip);
    oled.display();

}

void loop() {

  if(isLoading) 
    loader.update();
  else {

    float temperature = temperatureRead();
    Serial.println(temperature);
    oled.setTextSize(1);
    oled.setCursor(3, 55);
    oled.print((String)temperature);
    oled.print(" C");
    oled.display();

  }
}