#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include <Arduino.h>

extern String text;

lv_obj_t* label_text;


void setup_scr_text(lv_ui* ui){
    lv_obj_set_style_local_bg_color(ui->text, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // 字体格式 maiyuan_24
    static lv_style_t style_font_maiyuan_24;
    lv_style_init(&style_font_maiyuan_24);
    lv_style_set_text_font(&style_font_maiyuan_24, LV_STATE_DEFAULT, &lv_font_maiyuan_24);
    lv_style_set_text_color(&style_font_maiyuan_24, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_letter_space(&style_font_maiyuan_24,LV_STATE_DEFAULT,2);


    // 文字
    label_text = lv_label_create(ui->text, NULL);
    lv_obj_add_style(label_text, LV_LABEL_PART_MAIN, &style_font_maiyuan_24);
    lv_obj_set_auto_realign(label_text, true); 
    lv_label_set_long_mode(label_text, LV_LABEL_LONG_BREAK);     
    lv_label_set_recolor(label_text, true);   //重新设置颜色                   
    lv_label_set_align(label_text, LV_LABEL_ALIGN_CENTER);      
    lv_label_set_text(label_text, text.c_str());
    lv_obj_set_width(label_text, 240);
    //lv_obj_set_height(label_text, 240);
    lv_obj_align(label_text, NULL, LV_ALIGN_CENTER, 0, 0);

}