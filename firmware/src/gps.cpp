#include "gps.h"

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

// Tracks previous position for distance calculation
static float prev_lat = 0.0f;
static float prev_lon = 0.0f;
static bool has_prev = false;

void gps_init() {
    // Start Serial1 on GPIO 16 (RX) and 17 (TX) at 9600 baud
    // 9600 is the NEO-6M's default communication speed
    gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
    Serial.println("GPS initialized on GPIO 16/17");
}

void gps_update() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    // Valid = we have a fix AND data is recent (< 5 sec old)
    gps_valid = gps.location.isValid() && gps.location.age() < 5000;

    // Only refresh the stored values when a new sentence arrived
    if (gps.location.isUpdated()) {
        float current_lat = gps.location.lat();
        float current_lon = gps.location.lng();
        gps_speed_mph = gps.speed.mph();

        if (has_prev) {
            float dist_meters = TinyGPSPlus::distanceBetween(
                prev_lat, prev_lon, current_lat, current_lon
            );
            gps_distance_miles += dist_meters / 1609.34f;
        }
        prev_lat = current_lat;
        prev_lon = current_lon;
        has_prev = true;
        gps_lat = current_lat;
        gps_lon = current_lon;
    }
}
