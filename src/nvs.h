#ifndef NVS_H
#define NVS_H

#define TARGET_LAT_KEY "target_lat"
#define TARGET_LNG_KEY "target_lng"
#define TARGET_RANGE_KEY "target_range"

void nvsBegin();
void nvsEnd();
double nvsGetTargetLat(double defaultLat);
double nvsGetTargetLng(double defaultLng);
double nvsGetTargetRange(double defaultRange);
void nvsSetTargetLat(double lat);
void nvsSetTargetLng(double lng);
void nvsSetTargetRange(double range);

#endif