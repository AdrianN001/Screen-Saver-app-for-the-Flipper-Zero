#pragma once

#ifndef VERTICAL_OFFSET
#define VERTICAL_OFFSET 3
#endif

void move_the_text(App* app){
	if ((app->x_position + app->horizontal_velocity + app->current_string_length > MAX_WIDTH) || (app->x_position + app->horizontal_velocity < 0) ) app->horizontal_velocity *= -1;
	if ((app->y_position + app->vertical_velocity + VERTICAL_OFFSET  >= MAX_HEIGHT) || (app->y_position + app->vertical_velocity < 0) )  app->vertical_velocity *= -1;
	app->x_position += app->horizontal_velocity;
	app->y_position += app->vertical_velocity;
}

int32_t animate_text_in_the_box( void* context ){

	App* app = context;

	for (;;){
		widget_add_string_element(
			app->widget, 
			app->x_position,
			app->y_position,
			AlignLeft,
			AlignTop,
			FontSecondary,
			app->current_string);
		
		furi_delay_ms(DELAY);
		widget_reset(app->widget);
		move_the_text(app);
	}

	return 0;
		
}
