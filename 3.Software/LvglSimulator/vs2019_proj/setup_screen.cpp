#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
extern "C" {
    LV_FONT_DECLARE(lv_font_digital_32)
    LV_FONT_DECLARE(lv_font_digital_48)
    LV_FONT_DECLARE(lv_font_simsun_12)
    LV_FONT_DECLARE(lv_font_maiyuan_24)
}


void setup_scr(){
    lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
}

void setup_scr_spaceman(lv_ui* ui){
    ui->spaceman = lv_obj_create(NULL, NULL);
    static lv_point_t line_points[] = {{0,60}, {240,60} };
    // 设置分割线
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 3);
    lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, false);

    /*Create a line and apply the new style*/
    lv_obj_t * line;
    line = lv_line_create(lv_scr_act(), NULL);
    lv_line_set_points(line, line_points, 2);     /*Set the points*/
    lv_obj_add_style(line, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_obj_align(line, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // 设置天气
    //lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &hei_20);
    static lv_style_t style_font;
    lv_style_init(&style_font);
    lv_style_set_text_font(&style_font, LV_STATE_DEFAULT, &lv_font_maiyuan_24);
    lv_obj_t* label1 = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &style_font);
    //lv_obj_set_style_local_text_font(label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);
    //lv_obj_set_style_local_text_font(label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_digital_48);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
    //lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
    //    "and  wrap long text automatically.");
    lv_label_set_text(label1, "#0000ff 张#");
    lv_obj_set_width(label1, 150);
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* label2 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
    lv_obj_set_width(label2, 150);
    lv_label_set_text(label2, "It is a circularly scrolling text. ");
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);


}