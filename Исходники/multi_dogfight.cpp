// do frame
void multi_df_debrief_do()
{
	int k, new_k;
	char buf[256];
	
	k = chatbox_process();	
	new_k = Multi_df_window.process(k, 0);	

	// process keypresses
	switch(new_k){
	case KEY_ESC:
		multi_debrief_esc_hit();
		break;
	}

	// process buttons	
	multi_df_process_buttons();

	// music stuff
	common_music_do();

	// process debriefing details
	multi_debrief_do_frame();

	// draw the background
	GR_MAYBE_CLEAR_RES(Multi_df_background_bitmap);
	if (Multi_df_background_bitmap >= 0) {
		gr_set_bitmap(Multi_df_background_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	} 

	// draw the window
	Multi_df_window.draw();	

	// kill matrix
	multi_df_blit_kill_matrix();

	// render the chatbox
	chatbox_render();

	// draw the mission title
	strcpy_s(buf, The_mission.name);
	font::force_fit_string(buf, 255, Kill_matrix_title_coords[gr_screen.res][2]);
	gr_set_color_fast(&Color_bright_white);
	gr_string(Kill_matrix_title_coords[gr_screen.res][0], Kill_matrix_title_coords[gr_screen.res][1], buf, GR_RESIZE_MENU);

	// flip
	gr_flip();
}