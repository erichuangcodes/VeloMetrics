// ui.h
#ifndef UI_H
#define UI_H

#include <lvgl.h>

// Screens & Containers
extern lv_obj_t *home_screen;
extern lv_obj_t *stats_screen;
extern lv_obj_t *map_screen;
extern lv_obj_t *settings_screen;
extern lv_obj_t *header_container;

// Dynamic Labels
extern lv_obj_t *speed_label;
extern lv_obj_t *unit_label;
extern lv_obj_t *time_label;
extern lv_obj_t *distance_label;

extern lv_obj_t *avg_speed_label;
extern lv_obj_t *max_speed_label;
extern lv_obj_t *calories_label;
extern lv_obj_t *elevation_label_stats;

extern lv_obj_t *battery_label;
extern lv_obj_t *bluetooth_label;
extern lv_obj_t *temp_label;
extern lv_obj_t *localtime_label;

extern lv_obj_t *position_dot;

extern lv_obj_t *screensaver;

// Mock Data
extern int fake_battery;
extern int fake_temp;
extern float fake_avg_speed;
extern float fake_max_speed;
extern int fake_elevation;
extern int fake_calories;

// Functions main.cpp needs to call
void create_global_header();
void build_home_screen();
void build_stats_screen();
void build_map_screen();
void switch_screen();
void switch_screen_back();
void add_screen_dots(lv_obj_t *screen, int active_index);
void gps_to_pixel(float lat, float lon, int *px, int *py);
void update_map();
void update_ui();

#ifdef __cplusplus
extern "C" {
#endif

LV_FONT_DECLARE(Exo_12_Regular);
LV_FONT_DECLARE(Exo_18_Regular);
LV_FONT_DECLARE(Exo_24_Regular);
LV_FONT_DECLARE(Orbitron_24_Regular);
LV_FONT_DECLARE(Orbitron_36_Regular);
LV_FONT_DECLARE(Orbitron_48_Regular);
LV_FONT_DECLARE(Orbitron_72_Regular);

#ifdef __cplusplus
}
#endif

#endif