// called once a frame during show goals state to process events and render the screen
void mission_show_goals_do_frame(float frametime)
{
	int k, i, y, z;
	int font_height = gr_get_font_height();
	
	k = Goals_screen_ui_window.process();
	switch (k) {
		case KEY_ESC:
			mission_goal_exit();			
			break;
		
		case KEY_DOWN:
			goal_screen_scroll_down();
			break;

		case KEY_UP:
			goal_screen_scroll_up();
			break;

		default:
			// do nothing
			break;
	}	// end switch

	for (i=0; i<NUM_GOAL_SCREEN_BUTTONS; i++){
		if (Goal_buttons[i].button.pressed()){
			goal_screen_button_pressed(i);
		}
	}

	GR_MAYBE_CLEAR_RES(Goals_screen_bg_bitmap);
	if (Goals_screen_bg_bitmap >= 0) {
		gr_set_bitmap(Goals_screen_bg_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	}
	Goals_screen_ui_window.draw();

	y = 0;
	z = Scroll_offset;
	while (y + font_height <= Goal_screen_text_h) {
		Goal_text.display(z, y);
		y += font_height;
		z++;
	}

	Primary_goal_list.icons_display(Scroll_offset);
	Secondary_goal_list.icons_display(Scroll_offset);
	Bonus_goal_list.icons_display(Scroll_offset);

	gr_flip();
}