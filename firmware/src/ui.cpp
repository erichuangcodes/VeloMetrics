/*  This is the VeloMetrics UI Screen.
    It is coded using C++ and the LVGL library for user interface development. 
    The UI is designed to display information related to the VeloMetrics bike computer.
    Includes ------
*/

#include <lvgl.h>
#include "ui.h"

//POINTERS FOR OBJECTS ON SCREEN 

// Screen objects
lv_obj_t *home_screen = NULL;
lv_obj_t *stats_screen = NULL;
lv_obj_t *map_screen = NULL;
lv_obj_t *settings_screen = NULL;
lv_obj_t *header_container = NULL;

// Dynamic Labels - Home Screen 
lv_obj_t *speed_label = NULL;
lv_obj_t *unit_label = NULL;
lv_obj_t *time_label = NULL;
lv_obj_t *distance_label = NULL;

// Dynamic Labels - Stats Screen 
lv_obj_t *avg_speed_label = NULL;
lv_obj_t *max_speed_label = NULL;
lv_obj_t *calories_label = NULL;
lv_obj_t *elevation_label_stats = NULL;

// Dynamic Labels - Header Bar
lv_obj_t *battery_label = NULL;
lv_obj_t *bluetooth_label = NULL;
lv_obj_t *temp_label = NULL;
lv_obj_t *localtime_label = NULL;

static lv_obj_t *home_dot;
static lv_obj_t *stats_dot;
static lv_obj_t *settings_dot;

// Testing / Mock Data Values
float fake_speed = 6.7f;
float fake_distance = 16.7f;
int fake_battery = 68;
int fake_temp = 35;
float fake_avg_speed = 14.2f;
float fake_max_speed = 22.8f;
int fake_elevation = 320;
int fake_calories = 187;


//GPS


#define MAX_TRAIL_POINTS 500

typedef struct {
    float lat;
    float lon; 
}
GpsPoint;

GpsPoint trail[MAX_TRAIL_POINTS];
int trail_count = 0;

lv_obj_t *position_dot = NULL;

float fake_route_lat[] = {
    40.7128, 40.7130, 40.7133, 40.7136, 40.7138,
    40.7138, 40.7136, 40.7133, 40.7130, 40.7128,
    40.7126, 40.7124, 40.7122, 40.7122, 40.7124,
    40.7126, 40.7128
};

float fake_route_lon[] = {
    -74.0060, -74.0055, -74.0050, -74.0045, -74.0040,
    -74.0035, -74.0030, -74.0028, -74.0025, -74.0022,
    -74.0022, -74.0025, -74.0030, -74.0040, -74.0048,
    -74.0055, -74.0060
};
int fake_route_length = 17;
int fake_route_index = 0;





void create_global_header() {
    lv_obj_t *sys_layer = lv_layer_sys();

    lv_obj_remove_flag(sys_layer, LV_OBJ_FLAG_CLICKABLE); // Make the system layer non clickable

    header_container = lv_obj_create(sys_layer);
    lv_obj_set_size(header_container, 240, 32);
    lv_obj_align(header_container, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_set_style_bg_color(header_container, lv_color_hex(0xF8FAFC), 0);
    lv_obj_set_style_bg_opa(header_container, LV_OPA_COVER, 0);

    lv_obj_set_style_pad_all(header_container, 0, 0);
    lv_obj_set_style_radius(header_container, 0, 0);
    lv_obj_set_style_border_width(header_container, 0, 0);

    
    //Header Labels

    localtime_label = lv_label_create(header_container);
    lv_label_set_text(localtime_label, "12:34");
    lv_obj_set_style_text_font(localtime_label, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(localtime_label, lv_color_black(), 0);
    lv_obj_align(localtime_label, LV_ALIGN_TOP_LEFT, 10, 8);

    temp_label = lv_label_create(header_container);
    lv_label_set_text(temp_label, "35 C");
    lv_obj_set_style_text_font(temp_label, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(temp_label, lv_color_black(), 0);
    lv_obj_align(temp_label, LV_ALIGN_TOP_MID, 0, 8);

    battery_label = lv_label_create(header_container);
    lv_label_set_text(battery_label, "68%");
    lv_obj_set_style_text_font(battery_label, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(battery_label, lv_color_black(), 0);
    lv_obj_align(battery_label, LV_ALIGN_TOP_RIGHT, -10, 8);

}




//Home screen function

void build_home_screen() {

    home_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(home_screen, lv_color_hex(0xF8FAFC), 0);
    lv_obj_set_style_bg_opa(home_screen, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(home_screen, 0, 0);
    lv_obj_set_style_border_width(home_screen, 0, 0);
    lv_obj_set_style_radius(home_screen, 0, 0);

    // Horizontal divider at y=170 (raised from 200)
    lv_obj_t *divider = lv_line_create(home_screen);
    static lv_point_precise_t divider_points[] = {{0, 0}, {240, 0}};
    lv_line_set_points(divider, divider_points, 2);
    lv_obj_set_style_line_color(divider, lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_line_width(divider, 2, 0);
    lv_obj_set_pos(divider, 0, 170);

    // Vertical divider splitting labels from values
    // Spans y=170 to y=290 (120px tall)
    lv_obj_t *vert_divider = lv_line_create(home_screen);
    static lv_point_precise_t vert_points[] = {{0, 0}, {0, 120}};
    lv_line_set_points(vert_divider, vert_points, 2);
    lv_obj_set_style_line_color(vert_divider, lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_line_width(vert_divider, 2, 0);
    lv_obj_set_pos(vert_divider, 90, 170);

    // ================================================================
    // SPEED SECTION (y=32 to y=170)
    // Center of section = 32 + (138/2) = 101
    // Orbitron 48 is roughly 55px tall
    // So top of number = 101 - 27 = 74
    // ================================================================

    speed_label = lv_label_create(home_screen);
    lv_label_set_text(speed_label, "6.7");
    lv_obj_set_style_text_font(speed_label, &Orbitron_72_Regular, 0);
    lv_obj_set_style_text_color(speed_label, lv_color_black(), 0);
    lv_obj_set_pos(speed_label, 10, 74);

    // mi/h label — top right, teal
    unit_label = lv_label_create(home_screen);
    lv_label_set_text(unit_label, "mi/h");
    lv_obj_set_style_text_font(unit_label, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(unit_label, lv_color_hex(0x00BCD4), 0);
    lv_obj_align(unit_label, LV_ALIGN_TOP_RIGHT, -10, 40);

    // ================================================================
    // BOTTOM LEFT — labels (y=170 to y=290, x=0 to x=90)
    // Two rows, each 60px tall
    // Row 1 center: 170 + 30 = 200, Row 2 center: 170 + 90 = 260
    // Exo_12 is ~14px tall, so top = center - 7
    // Row 1 label top: 193, Row 2 label top: 253
    // ================================================================

    lv_obj_t *distance_title = lv_label_create(home_screen);
    lv_label_set_text(distance_title, "DISTANCE");
    lv_obj_set_style_text_font(distance_title, &Exo_12_Regular, 0);
    lv_obj_set_style_text_color(distance_title, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_pos(distance_title, 8, 193);

    lv_obj_t *time_title = lv_label_create(home_screen);
    lv_label_set_text(time_title, "TIME");
    lv_obj_set_style_text_font(time_title, &Exo_12_Regular, 0);
    lv_obj_set_style_text_color(time_title, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_pos(time_title, 8, 253);

   
    // BOTTOM RIGHT — values (y=170 to y=290, x=90 to x=240)
    // Exo_24 is ~28px tall
    // Row 1 value center: 200, top = 200 - 14 = 186
    // Row 2 value center: 260, top = 260 - 14 = 246


    distance_label = lv_label_create(home_screen);
    lv_label_set_text(distance_label, "16.7 mi");
    lv_obj_set_style_text_font(distance_label, &Exo_24_Regular, 0);
    lv_obj_set_style_text_color(distance_label, lv_color_black(), 0);
    lv_obj_set_pos(distance_label, 98, 186);

    time_label = lv_label_create(home_screen);
    lv_label_set_text(time_label, "1:07:59");
    lv_obj_set_style_text_font(time_label, &Exo_24_Regular, 0);
    lv_obj_set_style_text_color(time_label, lv_color_black(), 0);
    lv_obj_set_pos(time_label, 98, 246);
}


//Stats screen function

void build_stats_screen() {

    stats_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(stats_screen, lv_color_hex(0xF8FAFC), 0);
    lv_obj_set_style_bg_opa(stats_screen, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(stats_screen, 0, 0);
    lv_obj_set_style_border_width(stats_screen, 0, 0);
    lv_obj_set_style_radius(stats_screen, 0, 0);

    // Main horizontal divider at y=185
    lv_obj_t *horiz_divider = lv_line_create(stats_screen);
    static lv_point_precise_t horiz_points[] = {{0, 0}, {240, 0}};
    lv_line_set_points(horiz_divider, horiz_points, 2);
    lv_obj_set_style_line_color(horiz_divider, lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_line_width(horiz_divider, 2, 0);
    lv_obj_set_pos(horiz_divider, 0, 185);

    // Mid divider between AVG and MAX rows at y=108
    lv_obj_t *mid_divider = lv_line_create(stats_screen);
    static lv_point_precise_t mid_points[] = {{0, 0}, {240, 0}};
    lv_line_set_points(mid_divider, mid_points, 2);
    lv_obj_set_style_line_color(mid_divider, lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_line_width(mid_divider, 1, 0);
    lv_obj_set_pos(mid_divider, 0, 108);

    // Vertical divider ONLY bottom half (y=185 to y=290)
    lv_obj_t *vert_divider = lv_line_create(stats_screen);
    static lv_point_precise_t vert_points[] = {{0, 0}, {0, 105}};
    lv_line_set_points(vert_divider, vert_points, 2);
    lv_obj_set_style_line_color(vert_divider, lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_line_width(vert_divider, 2, 0);
    lv_obj_set_pos(vert_divider, 120, 185);

    lv_obj_t *speed_title = lv_label_create(stats_screen);
    lv_label_set_text(speed_title, "SPEED");
    lv_obj_set_style_text_font(speed_title, &Exo_12_Regular, 0);
    lv_obj_set_style_text_color(speed_title, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_pos(speed_title, 10, 36);

    lv_obj_t *speed_unit = lv_label_create(stats_screen);
    lv_label_set_text(speed_unit, "mi/h");
    lv_obj_set_style_text_font(speed_unit, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(speed_unit, lv_color_hex(0x00BCD4), 0);
    lv_obj_align(speed_unit, LV_ALIGN_TOP_RIGHT, -10, 32);

    lv_obj_t *avg_label = lv_label_create(stats_screen);
    lv_label_set_text(avg_label, "AVG");
    lv_obj_set_style_text_font(avg_label, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(avg_label, lv_color_hex(0x888888), 0);
    lv_obj_set_pos(avg_label, 8, 82);

    avg_speed_label = lv_label_create(stats_screen);
    lv_label_set_text(avg_speed_label, "13.6");
    lv_obj_set_style_text_font(avg_speed_label, &Orbitron_48_Regular, 0);
    lv_obj_set_style_text_color(avg_speed_label, lv_color_black(), 0);
    lv_obj_set_pos(avg_speed_label, 60, 48);

    lv_obj_t *max_label = lv_label_create(stats_screen);
    lv_label_set_text(max_label, "MAX");
    lv_obj_set_style_text_font(max_label, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(max_label, lv_color_hex(0x888888), 0);
    lv_obj_set_pos(max_label, 8, 159);

    max_speed_label = lv_label_create(stats_screen);
    lv_label_set_text(max_speed_label, "26.6");
    lv_obj_set_style_text_font(max_speed_label, &Orbitron_48_Regular, 0);
    lv_obj_set_style_text_color(max_speed_label, lv_color_black(), 0);
    lv_obj_set_pos(max_speed_label, 60, 118);

    lv_obj_t *elev_title = lv_label_create(stats_screen);
    lv_label_set_text(elev_title, "ELEVATION");
    lv_obj_set_style_text_font(elev_title, &Exo_12_Regular, 0);
    lv_obj_set_style_text_color(elev_title, lv_color_hex(0x888888), 0);
    lv_obj_set_style_text_align(elev_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(elev_title, 120);
    lv_obj_set_pos(elev_title, 0, 193);

    elevation_label_stats = lv_label_create(stats_screen);
    lv_label_set_text(elevation_label_stats, "255");
    lv_obj_set_style_text_font(elevation_label_stats, &Exo_24_Regular, 0);
    lv_obj_set_style_text_color(elevation_label_stats, lv_color_black(), 0);
    lv_obj_set_style_text_align(elevation_label_stats, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(elevation_label_stats, 120);
    lv_obj_set_pos(elevation_label_stats, 0, 213);

    lv_obj_t *elev_unit = lv_label_create(stats_screen);
    lv_label_set_text(elev_unit, "ft");
    lv_obj_set_style_text_font(elev_unit, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(elev_unit, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_style_text_align(elev_unit, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(elev_unit, 120);
    lv_obj_set_pos(elev_unit, 0, 255);

    // BOTTOM RIGHT: Calories (x=120 to x=240, y=185 to y=290)

    lv_obj_t *cal_title = lv_label_create(stats_screen);
    lv_label_set_text(cal_title, "CALORIES");
    lv_obj_set_style_text_font(cal_title, &Exo_12_Regular, 0);
    lv_obj_set_style_text_color(cal_title, lv_color_hex(0x888888), 0);
    lv_obj_set_style_text_align(cal_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(cal_title, 120);
    lv_obj_set_pos(cal_title, 120, 193);

    calories_label = lv_label_create(stats_screen);
    lv_label_set_text(calories_label, "7129");
    lv_obj_set_style_text_font(calories_label, &Exo_24_Regular, 0);
    lv_obj_set_style_text_color(calories_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(calories_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(calories_label, 120);
    lv_obj_set_pos(calories_label, 120, 213);

    lv_obj_t *cal_unit = lv_label_create(stats_screen);
    lv_label_set_text(cal_unit, "kcal");
    lv_obj_set_style_text_font(cal_unit, &Exo_18_Regular, 0);
    lv_obj_set_style_text_color(cal_unit, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_style_text_align(cal_unit, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(cal_unit, 120);
    lv_obj_set_pos(cal_unit, 120, 255);
}

void gps_to_pixel(float lat, float lon, int *px, int *py) {
    if (trail_count < 2) {
        *px = 120;
        *py = 160;
        return;
    }

    float min_lat = trail[0].lat;
    float max_lat = trail[0].lat;
    float min_lon = trail[0].lon;
    float max_lon = trail[0].lon;

    for (int i = 1; i < trail_count; i++) {
        if (trail[i].lat < min_lat) min_lat = trail[i].lat;
        if (trail[i].lat > max_lat) max_lat = trail[i].lat;
        if (trail[i].lon < min_lon) min_lon = trail[i].lon;
        if (trail[i].lon > max_lon) max_lon = trail[i].lon;
    }

    float padding = 0.0002f;
    min_lat -= padding;
    max_lat += padding;
    min_lon -= padding;
    max_lon += padding;

    float lat_range = max_lat - min_lat;
    float lon_range = max_lon - min_lon;

    int map_x_min = 10;
    int map_x_max = 230;
    int map_y_min = 42;
    int map_y_max = 280;

    int map_width = map_x_max - map_x_min;
    int map_height = map_y_max - map_y_min;

    if (lon_range < 0.0001f) {
        *px = 120;
    } else {
        *px = map_x_min + (int)((lon - min_lon) / lon_range * map_width);
    }

    if (lat_range < 0.0001f) {
        *py = 160;
    } else {
        *py = map_y_min + (int)((max_lat - lat) / lat_range * map_height);
    }
}




void build_map_screen() {
    map_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(map_screen, lv_color_hex(0xF8FAFC), 0);
    lv_obj_set_style_bg_opa(map_screen, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(map_screen, 0, 0);
    lv_obj_set_style_border_width(map_screen, 0, 0);
    lv_obj_set_style_radius(map_screen, 0, 0);

    position_dot = lv_obj_create(map_screen);
    lv_obj_set_size(position_dot, 10, 10);
    lv_obj_set_style_radius(position_dot, 5, 0);
    lv_obj_set_style_bg_color(position_dot, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_style_bg_opa(position_dot, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(position_dot, 0, 0);
    lv_obj_set_pos(position_dot, 115, 155);
}

void update_map() {
    if (trail_count < 2) return;

    // Delete all children of map_screen except position_dot
    // then redraw all trail lines fresh
    lv_obj_t *child = lv_obj_get_child(map_screen, 0);
    while (child != NULL) {
        lv_obj_t *next = lv_obj_get_child(map_screen, 0);
        if (child != position_dot) {
            lv_obj_del(child);
        }
        child = next;
        if (child == position_dot) {
            child = lv_obj_get_child(map_screen, 1);
        }
    }

    // Draw all trail segments fresh
    static lv_point_precise_t point_pool[MAX_TRAIL_POINTS][2];

    for (int i = 0; i < trail_count - 1; i++) {
        int x1, y1, x2, y2;
        gps_to_pixel(trail[i].lat, trail[i].lon, &x1, &y1);
        gps_to_pixel(trail[i+1].lat, trail[i+1].lon, &x2, &y2);

        point_pool[i][0].x = x1;
        point_pool[i][0].y = y1;
        point_pool[i][1].x = x2;
        point_pool[i][1].y = y2;

        lv_obj_t *segment = lv_line_create(map_screen);
        lv_line_set_points(segment, point_pool[i], 2);
        lv_obj_set_style_line_color(segment, lv_color_black(), 0);
        lv_obj_set_style_line_width(segment, 2, 0);
    }

    // Move dot to current position, keep it on top
    int dot_x, dot_y;
    gps_to_pixel(trail[trail_count-1].lat, trail[trail_count-1].lon, &dot_x, &dot_y);
    lv_obj_set_pos(position_dot, dot_x - 5, dot_y - 5);
    lv_obj_move_foreground(position_dot);
}









void build_settings_screen() {

}






static int current_screen = 0; //0 = home, 1 = stats

void switch_screen() {
    if (current_screen == 0) {
        lv_scr_load(stats_screen);
        current_screen = 1;
    } else if (current_screen == 1) {
        lv_scr_load(home_screen);
        current_screen = 2;
    } else if (current_screen == 2) {
        lv_scr_load(map_screen);
        current_screen = 0;
    }
    
}

void add_screen_dots(lv_obj_t *screen, int active_index) {

    lv_obj_t *dot1 = lv_obj_create(screen);
    lv_obj_set_size(dot1, 8, 8);
    lv_obj_set_style_radius(dot1, 4, 0);
    lv_obj_set_style_border_color(dot1, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_style_border_width(dot1, 2, 0);
    lv_obj_align(dot1, LV_ALIGN_BOTTOM_MID, -18, -8);
    lv_obj_set_style_bg_color(dot1, active_index == 0 ? lv_color_hex(0x00BCD4) : lv_color_hex(0xF8FAFC), 0);
    lv_obj_set_style_bg_opa(dot1, LV_OPA_COVER, 0);

    lv_obj_t *dot2 = lv_obj_create(screen);
    lv_obj_set_size(dot2, 8, 8);
    lv_obj_set_style_radius(dot2, 4, 0);
    lv_obj_set_style_border_color(dot2, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_style_border_width(dot2, 2, 0);
    lv_obj_align(dot2, LV_ALIGN_BOTTOM_MID, 0, -8);
    lv_obj_set_style_bg_color(dot2, active_index == 1 ? lv_color_hex(0x00BCD4) : lv_color_hex(0xF8FAFC), 0);
    lv_obj_set_style_bg_opa(dot2, LV_OPA_COVER, 0);

    lv_obj_t *dot3 = lv_obj_create(screen);
    lv_obj_set_size(dot3, 8, 8);
    lv_obj_set_style_radius(dot3, 4, 0);
    lv_obj_set_style_border_color(dot3, lv_color_hex(0x00BCD4), 0);
    lv_obj_set_style_border_width(dot3, 2, 0);
    lv_obj_align(dot3, LV_ALIGN_BOTTOM_MID, 18, -8);
    lv_obj_set_style_bg_color(dot3, active_index == 2 ? lv_color_hex(0x00BCD4) : lv_color_hex(0xF8FAFC), 0);
    lv_obj_set_style_bg_opa(dot3, LV_OPA_COVER, 0);
}


// Function to update the UI with new values

void update_ui() {
    //Speed
    if (speed_label != NULL) {
    char speed_text[16];
    lv_snprintf(speed_text, sizeof(speed_text), "%.1f", fake_speed);
    lv_label_set_text(speed_label, speed_text);
}
    // Distance
    if (distance_label != NULL) {
    char distance_text[16];
    lv_snprintf(distance_text, sizeof(distance_text), "%.1f mi", fake_distance);
    lv_label_set_text(distance_label, distance_text);
}
    // Battery
    if (battery_label != NULL) {
    char battery_text[16];
    lv_snprintf(battery_text, sizeof(battery_text), "%d%%", fake_battery);
    lv_label_set_text(battery_label, battery_text);
}
    // average speed
    if (avg_speed_label != NULL) {    
    char avg_speed_text[16];
    lv_snprintf(avg_speed_text, sizeof(avg_speed_text), "%.1f", fake_avg_speed);
    lv_label_set_text(avg_speed_label, avg_speed_text);
    }
    // max speed
    if (max_speed_label != NULL) {
    char max_speed_text[16];
    lv_snprintf(max_speed_text, sizeof(max_speed_text), "%.1f", fake_max_speed);
    lv_label_set_text(max_speed_label, max_speed_text);
    }
    // calories text
    if (calories_label != NULL) {
    char calories_text[16];
    lv_snprintf(calories_text, sizeof(calories_text), "%d", fake_calories);
    lv_label_set_text(calories_label, calories_text);
    }
    //elevation text
    if (elevation_label_stats != NULL) {
    char elevation_text[16];
    lv_snprintf(elevation_text, sizeof(elevation_text), "%d", fake_elevation);
    lv_label_set_text(elevation_label_stats, elevation_text);
    }
}