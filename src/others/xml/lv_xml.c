/**
 * @file lv_xml.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "../../libs/expat/expat.h"
#include <stdio.h>
#include "lv_xml_private.h"
#include "lv_xml_obj_parser.h"
#include "lv_xml_button_parser.h"
#include "lv_xml_label_parser.h"
#include "lv_xml_slider_parser.h"
#include "lv_xml_tabview_parser.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _lv_widget_processor_t {
    const char * name;
    lv_xml_widget_process_cb_t cb;
    struct _lv_widget_processor_t * next;
} lv_widget_processor_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void start_element_handler(void * user_data, const char * name, const char ** attrs);
static void end_element_handler(void * user_data, const char * name, const char ** attrs);
//static void character_data_handler(void *user_data, const char *s, int len);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_widget_processor_t * processor_head;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_xml_init(void)
{
    lv_xml_register_processor("obj", lv_xml_obj_process);
    lv_xml_register_processor("button", lv_xml_button_process);
    lv_xml_register_processor("label", lv_xml_label_process);
    lv_xml_register_processor("slider", lv_xml_label_process);
    lv_xml_register_processor("tabview", lv_xml_tabview_process);
    lv_xml_register_processor("tabview-tab_bar", lv_xml_tabview_tab_bar_process);
    lv_xml_register_processor("tabview-tab", lv_xml_tabview_tab_process);
}

lv_result_t lv_xml_register_processor(const char * name, lv_xml_widget_process_cb_t cb)
{
    lv_widget_processor_t * p = lv_malloc(sizeof(lv_widget_processor_t));
    lv_memzero(p, sizeof(lv_widget_processor_t));

    p->cb = cb;
    p->name = lv_strdup(name);

    if(processor_head == NULL) processor_head = p;
    else {
        p->next = processor_head;
        processor_head = p;
    }
    return LV_RESULT_OK;
}

lv_result_t lv_xml_load_data(lv_obj_t * parent, const char * data, size_t data_len)
{
    lv_obj_clean(parent);

    // Initialize the parser state
    lv_xml_parser_state_t state = {};
    lv_ll_init(&state.parent_ll, sizeof(lv_obj_t *));
    lv_obj_t ** parent_node = lv_ll_ins_head(&state.parent_ll);
    *parent_node = parent;

    lv_ll_init(&state.style_ll, sizeof(lv_xml_style_t));

    // Create an XML parser and set handlers
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, &state);
    XML_SetElementHandler(parser, start_element_handler, end_element_handler);
    //  XML_SetCharacterDataHandler(parser, character_data_handler);

    // Parse the XML
    if(XML_Parse(parser, data, data_len, XML_TRUE) == XML_STATUS_ERROR) {
        LV_LOG_ERROR("XML parsing error: %s", XML_ErrorString(XML_GetErrorCode(parser)));
        XML_ParserFree(parser);
        return LV_RESULT_INVALID;
    }

    XML_ParserFree(parser);

    return LV_RESULT_OK;
}


lv_result_t lv_xml_load_file(lv_obj_t * parent, const char * path)
{

    lv_res_t res;
    char xml_buf[8 * 1024];
    FILE * f = fopen(path, "r");
    if(f == NULL) {
        LV_LOG_WARN("Couldn't open %s", path);
        return LV_RESULT_INVALID;
    }
    size_t rn = fread(xml_buf, 1, sizeof(xml_buf), f);
    if(rn == 0) {
        LV_LOG_WARN("Couldn't read %s", path);
        return LV_RESULT_INVALID;
    }

    if(rn == sizeof(xml_buf)) {
        LV_LOG_WARN("%s was too large to read at once", path);
        return LV_RESULT_INVALID;
    }

    res = lv_xml_load_data(parent, xml_buf, rn);
    if(res != LV_RESULT_OK) LV_LOG_WARN("An error occurred while processing %s", path);
    fclose(f);

    return res;

}

const char * lv_xml_get_value_of(const char ** attrs, const char * name)
{
    for(int i = 0; attrs[i]; i += 2) {
        if(lv_streq(attrs[i], name)) return attrs[i + 1];
    }

    LV_LOG_WARN("No value found for name:%s", name);
    return NULL;
}

void * lv_xml_state_get_parent(lv_xml_parser_state_t * state)
{
    return state->parent;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void start_element_handler(void * user_data, const char * name, const char ** attrs)
{
    lv_xml_parser_state_t * state = (lv_xml_parser_state_t *)user_data;
    bool is_view = false;
    if(lv_streq(name, "view")) {
        const char * extends = lv_xml_get_value_of(attrs, "extends");
        name = extends ? extends : "obj";
        is_view = true;
    }

    /*Select the widget specific parser type based on the name*/
    if(lv_streq(name, "styles")) return;
    else if(lv_streq(name, "style")) lv_xml_style_process(state, attrs);
    else {
        lv_obj_t ** current_parent_p = lv_ll_get_tail(&state->parent_ll);
        if(current_parent_p == NULL) state->parent = lv_screen_active();
        else state->parent = *current_parent_p;
        void * item = NULL;

        lv_widget_processor_t * p = processor_head;
        while(p) {
            if(lv_streq(p->name, name)) {
                item = p->cb(state, attrs);
                break;
            }

            p = p->next;
        }

        if(item == NULL) {
            LV_LOG_WARN("%s in not a known widget or element", name);
            return;
        }

        void ** new_parent = lv_ll_ins_tail(&state->parent_ll);
        *new_parent = item;

        if(is_view) {
            state->view = item;
        }
    }
}
static void end_element_handler(void * user_data, const char * name, const char ** attrs)
{
    LV_UNUSED(attrs);
    lv_xml_parser_state_t * state = (lv_xml_parser_state_t *)user_data;

    lv_obj_t ** current_parent = lv_ll_get_tail(&state->parent_ll);
    if(current_parent) lv_ll_remove(&state->parent_ll, current_parent);
}


//char *strip(char *str) {
//    char *end;
//
//    // Trim leading spaces
//    while (isspace((unsigned char)*str)) str++;
//
//    if (*str == 0) { // All spaces?
//        return str;
//    }
//
//    // Trim trailing spaces
//    end = str + strlen(str) - 1;
//    while (end > str && isspace((unsigned char)*end)) end--;
//
//    // Write new null terminator
//    *(end + 1) = '\0';
//
//    return str;
//}
//
//static void character_data_handler(void *user_data, const char *s, int len)
//{
//  char t[1000] = {};
//  memcpy(t, s, len);
//  t[len] = '\0';
//  const char * t2 = strip(t);
//  if(strlen(t2)) printf("%s\n", t2);
//}
