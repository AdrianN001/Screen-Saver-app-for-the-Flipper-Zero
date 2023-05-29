#pragma once


void move_the_text(App* app){
	if ((app->x_position + app->horizontal_velocity + app->current_string_length > MAX_WIDTH) || (app->x_position + app->horizontal_velocity < 0) ) app->horizontal_velocity *= -1;
	if ((app->y_position + app->vertical_velocity  >= MAX_HEIGHT) || (app->y_position + app->vertical_velocity < 0) )  app->vertical_velocity *= -1;
	app->x_position += app->horizontal_velocity;
	app->y_position += app->vertical_velocity;
}

void animate_text_in_the_box( App* app ){
	for (;;){
		widget_add_string_element(
			app->widget, 
			app->x_position,
			app->y_position,
			AlignLeft,
			AlignCenter,
			FontPrimary,
			app->current_string);
		
		furi_delay_ms(DELAY);
		widget_reset(app->widget);
		move_the_text(app);
	}
		
}
