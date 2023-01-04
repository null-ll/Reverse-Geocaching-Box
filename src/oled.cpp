#include "oled.h"
#include "config.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
const int charWidth = 5, charHeight = 7;

int centerAlign(int length) {
    return (OLED_WIDTH - charWidth * length) / 2;
}

void oledInit() {
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oledSleep();
}

void oledReset() {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
}

void oledDisplayLocation(const double lat, const double lng) {
    oledReset();

    // Print latitude
    oled.setCursor(15, 5);
    oled.print("LAT: ");
    oled.setCursor(50, 5);
    oled.print(lat, ROUND_COORD);
    
    // Print longitude
    oled.setCursor(15, 15);
    oled.print("LNG: ");
    oled.setCursor(50, 15);
    oled.print(lng, ROUND_COORD);
}

void oledDisplayDistance(const double dist) {
    oled.setCursor(15, 25);
    oled.print("DIST: ");
    oled.setCursor(50, 25);
    oled.print(dist, ROUND_DIST);
    oled.print("m");
    oled.display();
}

void oledTargetReached() {
    String msg = "Location reached!";
    oled.setCursor(centerAlign(msg.length()), 25);
    oled.print(msg);
    oled.display();
}

void oledNoData() {
    oledReset();
    String msg = "No GPS data";
    oled.setCursor(msg.length(), 15);
    oled.print(msg);
    oled.display();
}

void oledDisplayWiFi(const char *ip, bool connected) {
    oled.clearDisplay();
    String msg = "Connection avail";
    oled.setCursor(centerAlign(msg.length()), 10);
    oled.print(msg);
    oled.setCursor(centerAlign(strlen(ip)), 20);
    oled.print(ip);
    oled.display();
}

void oledSleep() {
    oled.clearDisplay();
    oled.display();
}