#include "parser_state.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	const char * name;
	lv_obj_t * (*process_cb)(lv_obj_t * ,const char ** atts);
}widget_process_t;

static inline bool streq(const char * str1, const char * str2) {
	return strcmp(str1, str2) == 0;
}

lv_align_t align_string_to_value(const char * txt)
{
	if(streq(txt, "center")) return LV_ALIGN_CENTER;
	if(streq(txt, "top_left")) return LV_ALIGN_TOP_LEFT;
	if(streq(txt, "bottom_right")) return LV_ALIGN_BOTTOM_RIGHT;

	LV_LOG_WARN("%s is an unknown align value", txt);
	return 0;
}


void obj_apply_atts(lv_obj_t * obj, const char ** atts)
{
	for(int i = 0; atts[i]; i += 2) {
		const char * name = atts[i];
		const char * value = atts[i + 1];
		if (streq(name, "width")) lv_obj_set_width(obj, atoi(value));
		else if (streq(name, "height")) lv_obj_set_height(obj, atoi(value));
		else if (streq(name, "x")) lv_obj_set_x(obj, atoi(value));
		else if (streq(name, "y")) lv_obj_set_y(obj, atoi(value));
		else if (streq(name, "align")) lv_obj_set_align(obj, align_string_to_value(value));
	}

}

static lv_obj_t * obj_process_cb(lv_obj_t * parent, const char **atts)
{
	lv_obj_t * obj = lv_obj_create(parent);
	obj_apply_atts(obj, atts);

	return obj;
}

static lv_obj_t * button_process_cb(lv_obj_t * parent, const char **atts)
{
	lv_obj_t * obj = lv_button_create(parent);
	obj_apply_atts(obj, atts);

	return obj;
}

static lv_slider_mode_t slider_mode_string_to_value(const char * txt)
{
	if(streq(txt, "normal")) return LV_SLIDER_MODE_NORMAL;
	if(streq(txt, "symmetrical")) return LV_SLIDER_MODE_SYMMETRICAL;
	if(streq(txt, "range")) return LV_SLIDER_MODE_RANGE;

	LV_LOG_WARN("%s is an unknown slider mode value", txt);
	return 0;
}


static lv_obj_t * slider_process_cb(lv_obj_t * parent, const char **atts)
{
	lv_obj_t * obj = lv_slider_create(parent);
	obj_apply_atts(obj, atts);

	for(int i = 0; atts[i]; i += 2) {
		const char * name = atts[i];
		const char * value = atts[i + 1];
		if (strcmp(name, "value") == 0) lv_slider_set_value(obj, atoi(value), LV_ANIM_OFF);
		else if (strcmp(name, "mode") == 0) lv_slider_set_mode(obj, slider_mode_string_to_value(value));

	}

	return obj;
}

static lv_label_long_mode_t label_long_mode_string_to_value(const char * txt)
{
	if(streq(txt, "wrap")) return LV_LABEL_LONG_WRAP;
	if(streq(txt, "dot")) return LV_LABEL_LONG_DOT;
	if(streq(txt, "long_scroll")) return LV_LABEL_LONG_SCROLL;
	if(streq(txt, "scroll_circular")) return LV_LABEL_LONG_SCROLL_CIRCULAR;
	if(streq(txt, "clip")) return LV_LABEL_LONG_CLIP;

	LV_LOG_WARN("%s is an unknown label long mode value", txt);
	return 0;
}

static lv_obj_t * label_process_cb(lv_obj_t * parent, const char **atts)
{
	lv_obj_t * obj = lv_label_create(parent);
	obj_apply_atts(obj, atts);

	for(int i = 0; atts[i]; i += 2) {
		const char * name = atts[i];
		const char * value = atts[i + 1];
		 if (streq(name, "text"))lv_label_set_text(obj, value);
		 else if (streq(name, "long_mode")) lv_label_set_long_mode(obj, label_long_mode_string_to_value(value));
	}

	return obj;
}


widget_process_t widget_processors[] =
{
		{.name = "obj", .process_cb = obj_process_cb},
		{.name = "button", .process_cb = button_process_cb},
		{.name = "slider", .process_cb = slider_process_cb},
		{.name = "label", .process_cb = label_process_cb},
		{.name = NULL, .process_cb = NULL}
};


// Start element handler
void start_element_handler(void *userData, const char *name, const char **atts) {

	if(streq(name, "view")) return;

    ParserState *state = (ParserState *)userData;

    lv_obj_t ** current_parent_p = lv_ll_get_tail(&state->parent_ll);
    lv_obj_t * current_parent;
    if(current_parent_p == NULL) current_parent = lv_screen_active();
    else current_parent = *current_parent_p;
    void * item;
    /*Select the widget specific parser type based on the name*/
    if(streq(name, "obj")) item = obj_process_cb(current_parent, atts);
    if(streq(name, "button")) item = button_process_cb(current_parent, atts);
    if(streq(name, "slider")) item = slider_process_cb(current_parent, atts);
    if(streq(name, "label")) item = label_process_cb(current_parent, atts);

    if(item == NULL) {
    	LV_LOG_WARN("%s in not a known widget", name);
    	return;
    }

    lv_obj_t ** new_parent = lv_ll_ins_tail(&state->parent_ll);
    *new_parent = item;
}


// End element handler
void end_element_handler(void *userData, const char *name) {
    ParserState *state = (ParserState *)userData;

    lv_obj_t ** current_parent = lv_ll_get_tail(&state->parent_ll);
    if(current_parent) lv_ll_remove(&state->parent_ll, current_parent);
}

// Character data handler
void character_data_handler(void *userData, const char *s, int len) {
    // Handle character data if needed
}
