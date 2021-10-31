#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

	typedef struct
	{
		lv_obj_t* spaceman;
		lv_obj_t* image;
		lv_obj_t* weather;
		lv_obj_t* text;
	}lv_ui;

	void setup_ui(lv_ui* ui);
	
	void setup_scr_spaceman(lv_ui* ui);
	void setup_task_spaceman(void);
	void setup_scr_image(lv_ui* ui);
	void setup_scr_weather(lv_ui* ui);
	void setup_scr_text(lv_ui* ui);
	void setup_scr(lv_ui* ui);

	extern lv_ui guider_ui;
	extern struct tm timeinfo;
	extern lv_obj_t* tabview;

	// 太空人
	extern lv_obj_t* img_spaceman;
	extern lv_obj_t* label_clock1;
	extern lv_obj_t* label_clock2;
	extern lv_obj_t* img_weather_1;
	extern lv_obj_t* label_weather;
	extern lv_obj_t* label_temperature;
	extern lv_obj_t* label_day;
	extern lv_obj_t* label_week;
	extern lv_obj_t* label_city;
	extern lv_obj_t* weather_label_location;
	
	
#ifdef __cplusplus
}
#endif

#endif