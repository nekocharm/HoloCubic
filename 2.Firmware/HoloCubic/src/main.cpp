#include <Arduino.h>
#include "display.h"
#include "imu.h"
#include "ambient.h"
#include "network.h"
#include "sd_card.h"
#include "lv_port_indev.h"
#include "lv_port_fatfs.h"
#include "gui_guider.h"
#include <TFT_eSPI.h>
#include "time.h"
#include <ESP32Time.h>

// 函数声明
bool getWeather();

/*** Component objects ***/
Display screen;  //屏幕显示
IMU mpu;  //MPU6050
SdCard tf;  // 内存卡
Network wifi;  //网络ambient
Ambient ambient; //环境光传感器
lv_ui guider_ui;  //GUI

// 更换页面
uint8_t button_state=0;
uint8_t page_num=0;
//static char buf[100];

//float duty=0;

/*** 全局变量 ***/
// 天气位置

extern String location;
extern String key;
String _location="";
// 时间
struct tm timeinfo;
ESP32Time rtc;

// 天气变量
extern String temperature;
extern String weather;
extern uint8_t weather_code;

// wifi连接
String ssid;
String password;
String _ssid;
String _password;


// 备忘录
String text="";
extern lv_obj_t* label_text;

boolean wifi_status=false;


// 对时任务，天气任务和调光任务

uint16_t time_num=0;
void user_task(lv_task_t * task){
    /*Use the user_data*/
    uint16_t* user_data=(uint16_t*)task->user_data;
    //duty=ambient.getLux()/30;
    //duty = constrain(duty, 0, 0.3);
    //screen.setBackLight(duty+0.4);  //设置背光
    (*user_data)++;
    if(*user_data==600){
        (*user_data)=0;
        if(wifi_status){
            configTime(28800, 0, "ntp3.aliyun.com");
            if(getLocalTime(&timeinfo)){
                rtc.setTimeStruct(timeinfo); 
            }
            getWeather();
        }
        
    }
}

void setup_task(void){
    lv_task_t * task_user = lv_task_create(user_task, 1000, LV_TASK_PRIO_MID, &time_num);
    lv_task_ready(task_user);
    
}



void setup()
{
    Serial.begin(115200);  //打开串口

    /*** Init screen ***/
    screen.init();   //初始化屏幕
    screen.setBackLight(0.5);  //设置背光
    ambient.init(ONE_TIME_H_RESOLUTION_MODE);  //初始化环境光传感器 采样时间125
   
    /*** Init IMU as input device ***/
    lv_port_indev_init();  //初始化输入设备
    mpu.init();  //初始化加速度计

    delay(1000);

    /*** Init micro SD-Card ***/
    tf.init();  //初始化tf卡
    lv_fs_if_init();  //初始化 文件系统

    /*** 设置WiFi ***/
    ssid = tf.readFileLine("/wifi.txt", 1);        // line-1 for WiFi ssid
    _ssid = ssid;
    password = tf.readFileLine("/wifi.txt", 2);    // line-2 for WiFi password
    _password=password;
    //tf.writeFile("/text.txt","aaaa\n");
    text=tf.readFileLine("/text.txt",1);
    //Serial.println(ssid);
    //Serial.println(password);

    location = tf.readFileLine("/location.txt",1);
    _location = location;
    key = tf.readFileLine("/weather.txt",2);
    
    /*** Read WiFi info from SD-Card, then scan & connect WiFi ***/
    wifi.init(ssid, password);
    wifi_status=wifi.status();
    // 初始化时间
    if(wifi_status){
        configTime(28800, 0, "ntp3.aliyun.com");
        if(getLocalTime(&timeinfo)){
            rtc.setTimeStruct(timeinfo); 
        }
    }
    Serial.println("gettime done");
    /*** Inflate GUI objects ***/
    setup_ui(&guider_ui);
    Serial.println("setup_ui done");
    setup_task();
    Serial.println("setup_task done");

    if(wifi_status){
        Serial.println("status");
        getWeather();
    }

}

int frame_id = 1;

// 串口缓冲变量
String comdata = "";

void loop()
{
    // run this as often as possible
    screen.routine();

    // 200 means update IMU data every 200ms
    mpu.update(200);
    //Serial.println(mpu.getAccelX());
    //Serial.println("hello");

    switch (button_state)
    {
    case 1:
        if(page_num>0)
            page_num--;
            lv_tabview_set_tab_act(tabview, page_num, LV_ANIM_OFF);
        break;
    case 2:
        if(page_num<3)
            page_num++;
            lv_tabview_set_tab_act(tabview, page_num, LV_ANIM_OFF);
        break;
    
    default:
        break;
    }

    //Serial.println(ambient.getLux());
    while (Serial.available() > 0){
        comdata += char(Serial.read());
        delay(2);
    }
    if (comdata.length() > 0)
    {  
        Serial.println(comdata); 
        if(comdata.startsWith("ssid")){
            comdata=comdata.substring(4,comdata.length());
            Serial.println(comdata);
            ssid=comdata;
        }
        if(comdata.startsWith("pswd")){
            comdata=comdata.substring(4,comdata.length());
            Serial.println(comdata);
            password = comdata;
        }
        if(comdata.startsWith("weat")){
            comdata=comdata.substring(4,comdata.length());
            Serial.println(comdata);
            location = comdata;
        }
        if(comdata.startsWith("text")){
            comdata=comdata.substring(4,comdata.length());
            Serial.println(comdata);
            if(!text.equals(comdata)){
                text=comdata;
                tf.writeFile("/text.txt",(text+"\n").c_str());
                lv_label_set_text(label_text, text.c_str());
            }
        }
        comdata = "";
    }

    if(!location.equals(_location)){
        _location=location;
        getWeather();
        tf.writeFile("/location.txt",(location+"\n").c_str());
        lv_label_set_text(weather_label_location, location.c_str());
        lv_label_set_text(label_city, location.c_str());
    }
    if(!ssid.equals(_ssid)&&!password.equals(_password)){
        _ssid=ssid;
        _password = password;
        tf.writeFile("/wifi.txt",(ssid+"\n"+password+"\n").c_str());
        wifi.init(ssid, password);
        
    }
    //delay(20);
    wifi_status=wifi.status();
    delay(10);
}

