#include <furi.h>
#include "state.h"
#include "handles.h"

int screen_saver_entry(void *p){
	UNUSED(p);
	
	App *app = app_alloc();
	
	Gui* gui = furi_record_open(RECORD_GUI);
	
	view_dispatcher_attach_to_gui(
		app->view_dispatcher,
		gui,
		ViewDispatcherTypeFullscreen);
	
	// Set the first scene
	scene_manager_next_scene(
		app->scene_manager,
		ScreenSaverWidgetView);
		
	view_dispatcher_run(app->view_dispatcher);
	
	app_free(app);
	
	
	return 0;
}
