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
    // Read all available bytes from the GPS module
    // and feed them into TinyGPS++ for parsing
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    // Only update values if GPS has a valid fix
    if (gps.location.isValid() && gps.location.isUpdated()) {
        gps_valid = true;

        // Get current coordinates
        float current_lat = gps.location.lat();
        float current_lon = gps.location.lng();

        // Update speed — TinyGPS++ gives speed in knots, convert to mph
        // 1 knot = 1.15078 mph
        gps_speed_mph = gps.speed.mph();

        // Calculate distance traveled since last position
        if (has_prev) {
            // TinyGPS++ has a built-in distance function
            // distanceBetween() returns meters
            float dist_meters = TinyGPSPlus::distanceBetween(
                prev_lat, prev_lon,
                current_lat, current_lon
            );

            // Convert meters to miles (1 mile = 1609.34 meters)
            gps_distance_miles += dist_meters / 1609.34f;
        }

        // Save current position as previous for next update
        prev_lat = current_lat;
        prev_lon = current_lon;
        has_prev = true;

        // Store coordinates for the map
        gps_lat = current_lat;
        gps_lon = current_lon;
    } else {
        gps_valid = false;
    }
}