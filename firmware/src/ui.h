#ifndef UI_H
#define UI_H

#include <lvgl.h>

// Screen objects (so main.cpp can access them)
extern lv_obj_t *home_screen;
extern lv_obj_t *stats_screen;

// Functions main.cpp needs to call
void build_home_screen();
void build_stats_screen();
void switch_screen();
void add_screen_dots(lv_obj_t *screen, int active_index);
void update_ui();

#endif