#include <furi.h>
#include "state.h"
#include "handles.h"

int screen_saver_entry(void *p){
	UNUSED(p);
	
	
	furi_delay_ms(2000);
	
	return 0;
}
