#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "time.h"
#include <ESP32Time.h>

bool getLocalTime(struct tm * info, uint32_t ms);

// 全局变量声明
static lv_task_t * task_spaceman;
lv_obj_t* img_spaceman;
lv_obj_t* label_clock1;
lv_obj_t* label_clock2;
lv_obj_t* img_weather_1;
lv_obj_t* label_weather;
lv_obj_t* label_temperature;
lv_obj_t* label_day;
lv_obj_t* label_week;
lv_obj_t* label_city;


//全局使用的缓存
static char buf[100];

// 实时时钟变量
extern ESP32Time rtc;
static int day=0;
extern boolean wifi_status;

// 天气变量
extern String location;
extern String temperature;
extern String weather;
extern uint8_t weather_code;


// 获取星期函数
String week(uint8_t num){
    switch (num)
    {
    case 0:
        return "星期日";
    case 1:
        return "星期一";
    case 2:
        return "星期二";
    case 3:
        return "星期三";
    case 4:
        return "星期四";
    case 5:
        return "星期五";
    case 6:
        return "星期六";

    default:
        break;
    }
    return "";
}


void setup_scr_spaceman(lv_ui* ui){

    lv_obj_set_style_local_bg_color(ui->spaceman, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
   
    // 字体格式 maiyuan_24
    static lv_style_t style_font_maiyuan_24;
    lv_style_init(&style_font_maiyuan_24);
    lv_style_set_text_font(&style_font_maiyuan_24, LV_STATE_DEFAULT, &lv_font_maiyuan_24);
    lv_style_set_text_color(&style_font_maiyuan_24, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_letter_space(&style_font_maiyuan_24,LV_STATE_DEFAULT,2);
    // 字体格式 digital_72
    static lv_style_t style_font_digital_72;
    lv_style_init(&style_font_digital_72);
    lv_style_set_text_font(&style_font_digital_72, LV_STATE_DEFAULT, &lv_font_digital_72);
    lv_style_set_text_color(&style_font_digital_72, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_letter_space(&style_font_digital_72,LV_STATE_DEFAULT,2);
    // 字体格式 digital_48
    static lv_style_t style_font_digital_48;
    lv_style_init(&style_font_digital_48);
    lv_style_set_text_font(&style_font_digital_48, LV_STATE_DEFAULT, &lv_font_digital_48);
    lv_style_set_text_color(&style_font_digital_48, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_letter_space(&style_font_digital_48,LV_STATE_DEFAULT,2);
    

    // 城市名称
    label_city = lv_label_create(ui->spaceman, NULL);
    lv_obj_add_style(label_city, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    //lv_obj_set_style_local_text_font(label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_maiyuan_24);
    lv_label_set_long_mode(label_city, LV_LABEL_LONG_DOT);     
    //lv_label_set_recolor(label1, true);   //重新设置颜色                   
    lv_label_set_align(label_city, LV_LABEL_ALIGN_LEFT);      
    lv_label_set_text(label_city, location.c_str());
    lv_obj_set_width(label_city, 90);
    lv_obj_align(label_city, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 10);
    
    // 天气
    label_weather = lv_label_create(ui->spaceman, NULL);
    lv_obj_add_style(label_weather, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    lv_label_set_long_mode(label_weather, LV_LABEL_LONG_SROLL_CIRC);                    
    lv_label_set_align(label_weather, LV_LABEL_ALIGN_RIGHT);      
    lv_label_set_text(label_weather, "");
    lv_obj_set_width(label_weather, 129);
    lv_obj_align(label_weather, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 45);

    // 温度
    label_temperature = lv_label_create(ui->spaceman, NULL);
    lv_obj_add_style(label_temperature, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    lv_label_set_long_mode(label_temperature, LV_LABEL_LONG_CROP);                
    lv_label_set_align(label_temperature, LV_LABEL_ALIGN_RIGHT);      
    lv_label_set_text(label_temperature, "度");
    lv_obj_set_width(label_temperature, 65);
    lv_obj_align(label_temperature, NULL, LV_ALIGN_IN_TOP_LEFT, 85, 10);

    // 时间
    label_clock1 = lv_label_create(ui->spaceman, NULL);
    lv_obj_add_style(label_clock1, LV_LABEL_PART_MAIN, &style_font_digital_72);
    lv_label_set_long_mode(label_clock1, LV_LABEL_LONG_CROP);                
    lv_label_set_align(label_clock1, LV_LABEL_ALIGN_RIGHT);      
    lv_label_set_text_fmt(label_clock1, "%02d:%02d",0,0);
    lv_obj_set_width(label_clock1, 160);
    lv_obj_align(label_clock1, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 65);

    label_clock2 = lv_label_create(ui->spaceman, NULL);
    lv_obj_add_style(label_clock2, LV_LABEL_PART_MAIN, &style_font_digital_48);
    lv_label_set_long_mode(label_clock2, LV_LABEL_LONG_CROP);                
    lv_label_set_align(label_clock2, LV_LABEL_ALIGN_LEFT);      
    lv_label_set_text_fmt(label_clock2, "%02d",0);
    lv_label_set_text(label_clock2, "00");
    lv_obj_set_width(label_clock2, 80);
    lv_obj_align(label_clock2, NULL, LV_ALIGN_IN_TOP_LEFT, 175, 88);


    // 日期
    label_day = lv_label_create(ui->spaceman, NULL);
    lv_obj_add_style(label_day, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    lv_label_set_long_mode(label_day, LV_LABEL_LONG_CROP);                
    lv_label_set_align(label_day, LV_LABEL_ALIGN_CENTER);      
    lv_label_set_text_fmt(label_day, "%02d月%02d日",rtc.getMonth(),rtc.getDay());
    lv_obj_set_width(label_day, 100);
    lv_obj_align(label_day, NULL, LV_ALIGN_IN_TOP_LEFT, 110, 160);

    label_week = lv_label_create(ui->spaceman, NULL);
    lv_obj_add_style(label_week, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    lv_label_set_long_mode(label_week, LV_LABEL_LONG_CROP);                
    lv_label_set_align(label_week, LV_LABEL_ALIGN_CENTER);      
    lv_label_set_text(label_week, week(rtc.getDayofWeek()).c_str());
    lv_obj_set_width(label_week, 100);
    lv_obj_align(label_week, NULL, LV_ALIGN_IN_TOP_LEFT, 110, 200);

    // 天气图片

    img_weather_1 = lv_img_create(ui->spaceman, NULL);
    lv_img_set_src(img_weather_1, "S:/weather_icon/99.bin");
    lv_obj_set_style_local_image_recolor_opa(img_weather_1, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_image_recolor(img_weather_1, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_align(img_weather_1, NULL, LV_ALIGN_CENTER, 65, -90);


    // 太空人
    img_spaceman = lv_img_create(ui->spaceman, NULL);
    lv_img_set_src(img_spaceman, "S:/spaceman/1.bin");
    lv_obj_set_style_local_image_recolor_opa(img_spaceman, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_image_recolor(img_spaceman, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_align(img_spaceman, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 152);
    
}

static int spaceman_id=1;

void loop_spaceman(){
    int len = sprintf(buf, "S:/spaceman/%d.bin", spaceman_id++);
    buf[len] = 0;
    lv_img_set_src(img_spaceman, buf);
    if(spaceman_id==14){
        spaceman_id=1;
    }
}

void user_spaceman_task(lv_task_t * task){
    /*Use the user_data*/
    loop_spaceman();
    if(wifi_status){
        lv_label_set_text_fmt(label_clock1, "%02d:%02d",rtc.getHour(true),rtc.getMinute());
        lv_label_set_text_fmt(label_clock2, "%02d",rtc.getSecond());
        if(rtc.getDay()!=day){
            lv_label_set_text_fmt(label_day, "%02d月%02d日",rtc.getMonth()+1,rtc.getDay());
            lv_label_set_text(label_week, week(rtc.getDayofWeek()).c_str());
        }
    }
    
    
}

void setup_task_spaceman(void){
    task_spaceman = lv_task_create(user_spaceman_task, 100, LV_TASK_PRIO_MID, NULL);
    lv_task_ready(task_spaceman);
}






