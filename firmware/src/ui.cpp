/*  This is the VeloMetrics UI Screen.
    It is coded using C++ and the LVGL library for user interface development. 
    The UI is designed to display information related to the VeloMetrics bike computer.
    Includes ------
*/

#include "lvgl/lvgl.h"

//UI objects - pointers to things on screen | add more later as needed
static lv_obj_t *speed_label;
static lv_obj_t *unit_label;
static lv_obj_t *time_label;
static lv_obj_t *distance_label;
static lv_obj_t *elevation_label;

//UI objects that stay on every screen 
//Always on the top
static lv_obj_t *battery_label;
static lv_obj_t *bluetooth_label;
static lv_obj_t *temp_label;
static lv_obj_t *localtime_label;

//fake testing values will change to real values later
static float fake_speed = 6.7;
static float fake_distance = 16.7;
static int fake_battery = 68;
static int fake_temp = 35;

void build_home_screen() {

    // Get the active screen
    lv_obj_t *screen = lv_scr_act(); 

    // Set background color to black
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0); 

    //Header Labels

    localtime_label = lv_label_create(screen);
    lv_label_set_text(localtime_label, "12:34");
    lv_obj_set_style_text_font(localtime_label, &lv_font_montserrat_14, 0); //Set font to Bank Gothic Demi 28
    lv_obj_set_style_text_color(localtime_label, lv_color_white(), 0);
    lv_obj_align(localtime_label, LV_ALIGN_TOP_LEFT, 10, 8);

    temp_label = lv_label_create(screen);
    lv_label_set_text(temp_label, (fake_temp) + "°C");
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_14, 0); //Set font to Bank Gothic Demi 28
    lv_obj_set_style_text_color(temp_label, lv_color_white(), 0);
    lv_obj_align(temp_label, LV_ALIGN_TOP_RIGHT, 0, 8);

    battery_label = lv_label_create(screen);
    lv_label_set_text(battery_label, (fake_battery) + "%");
    lv_obj_set_style_text_font(battery_label, &lv_font_montserrat_14, 0); //Set font to Bank Gothic Demi 28
    lv_obj_set_style_text_color(battery_label, lv_color_white(), 0);
    lv_obj_align(battery_label, LV_ALIGN_TOP_RIGHT, -10, 8);

    // Divider line to seperate header from main content
    lv_obj_t *divider_line = lv_label_create(screen);
    static lv_point_t line_points[] = {{0, 0}, {240, 0}};
    lv_obj_set_style_line_color(divider_line, lv_color_white(), 0);
    lv_obj_set_style_line_width(divider_line, 1, 0);
    lv_obj_align(divider_line, LV_ALIGN_TOP_MID, 0, 28);


    //Speed Label
    speed_label = lv_label_create(screen);
    lv_label_set_text(speed_label, "6.7"); //6.7 is only a placeholder for now
    // Use default font to avoid undefined font identifier (lv_font_montserrat_44)
    lv_obj_set_style_text_font(speed_label, LV_FONT_DEFAULT, 0);
    lv_obj_set_style_text_color(speed_label, lv_color_white(), 0);
    lv_obj_align(speed_label, LV_ALIGN_CENTER, 0, 40);
   
}