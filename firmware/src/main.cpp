#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <TinyGPSPlus.h>

// Include UI screens
#include "ui.h"
#include "gps.h"

#define frontbutton 4
#define backbutton 5
#define startsessionbutton 6


// Create the TFT display driver
TFT_eSPI tft = TFT_eSPI();

uint32_t my_tick_get_cb(void) {
    return millis();
}

// LVGL drawing buffer 240 by 10 
#define DRAW_BUF_SIZE (240 * 10 * 2) // 240 pixels * 10 rows * 2 bytes per pixel
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
    delay(100);
    Serial.println("VeloMetrics starting...");
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(0);

    lv_init();
    lv_tick_set_cb(my_tick_get_cb); // Set the tick callback for LVGL

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
    Serial.println("dots done");
    lv_scr_load(home_screen);
  

    delay(1000);
    gps_init();
    Serial.println("gps init done");

    pinMode(frontbutton, INPUT_PULLUP);
    pinMode(backbutton, INPUT_PULLUP);
    pinMode(startsessionbutton, INPUT_PULLUP);
}

void loop() {
    gps_update();
    update_ui();
    
    // Debug — print every 2 seconds
    static uint32_t last_print = 0;
    if (millis() - last_print > 2000) {
        Serial.print("gps_valid: ");
        Serial.println(gps_valid ? "TRUE" : "FALSE");
        Serial.print("satellites: ");
        Serial.println(gps.satellites.value());
        Serial.print(" | lat: ");
        Serial.print(gps_lat, 6);
        Serial.print(" | lon: ");
        Serial.print(gps_lon, 6);
        Serial.print(" | speed_mph: ");
        Serial.print(gps_speed_mph, 1);
        Serial.print(" | distance_mi: ");
        Serial.println(gps_distance_miles, 3);
        last_print = millis();
    }
    
    static bool last_frontbutton_state = HIGH;
    static uint32_t last_frontbuttonpress_time =0;
    bool current_frontbutton_state = digitalRead(frontbutton);

    if (current_frontbutton_state == LOW && last_frontbutton_state == HIGH) {
        if (millis() - last_frontbuttonpress_time > 200) {
            switch_screen();
            last_frontbuttonpress_time = millis();
        }
    }
    last_frontbutton_state = current_frontbutton_state;

    static bool last_backbutton_state = HIGH;
    static uint32_t last_backbuttonpresstime = 0;
    bool current_backbutton_state = digitalRead(backbutton);

    if (current_backbutton_state == LOW && last_backbutton_state == HIGH) {
        if (millis() - last_backbuttonpresstime > 200) {
            switch_screen_back();
            last_backbuttonpresstime = millis();
        }
    }
    last_backbutton_state = current_backbutton_state;

    static bool last_startsessionbutton_state = HIGH;
    static uint32_t last_startsessionbuttonpress_time = 0;
    bool current_startsessionbutton_state = digitalRead(startsessionbutton);
    if (current_startsessionbutton_state == LOW && last_startsessionbutton_state == HIGH) {
        if (millis()- last_startsessionbuttonpress_time > 200) {
            if (!session_active) {
                gps_start_session();
            } else {
                gps_stop_session();
            }
            last_startsessionbuttonpress_time = millis();
                }

            }
    last_startsessionbutton_state = current_startsessionbutton_state;





    lv_timer_handler();
    delay(5);
        }





    
