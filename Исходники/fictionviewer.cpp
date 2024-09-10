// do
void fiction_viewer_do_frame(float frametime)
{
	int i, k, w, h;

	// make sure we exist
	if (!Fiction_viewer_inited)
	{
		fiction_viewer_exit();
		return;
	}

	// process keys
	k = Fiction_viewer_window.process() & ~KEY_DEBUGGED;	

	switch (k)
	{
		case KEY_ESC:
			common_music_close();
			gameseq_post_event(GS_EVENT_MAIN_MENU);
			return;
	}

	// process button presses
	for (i = 0; i < NUM_FVW_BUTTONS; i++)
		if (Fiction_viewer_buttons[Fiction_viewer_ui][gr_screen.res][i].button.pressed())
			fiction_viewer_button_pressed(i);
	
	common_music_do();

	// clear
	GR_MAYBE_CLEAR_RES(Fiction_viewer_bitmap);
	if (Fiction_viewer_bitmap >= 0)
	{
		gr_set_bitmap(Fiction_viewer_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	} 
	
	// draw the window
	Fiction_viewer_window.draw();		

	// render the briefing text
	brief_render_text(Top_fiction_viewer_text_line, Fiction_viewer_text_coordinates[Fiction_viewer_ui][gr_screen.res][0], Fiction_viewer_text_coordinates[Fiction_viewer_ui][gr_screen.res][1], Fiction_viewer_text_coordinates[Fiction_viewer_ui][gr_screen.res][3], frametime);

	// maybe output the "more" indicator
	if ((Fiction_viewer_text_max_lines + Top_fiction_viewer_text_line) < Num_brief_text_lines[0])
	{
		use_std_font();

		// can be scrolled down
		int more_txt_x = Fiction_viewer_text_coordinates[Fiction_viewer_ui][gr_screen.res][0] + (Fiction_viewer_text_coordinates[Fiction_viewer_ui][gr_screen.res][2]/2) - 10;
		int more_txt_y = Fiction_viewer_text_coordinates[Fiction_viewer_ui][gr_screen.res][1] + Fiction_viewer_text_coordinates[Fiction_viewer_ui][gr_screen.res][3];				// located below text, centered

		gr_get_string_size(&w, &h, XSTR("more", 1469), strlen(XSTR("more", 1469)));
		gr_set_color_fast(&Color_black);
		gr_rect(more_txt_x-2, more_txt_y, w+3, h, GR_RESIZE_MENU);
		gr_set_color_fast(&Color_more_indicator);
		gr_string(more_txt_x, more_txt_y, XSTR("more", 1469), GR_RESIZE_MENU);  // base location on the input x and y?

		use_fv_font();
	}

	gr_flip();
}