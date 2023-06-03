#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <furi/core/thread.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/widget.h>
#include <gui/modules/text_input.h>

#define MAX_HEIGHT			60    
#define MAX_WIDTH			100
#define BLANK_SPACE			" "
#define NEW_LINE			"\n"
#define DELAY				100   // 10 fps

#define randint(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min))


typedef struct screen_saver_state {
	char* current_string;
	size_t current_string_length;
	short horizontal_velocity;
	short vertical_velocity;
	int x_position;
	int y_position;
	
	
	SceneManager* scene_manager;
	ViewDispatcher* view_dispatcher;
	Widget *widget;
	TextInput* text_input;

	FuriThread* animation_thread;
	FuriThreadId animation_thread_id;
} App;

// Defined in the handles.h
static App* app_alloc();
static void app_free();
FuriThread* animaton_thread_alloc();

int string_size(char* str){
	int size = 0;	
	while( *str++ != '\0') { size++; }
	return size;
}
