/**
 * @file lv_demo_ebike_lottie.h
 *
 */

#ifndef LV_DEMO_EBIKE_LOTTIE_H
#define LV_DEMO_EBIKE_LOTTIE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../../lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t  * lv_lottie_create(lv_obj_t * parent, const char * src, size_t src_size, int32_t w, int32_t h, uint8_t * buf);

/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DEMO_EBIKE_LOTTIEH*/
