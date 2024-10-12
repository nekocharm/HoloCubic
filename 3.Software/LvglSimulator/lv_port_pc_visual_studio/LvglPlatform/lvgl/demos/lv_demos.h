/**
 * @file lv_demos.h
 *
 */

#ifndef LV_DEMOS_H
#define LV_DEMOS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl.h"

#if LV_USE_DEMO_WIDGETS
#include "widgets/lv_demo_widgets.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Call lv_demo_xxx.
 * @param   info the information which contains demo name and parameters
 *               needs by lv_demo_xxx.
 * @size    size of information.
 */
bool lv_demos_create(char * info[], int size);

/**
 * Show help for lv_demos.
 */
void lv_demos_show_help(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_H*/
