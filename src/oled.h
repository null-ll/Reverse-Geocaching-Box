#ifndef OLED_H
#define OLED_H

#include <IPAddress.h>

void oledInit();
void oledReset();
void oledDisplayLocation(const double lat, const double lng);
void oledDisplayDistance(const double dist);
void oledTargetReached();
void oledNoData();
void oledWiFiInit();
void oledDisplayWiFi(IPAddress ip, bool connected);
void oledSleep();

#endif