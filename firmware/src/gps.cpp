#include "gps.h"
#include <cmath>

// The GPS parser object
TinyGPSPlus gps;

// Serial port for GPS communication
// ESP32-S3 has multiple hardware serial ports — we use Serial1
HardwareSerial gpsSerial(1);

// Current values
float gps_speed_mph = 0.0f;
float gps_distance_miles = 0.0f;
float gps_lat = 0.0f;
float gps_lon = 0.0f;
bool gps_valid = false;
int gps_local_hour = 0;
int gps_local_minute = 0;

// Tracks previous position for distance calculation
static float prev_lat = 0.0f;
static float prev_lon = 0.0f;
static bool has_prev = false;

void gps_init() {
    // Start Serial1 on GPIO 16 (RX) and 17 (TX) at 9600 baud
    // 9600 is the NEO-6M's default communication speed
    gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
    Serial.println("GPS initialized on GPIO 16/17");
    uint8_t setRate5Hz[] = {
        0xB5, 0x62, 0x06, 0x08, 0x06, 0x00,
        0xC8, 0x00, 0x01, 0x00, 0x01, 0x00,
        0xDE, 0x6A
    };
    gpsSerial.write(setRate5Hz, sizeof(setRate5Hz));
}

#define GPS_SPEED_DEADBAND_MPH 1.0f //Makes anything below 1mph not really moving
#define GPS_DISTANCE_DEADBAND_METERS 1.5f // makes anything below 1.5 meteres not actually moving
void gps_update() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    // Valid = we have a fix AND data is recent ( 2.5 sec old)
    gps_valid = gps.location.isValid() && gps.location.age() < 2500;

    // Only refresh the stored values when a new sentence arrived
    if (gps.location.isUpdated()) {
        float current_lat = gps.location.lat();
        float current_lon = gps.location.lng();
        float real_speed = gps.speed.mph();
        
        if (real_speed < GPS_SPEED_DEADBAND_MPH) {
            gps_speed_mph = 0.0f;
        }
        else { 
            gps_speed_mph = real_speed;
        }

        if (has_prev) {
            float dist_meters = TinyGPSPlus::distanceBetween(
                prev_lat, prev_lon, current_lat, current_lon
            );
            if (dist_meters >= GPS_DISTANCE_DEADBAND_METERS) {
                gps_distance_miles += dist_meters / 1609.34f;   
            }
        }
        prev_lat = current_lat;
        prev_lon = current_lon;
        has_prev = true;
        gps_lat = current_lat;
        gps_lon = current_lon;
    }


    //Time function for local time
    if (gps.time.isValid() && gps.location.isValid()) {
        float lon_value = gps_lon/15.0f;
        int offset = (int)round(lon_value);
        int raw_hour = gps.time.hour();
        gps_local_hour = (raw_hour + 24) % 24;
        gps_local_minute = gps.time.minute();
    }

}
