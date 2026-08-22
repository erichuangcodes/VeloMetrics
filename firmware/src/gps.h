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
extern float gps_max_speed_mph;
extern float gps_avg_speed_mph;
extern float gps_lat;
extern float gps_lon;
extern bool gps_valid;
extern int gps_local_hour;
extern int gps_local_minute;


extern uint32_t session_start_time; // Start ride
extern bool session_active;
extern uint32_t session_elapsed_ms;
void gps_start_session();
void gps_stop_session();

#endif