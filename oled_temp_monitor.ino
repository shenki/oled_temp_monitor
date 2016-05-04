#include <Wire.h>

#include "DHT.h"
#include "SSD1306.h"

#define DHTPIN D7

#define OLED_SDA    D2  // pin 14
#define OLED_SDC    D4  // pin 12
#define OLED_ADDR   0x3C

SSD1306 display(OLED_ADDR, OLED_SDA, OLED_SDC);
DHT dht(DHTPIN, DHT22);

float h, t;
int i;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting " __DATE__ " " __TIME__ "...");

  display.init();
  display.clear();
  
  display.drawString(0, 0, "Booting...");
  display.display();

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

  if (i == 5) {
    i = 0;
    display.clear();
  }
  delay(4000);
}
