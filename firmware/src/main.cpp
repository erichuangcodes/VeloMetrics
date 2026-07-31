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
    Serial.println("VeloMetrics starting...");

    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(0);

    lv_init();

    // Initialize the LVGL display driver
    lv_display_t *disp = lv_display_create(240, 320);
    lv_display_set_flush_cb(disp, my_flush_callback);
    lv_display_set_buffers(disp, lv_draw_buf, NULL, sizeof(lv_draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    create_global_header();
    build_home_screen();
    build_stats_screen();
    build_map_screen();
    add_screen_dots(home_screen, 0);
    add_screen_dots(stats_screen, 1);
    add_screen_dots(map_screen, 2);
    lv_scr_load(home_screen);

    delay(1000);
    gps_init();

    Serial.println("Setup complete");
}

void loop() {
    gps_update();
    
    // Debug — print every 2 seconds
    static uint32_t last_print = 0;
    if (millis() - last_print > 2000) {
        Serial.print("gps_valid: ");
        Serial.println(gps_valid ? "TRUE" : "FALSE");
        Serial.print("satellites: ");
        Serial.println(gps.satellites.value());
        last_print = millis();
    }
    
    lv_timer_handler();
    delay(5);
}
