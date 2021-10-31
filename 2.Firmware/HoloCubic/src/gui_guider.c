#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"


void setup_ui(lv_ui* ui)
{
	setup_scr(ui);
	setup_task_spaceman();
}
