#include <Arduino.h>

#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <LittleFS.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "helper/init.hpp"
#include "helper/oled/loading.hpp"

// #define ssid "nokt"
// #define password "samn1111"
#define ssid "D-Link"
#define password "4209368970"

bool isLoading = false;

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

WebServer server(3000);

OledLoader loader(oled);

void setup()
{
  Serial.begin(9600);
  initOled(oled);

  loader.update();
  if (!LittleFS.begin(true))
  {
    Serial.println("LittleFS Mount Failed!");
    return;
  }

  Serial.println("LittleFS mounted!");

  File root = LittleFS.open("/");

  File file = root.openNextFile();

  while (file)
  {
    Serial.print("FILE: ");
    Serial.print(file.name());
    Serial.print(" | SIZE: ");
    Serial.println(file.size());

    file = root.openNextFile();
  }

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    loader.update();
  }

  Serial.println();
  Serial.println("WiFi connected!");

  server.serveStatic("/", LittleFS, "/");

  server.begin();
  Serial.println("Server started!");

  IPAddress myip = WiFi.localIP();
  Serial.print("ESP32 IP address: ");
  Serial.println(myip);

  oled.clearDisplay();
  oled.setCursor(25, 20);
  oled.println("Server Ready");
  oled.setCursor(20, 35);
  oled.println(myip);
  oled.display();
}

void loop()
{
  server.handleClient();

  if (isLoading)
  {
    loader.update();
  }
  else
  {
    float temperature = temperatureRead();

    oled.setTextSize(1);
    oled.setCursor(3, 55);

    oled.print(temperature);
    oled.print(" C");

    oled.display();
  }
}