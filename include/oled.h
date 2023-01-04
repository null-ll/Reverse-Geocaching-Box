#ifndef OLED_H
#define OLED_H

#include <WString.h>

void oledInit();
void oledReset();
void oledDisplayLocation(const double lat, const double lng);
void oledDisplayDistance(const double dist);
void oledTargetReached();
void oledNoData();
void oledDisplayWiFi(const char *ip, bool connected);
void oledSleep();

#endif