#include "config.h"
#include "nvs.h"
#include "oled.h"
#include "server.h"

#include <Arduino.h>
#include <ESP32Servo.h>
#include <HardwareSerial.h>
#include <OneButton.h>
#include <TinyGPS++.h>

void toggleServer();
void lock();
void unlock();
void displayInfo();
void displaySleep();
void printData();
void printNoData();
double distFromTgt(double currLat, double currLng);

int buttonState = 0;
bool targetReached = false;
bool wifiConnected = false;

TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
Servo servo;
OneButton button(BUTTON_PIN, false, false);

double targetLat;
double targetLng;
double targetRange;

void setup() {
    lock();
    Serial.begin(9600);
    gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    oledInit();

    button.setPressTicks(500);
    button.attachDoubleClick(toggleServer);
    button.attachDuringLongPress(displayInfo);
    button.attachLongPressStop(displaySleep);

    nvsBegin();
    targetLat = nvsGetTargetLat(DEFAULT_TARGET_LAT);
    targetLng = nvsGetTargetLng(DEFAULT_TARGET_LNG);
    targetRange = nvsGetTargetRange(DEFAULT_TARGET_RANGE);
    nvsEnd();

    Serial.printf("Lat: %f\n", targetLat);
    Serial.printf("Long: %f\n", targetLng);
    Serial.printf("Range: %f\n", targetRange);
}

void loop() {
    button.tick();
}

/**
 * Initializes WiFi network.
 */
void toggleServer() {
    if (!wifiConnected) {
        wifiConnected = true;
        serverSetup();
    } else {
        wifiConnected = false;
        serverClose();
    }
}

/**
 * Display location and distance from target, if available. 
 */
void displayInfo() {
    if(wifiConnected) {
        return;
    }
    bool avail = false;
    while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isValid()) {
                avail = true;
            }
        }
    }
    if (avail) {
        printData();
    } else {
        printNoData();
    }
}

/**
 * Turns display off after a delay.
 */
void displaySleep() {
    if(wifiConnected) {
        return;
    }
    oledSleep();
}

/**
 * Locks the box.
 */
void lock() {
    servo.attach(SERVO_PIN);
    servo.write(90);
    delay(1000);
    servo.detach();
}

/**
 * Unlocks the box.
 */
void unlock() {
    servo.attach(SERVO_PIN);
    servo.write(0);
    delay(1000);
    servo.detach();
    exit(0);
}

/**
 * Print current location and distance from target.
 */
void printData() {
    const double lat = gps.location.lat();
    const double lng = gps.location.lng();
    const double dist = distFromTgt(lat, lng);

    oledDisplayLocation(lat, lng);
	if (dist < targetRange) {
		oledTargetReached();
	} else {
		oledDisplayDistance(dist);
	}
}

/**
 * No GPS data available.
*/
void printNoData() {
    oledNoData();
}

/**
   * Haversine formula - https://en.wikipedia.org/wiki/Haversine_formula
*/
double distFromTgt(double currLat, double currLng) {
    double lat1 = radians(currLat);
	double lng1 = radians(currLng);
    double lat2 = radians(targetLat);
	double lng2 = radians(targetLng);
    double a = 0.5 - cos(lat2 - lat1) / 2.0 + cos(lat1) * cos(lat2) * 
            (1 - cos(lng2 - lng1)) / 2.0;
    return (2 * RADIUS * asin(sqrt(a)));
}