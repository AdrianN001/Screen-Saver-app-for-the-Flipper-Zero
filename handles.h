#pragma once
#include "state.h"
#include "scenes.h"
#include "views.h"

void screen_saver_animation_on_enter(void *context){
	UNUSED(context);
}

bool screen_saver_animation_on_event(void *context, SceneManagerEvent event){
	UNUSED(context);
	UNUSED(event);
	return 0;
}

void screen_saver_animation_on_exit(void *context){
	UNUSED(context)
}

void screen_saver_text_input_on_enter(void *context){
	UNUSED(context);
}

bool screen_saver_text_input_on_event(void *context, SceneManagerEvent event){
	UNUSED(context);
	UNUSED(event);
	return 0;
}

void screen_saver_text_input_on_exit(void *context){
	UNUSED(context)
}

/* 			Custom event handlers  						*/

bool screen_saver_custom_callback(void *context, uint32_t custom_event) {
	furi_assert(context);
	App* app = context;
	return scene_manager_handle_custom_event(app->scene_manager, custom_event);
}	 

bool screen_saver_back_event_callback(void *context) {
	furi_assert(context);
	App* app = context;
	return scene_manager_handle_back_event(app->scene_manager);
}

/* 			Arrays of the event handlers 					*/

void (*const screen_saver_on_enter_handlers[])(*void) = {
	screen_saver_animation_on_enter,
	screen_saver_text_input_on_enter
}

bool (*const screen_saver_on_event_handlers[])(*void, SceneMangerEvent) = {
	screen_saver_animation_on_event,
	screen_saver_text_input_on_event
}

void (*const screen_saver_on_exit_handlers[])(*void) = {
	screen_saver_animation_on_exit,
	screen_saver_text_input_on_exit
}

static const SceneManagerHandlers screen_saver_scene_manager_handlers = {
	.on_enter_handlers = screen_saver_on_enter_handlers,
	.on_event_handlers = screen_saver_on_event_handlers,
	.on_exit_handlers  = screen_saver_on_exit_handlers,
	.scene_num         = ScreenSaverSceneCount
}

/* 			Constructor for the App						*/


static App* app_alloc() {
	App* app = malloc(sizeof(App));
	
															// Scene Manager switches between the pages
	app->scene_manager = scene_manager_alloc(					
		&screen_saver_scene_manager_handlers,
		app);
	
	app->view_dispatcher = view_dispatcher_alloc();
	view_dispatcher_enable_queue(app->view_dispatcher);	
    	view_dispatcher_set_event_callback_context(app->view_dispatcher, app); 						// sets the paramter void* context to the app
    	view_dispatcher_set_custom_event_callback(app->view_dispatcher, screen_saver_custom_callback);  		// sets the custom event callback (l. 36) as the def. callback
    	view_dispatcher_set_navigation_event_callback( app->view_dispatcher, screen_saver_back_event_callback );	// sets the back b. event callback (l. 42 ) as the def. callback
    	
    	
    	// 				Adds the different views to the app 
    	// Enums serve as IDs
    	app->widget = widget_alloc();											
    	view_dispatcher_add_view(
    		app->view_dispather,
    		ScreenSaverWidgetView,										
    		widget_get_view(app->widget));
    	
    	app->text_input = text_input_alloc();
    	view_dispatcher_add_view(
    		app->view_dispatcher,
    		ScreenSaverTextInputView,
    		text_input_get_view(app->text_input));
	
	return app;
}

static void app_free(App* app){
	furi_assert(app);
	
	// Deletes the view from the dispatcher
	view_dispatcher_remove_view(app->view_dispatcher, ScreenSaverWidgetView);
	view_dispatcher_remove_view(app->view_dispatcher, ScreenSaverTextInputView);

	// Frees the different components of the app	
	scene_manager_free(app->scene_manager);
	view_dispacther_free(app->view_dispatcher);
	widget_free(app->widget);
	text_input_free(app->text_input);


	free(app);
}
	
    	
	

