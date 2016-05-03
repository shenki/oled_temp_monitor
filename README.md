# Temperature monitor

This sketch reads the temperature from a DHT22 temperature/humidity module and
displays the current temperature on a D1306 compatible 128x64 OLED LCD display.

It has been tested on a NodeMCU 1.0 with Arduino 1.6.9.

Note that the temperature sensor needed to be unpowered in order for
programming to succeed.

## Wiring

| Signal| Pin |
| ----- | --- |
| SDA   | D2  |
| SCL   | D4  |
| DHT22 | D8  |

![Wiring diagram][diagram]

[diagram]: https://raw.githubusercontent.com/shenki/oled_temp_monitor/master/oled_temp_monitor.png

## Licence

The files I created are Apache 2.0.

The SSD1306 library is MIT.

The DHT library is MIT.
