#include <Arduino.h>
#include "network.h"
#include <ArduinoJson.h>
#include "lvgl.h"

String location="";
String key;
String weather="";
String temperature="";
String weather_str="99";

uint8_t weather_code=0;

// 声明全局变量

extern lv_obj_t* img_weather_1;
extern lv_obj_t* label_weather;
extern lv_obj_t* label_temperature;


extern lv_obj_t* weather_label_weather;
extern lv_obj_t* weather_image_weather;
extern lv_obj_t* weather_label_temperature;


//全局使用的缓存
static char buf[100];



bool getWeather(){
	HTTPClient http;
	String payload="0";
	http.begin("https://api.seniverse.com/v3/weather/now.json?key="+key+"&location="+location+"&language=zh-Hans&unit=c");
	int httpCode = http.GET();
	if (httpCode > 0)
	{
		// file found at server
		if (httpCode == HTTP_CODE_OK)
		{
			payload = http.getString();
			// Stream& input;
			StaticJsonDocument<512> doc;

			DeserializationError error = deserializeJson(doc, payload);

			if (error) {
  				Serial.print(F("deserializeJson() failed: "));
  				Serial.println(error.f_str());
  				return false;
			}

			JsonObject results_0 = doc["results"][0];
			JsonObject results_0_now = results_0["now"];
			const char* results_0_now_text=results_0_now["text"]; 
			String new_weather =  results_0_now_text;
			if(new_weather!=weather){
				weather=new_weather;
				lv_label_set_text(label_weather, weather.c_str());
				//lv_label_set_text(weather_label_weather, weather.c_str());
			}
			const char* results_0_now_code=results_0_now["code"]; 
			String new_weather_str=results_0_now_code;
			if(new_weather_str!=weather_str){
				weather_str=new_weather_str;
				weather_code=weather_str.toInt();
				int len = sprintf(buf, "S:/weather_icon/%d.bin", weather_code);
        		buf[len] = 0;
        		lv_img_set_src(img_weather_1, buf);
				len = sprintf(buf, "S:/weather_icon_240/%d.bin", weather_code);
				buf[len] = 0;
				lv_img_set_src(weather_image_weather, buf);
			}
			const char* results_0_now_temperature = results_0_now["temperature"];
			String new_temperature = results_0_now_temperature;
			if(new_temperature!=temperature){
				temperature=new_temperature;
				lv_label_set_text(label_temperature, (temperature+"度").c_str());
				lv_label_set_text(weather_label_temperature, (temperature+"度").c_str());
			}
			return true;
		}
	}

	return false;
}

