#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

// Include your UI screens
#include "ui.h"

// Create the TFT display driver
TFT_eSPI tft = TFT_eSPI();

// LVGL drawing buffer (240 pixels wide, 10 rows at a time)
#define DRAW_BUF_SIZE (240 * 10 * 2); // 240 pixels * 10 rows * 2 bytes per pixel (16-bit color)
alignas(4) static uint8_t lv_draw_buf[240 * 10 *2];

// Flush callback — sends pixels from LVGL buffer to the physical LCD
// LVGL v9 uses lv_display_t instead of lv_disp_drv_t
// LVGL v9 passes pixels as uint8_t* instead of lv_color_t*
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

    build_home_screen();
    build_stats_screen();
    add_screen_dots(home_screen, 0);
    add_screen_dots(stats_screen, 1);
    lv_scr_load(home_screen);

    Serial.println("Setup complete!");
}

void loop() {
    lv_timer_handler();
    delay(5);
}