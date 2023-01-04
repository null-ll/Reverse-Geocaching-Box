#include "server.h"
#include "config.h"
#include "nvs.h"
#include "oled.h"

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

enum Parameter {
    PARAM_LAT,
    PARAM_LNG,
    PARAM_RANGE
};

String processor(const String &str);
bool writeChange(Parameter parameter, const char *str);
void notFound(AsyncWebServerRequest *request);

AsyncWebServer server(80);
String request;

/**
 * Set up webserver.
 */
void serverSetup() {
    oledReset();
    WiFi.softAP(NETWORK_SSID, PASSWORD, 1, 0, 1, false);
    oledDisplayWiFi(WiFi.softAPIP().toString().c_str(), false);
    SPIFFS.begin();
    nvsBegin();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        if (request->hasParam(TARGET_LAT_KEY)) {
            writeChange(PARAM_LAT, 
                        request->getParam(TARGET_LAT_KEY)->value().c_str());
        } 
        if (request->hasParam(TARGET_LNG_KEY)) {
            writeChange(PARAM_LNG, 
                        request->getParam(TARGET_LNG_KEY)->value().c_str());
        } 
        if (request->hasParam(TARGET_RANGE_KEY)) {
            writeChange(PARAM_RANGE, 
                        request->getParam(TARGET_RANGE_KEY)->value().c_str());
        }
        request->redirect("/");
    });
    server.onNotFound(notFound);
    server.begin();
}

/**
 * Template processor. Replaces placeholder values in HTML file.
 */
String processor(const String &str) {
    if (str == "target_lat") {
        return String(nvsGetTargetLat(DEFAULT_TARGET_LAT), ROUND_COORD);
    } else if (str == "target_lng") {
        return String(nvsGetTargetLng(DEFAULT_TARGET_LNG), ROUND_COORD);
    } else if (str == "target_range") {
        return String(nvsGetTargetRange(DEFAULT_TARGET_RANGE), ROUND_DIST);
    }
    return String();
}

/**
 * Writes valid changes to NVS.
 */
bool writeChange(Parameter param, const char *str) {
    char* end = 0;
    double value = strtod(str, &end);
    if(*end != '\0' || end == str) {
        return false;
    }

    if (param == PARAM_LAT) {
        nvsSetTargetLat(value);
        targetLat = value;
    } else if (param == PARAM_LNG) {
        nvsSetTargetLng(value);
        targetLng = value;
    } else if (param == PARAM_RANGE) {
        nvsSetTargetRange(value);
        targetRange = value;
    }
    return true;
}

/**
 * Invalid request.
 */
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Page not found");
}

/**
 * Closes webserver.
 */
void serverClose() {
    server.end();
    nvsEnd();
    oledSleep();
}