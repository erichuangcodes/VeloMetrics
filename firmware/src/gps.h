#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPSPlus.h>

// GPS object — reads and parses NMEA sentences
extern TinyGPSPlus gps;

// Serial port for GPS communication
extern HardwareSerial gpsSerial;

// Functions
void gps_init();
void gps_update();

// Current GPS values (updated every loop)
extern float gps_speed_mph;
extern float gps_distance_miles;
extern float gps_lat;
extern float gps_lon;
extern bool gps_valid;

#endif