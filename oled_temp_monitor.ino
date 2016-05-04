#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"
#include "SSD1306.h"
#include "wifi_settings.h"

#define DHTPIN D7

#define OLED_SDA    D2  // pin 14
#define OLED_SDC    D4  // pin 12
#define OLED_ADDR   0x3C

SSD1306 display(OLED_ADDR, OLED_SDA, OLED_SDC);
DHT dht(DHTPIN, DHT22);

float h, t;
int i;

// URL to perform GET action on. This is for Domoticz, device ID 1
const char url[] = "http://192.168.1.164:8080/json.htm?type=command&param=udevice&idx=1&nvalue=0&svalue=";

#if !defined(WIFI_SSID) || !defined(WIFI_PASSPHRASE)
#error Please set SSID and passphrase
#endif

void setup() {
  Serial.begin(115200);
  Serial.println("Booting " __DATE__ " " __TIME__ "...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSPHRASE);

  display.init();
  display.clear();

  display.drawString(0, 0, "Booting...");
  display.display();

  delay(1000);

  pinMode(DHTPIN, INPUT_PULLUP);
  dht.begin();

  display.drawString(0, 12, __DATE__ " " __TIME__);
  display.display();

  i = 2;
}

void loop() {
  t = dht.readTemperature();
  display.drawString(0, 12 * i, String(t, 1) + "°C");
  display.display();
  i++;

  // With a spacing of 12, 5 lines display comfortably on the screen
  if (i == 5) {
    i = 0;
    display.clear();
  }

  if (!isnan(t)) {
    HTTPClient http;
    String http_url = url +  String(t, 1);

    http.begin(http_url);
    Serial.println(http_url);
    http.GET();
  }

  // Delay for 300 seconds (5 minutes). Reduce this when debugging
  delay(300000);
}
