#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"

void setup_scr_image(lv_ui* ui){
    
    lv_obj_set_style_local_bg_color(ui->image, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    lv_obj_t * img_image = lv_img_create(ui->image, NULL);
    lv_img_set_src(img_image, "S:/image/neko.bin");
    lv_obj_align(img_image, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
}