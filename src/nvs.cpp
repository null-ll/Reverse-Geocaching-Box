#include "nvs.h"

#include <Preferences.h>

Preferences preferences;

void nvsBegin() {
    preferences.begin("box", false);
}

void nvsEnd() {
    preferences.end();
}

double nvsGetTargetLat(double defaultLat) {
    return preferences.getDouble(TARGET_LAT_KEY, defaultLat);
}

double nvsGetTargetLng(double defaultLng) {
    return preferences.getDouble(TARGET_LNG_KEY, defaultLng);
}

double nvsGetTargetRange(double defaultRange) {
    return preferences.getDouble(TARGET_RANGE_KEY, defaultRange);
}

void nvsSetTargetLat(double lat) {
    preferences.putDouble(TARGET_LAT_KEY, lat);
}

void nvsSetTargetLng(double lng) {
    preferences.putDouble(TARGET_LNG_KEY, lng);
}

void nvsSetTargetRange(double range) {
    preferences.putDouble(TARGET_RANGE_KEY, range);
}