/**
 * @file lv_demo_ebike.h
 *
 */

#ifndef LV_DEMO_EBIKE_H
#define LV_DEMO_EBIKE_H

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
#define EBIKE_COLOR_TURQUOISE lv_color_hex(0x55FFEB)
#define EBIKE_COLOR_LIME lv_color_hex(0x91FF3B)
#define EBIKE_LARGE 0

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/
extern lv_subject_t ebike_subject_speed_arc;
extern lv_subject_t ebike_subject_speed_roller;
extern lv_subject_t ebike_subject_portrait;
extern lv_subject_t ebike_subject_language;

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DEMO_EBIKE_H*/
