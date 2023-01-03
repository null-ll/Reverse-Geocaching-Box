#ifndef CONFIG_H
#define CONFIG_H

#define NETWORK_SSID "box"
#define PASSWORD "01234567"

#define EEPROM_SIZE 12

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define GPS_BAUD 9600

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define SERVO_PIN 35
#define BUTTON_PIN 27

#define RADIUS 6371000.0   // radius of the Earth
#define ROUND_COORD 6

#define GPS_TIMEOUT 1000
#define DISPLAY_TIMEOUT 5000
#define WIFI_TIMEOUT 15000

#define DEFAULT_TARGET_LAT 30.327178
#define DEFAULT_TARGET_LNG -97.808992
#define DEFAULT_TARGET_RANGE 500.0

extern double targetLat;
extern double targetLng;
extern double targetRange;

#endif