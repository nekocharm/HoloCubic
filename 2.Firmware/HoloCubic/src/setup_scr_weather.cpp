#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include <Arduino.h>

// 天气变量
extern String location;
extern String temperature;
extern String weather;
extern uint8_t weather_code;

lv_obj_t* weather_label_weather;
lv_obj_t* weather_image_weather;
lv_obj_t* weather_label_temperature;
lv_obj_t* weather_label_location;

void setup_scr_weather(lv_ui* ui){

    lv_obj_set_style_local_bg_color(ui->weather, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // 字体格式 maiyuan_24
    static lv_style_t style_font_maiyuan_24;
    lv_style_init(&style_font_maiyuan_24);
    lv_style_set_text_font(&style_font_maiyuan_24, LV_STATE_DEFAULT, &lv_font_maiyuan_24);
    lv_style_set_text_color(&style_font_maiyuan_24, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_letter_space(&style_font_maiyuan_24,LV_STATE_DEFAULT,2);
    

    // 天气图片
    weather_image_weather = lv_img_create(ui->weather, NULL);
    lv_img_set_src(weather_image_weather, "S:/weather_icon/99.bin");
    lv_obj_set_style_local_image_recolor_opa(weather_image_weather, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_image_recolor(weather_image_weather, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_align(weather_image_weather, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // // 天气
    // weather_label_weather = lv_label_create(ui->weather, NULL);
    // lv_obj_add_style(weather_label_weather, LV_LABEL_PART_MAIN, &style_font_maiyuan_32);
    // lv_label_set_long_mode(weather_label_weather, LV_LABEL_LONG_SROLL_CIRC);                    
    // lv_label_set_align(weather_label_weather, LV_LABEL_ALIGN_RIGHT);      
    // lv_label_set_text(weather_label_weather, "");
    // lv_obj_set_width(weather_label_weather, 110);
    // lv_obj_align(weather_label_weather, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -15);

    // 温度
    weather_label_temperature = lv_label_create(ui->weather, NULL);
    lv_obj_add_style(weather_label_temperature, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    lv_label_set_long_mode(weather_label_temperature, LV_LABEL_LONG_SROLL_CIRC);                    
    lv_label_set_align(weather_label_temperature, LV_LABEL_ALIGN_LEFT);  
    lv_label_set_text(weather_label_temperature, "度");
    lv_obj_set_width(weather_label_temperature, 90);
    lv_obj_align(weather_label_temperature, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, -15);

    // 地点
    weather_label_location = lv_label_create(ui->weather, NULL);
    lv_obj_add_style(weather_label_location, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    lv_label_set_long_mode(weather_label_location, LV_LABEL_LONG_SROLL_CIRC);                    
    lv_label_set_align(weather_label_location, LV_LABEL_ALIGN_CENTER);      
    lv_label_set_text(weather_label_location, location.c_str());
    lv_obj_set_width(weather_label_location, 110);
    lv_obj_align(weather_label_location, NULL, LV_ALIGN_IN_BOTTOM_MID, -40, -15);

}