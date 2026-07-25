#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <TinyGPSPlus.h>

// Include UI screens
#include "ui.h"
#include "gps.h"

// Create the TFT display driver
TFT_eSPI tft = TFT_eSPI();

// LVGL drawing buffer 240 by 10 
#define DRAW_BUF_SIZE (240 * 10 * 2); // 240 pixels * 10 rows * 2 bytes per pixel
alignas(4) static uint8_t lv_draw_buf[240 * 10 *2];

// Flush callback sends pixels from LVGL buffer to the physical LCD
void my_flush_callback(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)px_map, w * h, true);
    tft.endWrite();

    lv_display_flush_ready(disp);
}


void setup() {
    Serial.begin(115200);
    gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
    Serial.println("GPS test starting...");
}

void loop() {
    while (gpsSerial.available() > 0) {
        char c = gpsSerial.read();
        Serial.write(c);  // Print raw GPS data to Serial Monitor
        gps.encode(c);
    }

    if (gps.location.isUpdated()) {
        Serial.print("LAT: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("LON: ");
        Serial.println(gps.location.lng(), 6);
        Serial.print("SPEED: ");
        Serial.println(gps.speed.mph());
        Serial.print("SATELLITES: ");
        Serial.println(gps.satellites.value());
    }

    delay(100);
}