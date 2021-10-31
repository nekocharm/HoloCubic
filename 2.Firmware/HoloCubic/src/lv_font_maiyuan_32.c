/*
*---------------------------------------------------------------
*                        Lvgl Font Tool                         
*                                                               
* 注:使用unicode编码                                              
* 注:本字体文件由Lvgl Font Tool V0.4 生成                          
* 作者:阿里(qq:617622104)                                         
*---------------------------------------------------------------
*/


#include "lvgl.h"


typedef struct{
    uint16_t min;
    uint16_t max;
    uint8_t  bpp;
    uint8_t  reserved[3];
}x_header_t;
typedef struct{
    uint32_t pos;
}x_table_t;
typedef struct{
    uint8_t adv_w;
    uint8_t box_w;
    uint8_t box_h;
    int8_t  ofs_x;
    int8_t  ofs_y;
    uint8_t r;
}glyph_dsc_t;
typedef struct {
    uint32_t unicode;
    uint8_t bmp[512];
}lv_font_maiyuan_24_bmp_t;

typedef struct {
    uint32_t unicode;
    glyph_dsc_t gd;
}lv_font_maiyuan_24_dsc_t;

static x_header_t __g_xbf_hd = {
    .min = 0x0020,
    .max = 0x9fa0,
    .bpp = 4,
};


static uint8_t __buf[8];//如bin文件存在SPI FLASH可使用此buff
static lv_fs_file_t font_f;
static uint8_t fontisopen=0;
static int bmp_len=-1;
static int dsc_len=-1;
static lv_font_maiyuan_24_bmp_t maiyuan_24[10]={
    {
        .unicode=0,
    }
};
static lv_font_maiyuan_24_dsc_t maiyuan_24_dsc[10]={
    {
        .unicode=0,
    }
};

static int16_t __user_font_judge_bmp(uint32_t code){

    uint16_t i;
    for(i=0;i<bmp_len;i++){
        if((maiyuan_24+i)->unicode==code){
            return i;
        } 
    }
    bmp_len++;
    if(bmp_len==10) bmp_len=0;
    return -1;
}

static int16_t __user_font_judge_dsc(uint32_t code){

    uint16_t i;
    for(i=0;i<dsc_len+1;i++){
        if((maiyuan_24_dsc+i)->unicode==code){
            return i;
        } 
    }
    dsc_len++;
    if(dsc_len==10) dsc_len=0;
    //LV_LOG_ERROR("code%d , len%d",code,dsc_len);
    return -1;
}

static void __user_font_getdata(int offset, int size, uint8_t* buf){
    //如字模保存在SPI FLASH, SPIFLASH_Read(__g_font_buf,offset,size);
    //如字模已加载到SDRAM,直接返回偏移地址即可如:return (uint8_t*)(sdram_fontddr+offset);
    
    if(fontisopen==0){
        lv_fs_open(&font_f,"S:/font/lv_font_maiyuan_32.bin",LV_FS_MODE_RD);
        fontisopen=1;
    }
    
    lv_fs_seek(&font_f,offset);
    lv_fs_read(&font_f, buf,size,NULL);
}
static const uint8_t * __user_font_get_bitmap(const lv_font_t * font, uint32_t unicode_letter) {
    
    if( unicode_letter>__g_xbf_hd.max || unicode_letter<__g_xbf_hd.min ) {
        return NULL;
    }
    int code=__user_font_judge_bmp(unicode_letter);
    if (code==-1){
        uint32_t unicode_offset = sizeof(x_header_t)+(unicode_letter-__g_xbf_hd.min)*4;
        __user_font_getdata(unicode_offset, 4, maiyuan_24[bmp_len].bmp);
        uint32_t * p_pos = (uint32_t *) maiyuan_24[bmp_len].bmp;
        if( p_pos[0] != 0 ) {
            uint32_t pos = p_pos[0];
            __user_font_getdata(pos, sizeof(glyph_dsc_t), maiyuan_24[bmp_len].bmp);
            glyph_dsc_t * gdsc=(glyph_dsc_t *) maiyuan_24[bmp_len].bmp;
            __user_font_getdata(pos+sizeof(glyph_dsc_t), gdsc->box_w*gdsc->box_h*__g_xbf_hd.bpp/8,maiyuan_24[bmp_len].bmp);
            maiyuan_24[bmp_len].unicode=unicode_letter;
            return maiyuan_24[bmp_len].bmp;
        }
    }
    return maiyuan_24[code].bmp;
}


static bool __user_font_get_glyph_dsc(const lv_font_t * font, lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter, uint32_t unicode_letter_next) {
    //LV_LOG_ERROR("dsc%d,dsc_len%d",unicode_letter,dsc_len);
    if( unicode_letter>__g_xbf_hd.max || unicode_letter<__g_xbf_hd.min ) {
        return NULL;
    }
    int code=__user_font_judge_dsc(unicode_letter);
    glyph_dsc_t * gdsc=NULL;
    if(code==-1){
        uint32_t unicode_offset = sizeof(x_header_t)+(unicode_letter-__g_xbf_hd.min)*4;
        __user_font_getdata(unicode_offset, 4, __buf);
        uint32_t *p_pos = (uint32_t *)__buf;
        if( p_pos[0] != 0 ) {
            __user_font_getdata(p_pos[0], sizeof(glyph_dsc_t), (uint8_t *)&(maiyuan_24_dsc[dsc_len].gd));
            gdsc = &(maiyuan_24_dsc[dsc_len].gd);
        }
        maiyuan_24_dsc[dsc_len].unicode=unicode_letter;
    }else{
        gdsc = &(maiyuan_24_dsc[code].gd);
    }
    dsc_out->adv_w = gdsc->adv_w;
    dsc_out->box_h = gdsc->box_h;
    dsc_out->box_w = gdsc->box_w;
    dsc_out->ofs_x = gdsc->ofs_x;
    dsc_out->ofs_y = gdsc->ofs_y;
    dsc_out->bpp   = __g_xbf_hd.bpp;
    
    return true;
}


//Kingnam Maiyuan Beta,,-1
//字模高度：32
//XBF字体,外部bin文件
lv_font_t lv_font_maiyuan_32 = {
    .get_glyph_bitmap = __user_font_get_bitmap,
    .get_glyph_dsc = __user_font_get_glyph_dsc,
    .line_height = 32,
    .base_line = 0,
};

