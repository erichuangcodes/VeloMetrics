/*  This is the VeloMetrics UI Screen.
    It is coded using C++ and the LVGL library for user interface development. 
    The UI is designed to display information related to the VeloMetrics bike computer.
    Includes ------
*/

#include <lvgl.h>
#include <ui.h>

//POINTERS FOR OBJECTS ON SCREEN 

//Screen objects
lv_obj_t *home_screen;
lv_obj_t *stats_screen;

//Screen Indicator dots
static lv_obj_t *home_dot;
static lv_obj_t *stats_dot;

//Labels for home screen 
static lv_obj_t *speed_label;
static lv_obj_t *unit_label;
static lv_obj_t *time_label;
static lv_obj_t *distance_label;

//Labels for stats screen 
static lv_obj_t *avg_speed_label;
static lv_obj_t *max_speed_label;
static lv_obj_t *calories_label;
static lv_obj_t *elevation_label_stats;

//UI objects that stay on every screen 
//Always on the top
static lv_obj_t *battery_label;
static lv_obj_t *battery_label_2;
static lv_obj_t *bluetooth_label;
static lv_obj_t *temp_label;
static lv_obj_t *temp_label_2;
static lv_obj_t *localtime_label;
static lv_obj_t *localtime_label_2;

//fake testing values will change to real values later
static float fake_speed = 6.7;
static float fake_distance = 16.7;
static int fake_battery = 68;
static int fake_temp = 35;
static float fake_avg_speed = 14.2f;
static float fake_max_speed = 22.8f;
static int fake_elevation = 320;
static int fake_calories = 187;


//Home screen function

void build_home_screen() {

    // Get the active screen
    home_screen = lv_obj_create(NULL);   // Create a new screen (not the default one)
    lv_obj_t *screen = home_screen;

    // Set background color to white
    lv_obj_set_style_bg_color(screen, lv_color_white(), 0); 

    //Header Labels

    localtime_label = lv_label_create(screen);
    lv_label_set_text(localtime_label, "12:34");
    lv_obj_set_style_text_font(localtime_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(localtime_label, lv_color_black(), 0);
    lv_obj_align(localtime_label, LV_ALIGN_TOP_LEFT, 10, 8);

    temp_label = lv_label_create(screen);
    lv_label_set_text(temp_label, "35°C");
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(temp_label, lv_color_black(), 0);
    lv_obj_align(temp_label, LV_ALIGN_TOP_MID, 0, 8);

    battery_label = lv_label_create(screen);
    lv_label_set_text(battery_label, "68%");
    lv_obj_set_style_text_font(battery_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(battery_label, lv_color_black(), 0);
    lv_obj_align(battery_label, LV_ALIGN_TOP_RIGHT, -10, 8);

    // Divider line to seperate header from main content
    lv_obj_t *header_line_1 = lv_line_create(screen);
    static lv_point_precise_t line_points_1[] = {{0, 0}, {240, 0}};
    lv_line_set_points(header_line_1, line_points_1, 2);
    lv_obj_set_style_line_color(header_line_1, lv_color_black(), 0);
    lv_obj_set_style_line_width(header_line_1, 2, 0);
    lv_obj_set_pos(header_line_1, 0, 32);

    // Vertical divider splitting speed (left) from distance/time (right)
    lv_obj_t *vertical_line = lv_line_create(screen);
    static lv_point_precise_t vertical_points[] = {{0, 0}, {0, 258}};
    lv_line_set_points(vertical_line, vertical_points, 2);
    lv_obj_set_style_line_color(vertical_line, lv_color_black(), 0);
    lv_obj_set_style_line_width(vertical_line, 2, 0);
    lv_obj_set_pos(vertical_line, 120, 32);

    // Horizontal divider splitting distance (top) from time (bottom)
    lv_obj_t *right_split_line = lv_line_create(screen);
    static lv_point_precise_t right_split_points[] = {{0, 0}, {120, 0}};
    lv_line_set_points(right_split_line, right_split_points, 2);
    lv_obj_set_style_line_color(right_split_line, lv_color_black(), 0);
    lv_obj_set_style_line_width(right_split_line, 2, 0);
    lv_obj_set_pos(right_split_line, 120, 161);

    // ---- SPEED (big number, left box, full height, vertically centered) ----
    speed_label = lv_label_create(screen);
    lv_label_set_text(speed_label, "6.7");
    lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(speed_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(speed_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(speed_label, 120);
    lv_obj_set_pos(speed_label, 0, 140);

    // ---- Units label (mi/h, below speed) ----
    unit_label = lv_label_create(screen);
    lv_label_set_text(unit_label, "mi/h");
    lv_obj_set_style_text_font(unit_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(unit_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(unit_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(unit_label, 120);
    lv_obj_set_pos(unit_label, 0, 180);

    // ---- Distance section (top right box) ----
    lv_obj_t *distance_title = lv_label_create(screen);
    lv_label_set_text(distance_title, "Distance");
    lv_obj_set_style_text_font(distance_title, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(distance_title, lv_color_black(), 0);
    lv_obj_set_style_text_align(distance_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(distance_title, 120);
    lv_obj_set_pos(distance_title, 120, 52);

    distance_label = lv_label_create(screen);
    lv_label_set_text(distance_label, "16.7 mi");
    lv_obj_set_style_text_font(distance_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(distance_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(distance_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(distance_label, 120);
    lv_obj_set_pos(distance_label, 120, 90);

    // ---- Time section (bottom right box) ----
    lv_obj_t *time_title = lv_label_create(screen);
    lv_label_set_text(time_title, "Time");
    lv_obj_set_style_text_font(time_title, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(time_title, lv_color_black(), 0);
    lv_obj_set_style_text_align(time_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(time_title, 120);
    lv_obj_set_pos(time_title, 120, 181);

    time_label = lv_label_create(screen);
    lv_label_set_text(time_label, "1:07:59");
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(time_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(time_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(time_label, 120);
    lv_obj_set_pos(time_label, 120, 219);
}


//Stats screen function

void build_stats_screen () {

    stats_screen = lv_obj_create(NULL);   // Create a new screen (not the default one)
    lv_obj_t *screen = stats_screen;

    lv_obj_set_style_bg_color(stats_screen, lv_color_white(), 0);

    // ================================================================
    // HEADER (y = 8 to y = 24)
    // ================================================================

    localtime_label_2 = lv_label_create(stats_screen);
    lv_label_set_text(localtime_label_2, "12:34");
    lv_obj_set_style_text_font(localtime_label_2, &lv_font_montserrat_14, 0); 
    lv_obj_set_style_text_color(localtime_label_2, lv_color_black(), 0);
    lv_obj_align(localtime_label_2, LV_ALIGN_TOP_LEFT, 10, 8);

    temp_label_2 = lv_label_create(stats_screen);
    lv_label_set_text(temp_label_2, "35°C");
    lv_obj_set_style_text_font(temp_label_2, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(temp_label_2, lv_color_black(), 0);
    lv_obj_align(temp_label_2, LV_ALIGN_TOP_MID, 0, 8);   // centered, not -50 offset

    battery_label_2 = lv_label_create(stats_screen);
    lv_label_set_text(battery_label_2, "68%");
    lv_obj_set_style_text_font(battery_label_2, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(battery_label_2, lv_color_black(), 0);
    lv_obj_align(battery_label_2, LV_ALIGN_TOP_RIGHT, -10, 8);

    // ================================================================
    // DIVIDERS
    // Header line at y=32. Grid area is y=32 to y=290 (258px tall).
    // Middle line at y=161 (32 + 129 = halfway). Vertical line at x=120 (halfway).
    // ================================================================

    lv_obj_t *header_line_2 = lv_line_create(stats_screen);
    static lv_point_precise_t header_points_2[] = {{0, 0}, {240, 0}};
    lv_line_set_points(header_line_2, header_points_2, 2);
    lv_obj_set_style_line_color(header_line_2, lv_color_black(), 0);
    lv_obj_set_style_line_width(header_line_2, 2, 0);
    lv_obj_set_pos(header_line_2, 0, 32);

    lv_obj_t *middle_line = lv_line_create(stats_screen);
    static lv_point_precise_t middle_points[] = {{0, 0}, {240, 0}};
    lv_line_set_points(middle_line, middle_points, 2);
    lv_obj_set_style_line_color(middle_line, lv_color_black(), 0);
    lv_obj_set_style_line_width(middle_line, 2, 0);
    lv_obj_set_pos(middle_line, 0, 161);

    lv_obj_t *vertical_line_2 = lv_line_create(stats_screen);
    static lv_point_precise_t vertical_points_2[] = {{0, 0}, {0, 258}};
    lv_line_set_points(vertical_line_2, vertical_points_2, 2);
    lv_obj_set_style_line_color(vertical_line_2, lv_color_black(), 0);
    lv_obj_set_style_line_width(vertical_line_2, 2, 0);
    lv_obj_set_pos(vertical_line_2, 120, 32);

    // TOP LEFT BOX
    lv_obj_t *avg_title = lv_label_create(stats_screen);
    lv_label_set_text(avg_title, "Avg Speed");
    lv_obj_set_style_text_font(avg_title, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(avg_title, lv_color_black(), 0);
    lv_obj_set_style_text_align(avg_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(avg_title, 120);
    lv_obj_set_pos(avg_title, 0, 52);

    avg_speed_label = lv_label_create(stats_screen);
    lv_label_set_text(avg_speed_label, "14.2");
    lv_obj_set_style_text_font(avg_speed_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(avg_speed_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(avg_speed_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(avg_speed_label, 120);
    lv_obj_set_pos(avg_speed_label, 0, 77);

    lv_obj_t *avg_unit = lv_label_create(stats_screen);
    lv_label_set_text(avg_unit, "mi/h");
    lv_obj_set_style_text_font(avg_unit, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(avg_unit, lv_color_black(), 0);
    lv_obj_set_style_text_align(avg_unit, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(avg_unit, 120);
    lv_obj_set_pos(avg_unit, 0, 112);

    // TOP RIGHT BOX
    lv_obj_t *max_title = lv_label_create(stats_screen);
    lv_label_set_text(max_title, "Max Speed");
    lv_obj_set_style_text_font(max_title, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(max_title, lv_color_black(), 0);
    lv_obj_set_style_text_align(max_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(max_title, 120);
    lv_obj_set_pos(max_title, 120, 52);

    max_speed_label = lv_label_create(stats_screen);
    lv_label_set_text(max_speed_label, "22.8");
    lv_obj_set_style_text_font(max_speed_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(max_speed_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(max_speed_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(max_speed_label, 120);
    lv_obj_set_pos(max_speed_label, 120, 77);

    lv_obj_t *max_unit = lv_label_create(stats_screen);
    lv_label_set_text(max_unit, "mi/h");
    lv_obj_set_style_text_font(max_unit, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(max_unit, lv_color_black(), 0);
    lv_obj_set_style_text_align(max_unit, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(max_unit, 120);
    lv_obj_set_pos(max_unit, 120, 112);

    // BOTTOM LEFT BOX
    lv_obj_t *elevation_title = lv_label_create(stats_screen);
    lv_label_set_text(elevation_title, "Elevation");
    lv_obj_set_style_text_font(elevation_title, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(elevation_title, lv_color_black(), 0);
    lv_obj_set_style_text_align(elevation_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(elevation_title, 120);
    lv_obj_set_pos(elevation_title, 0, 181);

    elevation_label_stats = lv_label_create(stats_screen);
    lv_label_set_text(elevation_label_stats, "342");
    lv_obj_set_style_text_font(elevation_label_stats, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(elevation_label_stats, lv_color_black(), 0);
    lv_obj_set_style_text_align(elevation_label_stats, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(elevation_label_stats, 120);
    lv_obj_set_pos(elevation_label_stats, 0, 206);
    
    lv_obj_t *elevation_unit = lv_label_create(stats_screen);
    lv_label_set_text(elevation_unit, "ft");
    lv_obj_set_style_text_font(elevation_unit, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(elevation_unit, lv_color_black(), 0);
    lv_obj_set_style_text_align(elevation_unit, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(elevation_unit, 120);
    lv_obj_set_pos(elevation_unit, 0, 241);

    // BOTTOM RIGHT BOX
    lv_obj_t *calories_title = lv_label_create(stats_screen);
    lv_label_set_text(calories_title, "Calories");
    lv_obj_set_style_text_font(calories_title, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(calories_title, lv_color_black(), 0);
    lv_obj_set_style_text_align(calories_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(calories_title, 120);
    lv_obj_set_pos(calories_title, 120, 181);

    calories_label = lv_label_create(stats_screen);
    lv_label_set_text(calories_label, "187");
    lv_obj_set_style_text_font(calories_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(calories_label, lv_color_black(), 0);
    lv_obj_set_style_text_align(calories_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(calories_label, 120);
    lv_obj_set_pos(calories_label, 120, 206);

    lv_obj_t *calories_unit = lv_label_create(stats_screen);
    lv_label_set_text(calories_unit, "kcal");
    lv_obj_set_style_text_font(calories_unit, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(calories_unit, lv_color_black(), 0);
    lv_obj_set_style_text_align(calories_unit, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(calories_unit, 120);
    lv_obj_set_pos(calories_unit, 120, 241);
}

static int current_screen = 0; //0 = home, 1 = stats

void switch_screen() {
    if (current_screen == 0) {
        lv_scr_load(stats_screen);
        current_screen = 1;
    } else {
        lv_scr_load(home_screen);
        current_screen = 0;
    }
}

void add_screen_dots(lv_obj_t *screen, int active_index) {

    lv_obj_t *dot_home = lv_obj_create(screen);
    lv_obj_set_size(dot_home, 10, 10);
    lv_obj_set_style_radius(dot_home, 5, 0);
    lv_obj_set_style_border_color(dot_home, lv_color_black(), 0);
    lv_obj_set_style_border_width(dot_home, 2, 0);
    lv_obj_align(dot_home, LV_ALIGN_BOTTOM_MID, -10, -5);

    if (active_index == 0) {
        lv_obj_set_style_bg_color(dot_home, lv_color_black(), 0);
    } else {
        lv_obj_set_style_bg_color(dot_home, lv_color_white(), 0);
    }

    lv_obj_t *dot_stats = lv_obj_create(screen);
    lv_obj_set_size(dot_stats, 10, 10);
    lv_obj_set_style_radius(dot_stats, 5, 0);
    lv_obj_set_style_border_color(dot_stats, lv_color_black(), 0);
    lv_obj_set_style_border_width(dot_stats, 2, 0);
    lv_obj_align(dot_stats, LV_ALIGN_BOTTOM_MID, 10, -5);

    if (active_index == 1) {
        lv_obj_set_style_bg_color(dot_stats, lv_color_black(), 0);
    } else {
        lv_obj_set_style_bg_color(dot_stats, lv_color_white(), 0);
    }

}




// Function to update the UI with new values

void update_ui() {
    //Speed
    char speed_text[16];
    lv_snprintf(speed_text, sizeof(speed_text), "%.1f", fake_speed);
    lv_label_set_text(speed_label, speed_text);

    // Distance
    char distance_text[16];
    lv_snprintf(distance_text, sizeof(distance_text), "%.1f mi", fake_distance);
    lv_label_set_text(distance_label, distance_text);

    // Battery
    char battery_text[16];
    lv_snprintf(battery_text, sizeof(battery_text), "%d%%", fake_battery);
    lv_label_set_text(battery_label, battery_text);

    // average speed
    char avg_speed_text[16];
    lv_snprintf(avg_speed_text, sizeof(avg_speed_text), "%.1f", fake_avg_speed);
    lv_label_set_text(avg_speed_label, avg_speed_text);

    // max speed
    char max_speed_text[16];
    lv_snprintf(max_speed_text, sizeof(max_speed_text), "%.1f", fake_max_speed);
    lv_label_set_text(max_speed_label, max_speed_text);

    // calories text
    char calories_text[16];
    lv_snprintf(calories_text, sizeof(calories_text), "%d", fake_calories);
    lv_label_set_text(calories_label, calories_text);

    //elevation text
    char elevation_text[16];
    lv_snprintf(elevation_text, sizeof(elevation_text), "%d", fake_elevation);
    lv_label_set_text(elevation_label_stats, elevation_text);
}