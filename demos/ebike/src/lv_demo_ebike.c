/**
 * @file lv_demo_ebike.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_ebike.h"
#include "lv_demo_ebike_home.h"
#include "lv_demo_ebike_settings.h"
#include "lv_demo_ebike_stat.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_ebike_create(void)
{
    lv_display_t * display = lv_display_get_default();
    lv_theme_t * theme = lv_theme_simple_init(display);
    lv_display_set_theme(display, theme);

    LV_IMAGE_DECLARE(img_ebike_bg);
    lv_obj_t * bg = lv_image_create(lv_screen_active());
    lv_image_set_src(bg, &img_ebike_bg);
    lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);

    lv_obj_remove_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_white(), 0);
    lv_obj_set_style_pad_right(lv_screen_active(), 44, 0);

    //  lv_demo_ebike_home_create();
    //  lv_demo_ebike_settings_create();
    lv_demo_ebike_stat_create();

    lv_obj_t * menu_cont = lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_color(menu_cont, lv_color_black(), 0);
    lv_obj_set_size(menu_cont, 44, lv_pct(100));
    lv_obj_align(menu_cont, LV_ALIGN_RIGHT_MID, 44, 0);
    lv_obj_set_flex_flow(menu_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(menu_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    LV_IMAGE_DECLARE(img_ebike_settings);
    lv_obj_t * icon1 = lv_image_create(menu_cont);
    lv_image_set_src(icon1, &img_ebike_settings);

    LV_IMAGE_DECLARE(img_ebike_stat);
    lv_obj_t * icon2 = lv_image_create(menu_cont);
    lv_image_set_src(icon2, &img_ebike_stat);

    LV_IMAGE_DECLARE(img_ebike_home);
    lv_obj_t * icon3 = lv_image_create(menu_cont);
    lv_image_set_src(icon3, &img_ebike_home);


}

/**********************
 *   STATIC FUNCTIONS
 **********************/
