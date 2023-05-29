#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/widget.h>
#include <gui/modules/text_input.h>

typedef struct screen_saver_state {
	char* current_string;
	size_t current_string_length;
	short horizontal_velocity;
	short vertical_velocity;
	int x_position;
	int y_position;
	
	
	SceneManger* scene_manager;
	ViewDispatcher* view_dispatcher;
	Widget *widget;
	TextInput* text_input;
} App;

// Defined in the handles.h
static App* app_alloc();
static void app_free();
