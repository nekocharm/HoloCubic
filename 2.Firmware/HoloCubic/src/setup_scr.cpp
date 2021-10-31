#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include <Arduino.h>

extern lv_indev_t* indev_encoder;

lv_obj_t* tabview;

void setup_scr(lv_ui* ui){

    tabview = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_style_local_bg_color(tabview, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_size(tabview, LV_HOR_RES_MAX, LV_VER_RES_MAX);//设置大小
    lv_obj_align(tabview, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);//对齐
    lv_tabview_set_btns_pos(tabview, LV_TABVIEW_TAB_POS_NONE);//不显示btns

    ui->spaceman = lv_tabview_add_tab(tabview, "Tab 1");
    ui->image = lv_tabview_add_tab(tabview, "Tab 2");
    ui->weather = lv_tabview_add_tab(tabview, "Tab 3");
    ui->text = lv_tabview_add_tab(tabview, "Tab 4");

    setup_scr_spaceman(ui);//第一页
    //LV_LOG_ERROR("spaceman done");
    setup_scr_image(ui);//第二页
    //LV_LOG_ERROR("image done");
    setup_scr_weather(ui); // 第三页
    //LV_LOG_ERROR("weather done");
    setup_scr_text(ui); // 第四页
    //LV_LOG_ERROR("text done");
    
}