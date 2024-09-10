// called once per frame when game state is GS_STATE_RED_ALERT
void red_alert_do_frame(float frametime)
{
	int i, k;	

	// ensure that the red alert interface has been initialized
	if (!Red_alert_inited) {
		Int3();
		return;
	}

	// commit if skipping briefing, but not in multi - Goober5000
	if (!(Game_mode & GM_MULTIPLAYER)) {
		if (The_mission.flags[Mission::Mission_Flags::No_briefing])
		{
			red_alert_button_pressed(RA_CONTINUE);
			return;
		}
	}

	k = Ui_window.process() & ~KEY_DEBUGGED;
	switch (k) {
		case KEY_ESC:
//			gameseq_post_event(GS_EVENT_ENTER_GAME);
			gameseq_post_event(GS_EVENT_MAIN_MENU);
			break;
	}	// end switch

	for (i=0; i<NUM_BUTTONS; i++){
		if (Buttons[gr_screen.res][i].button.pressed()){
			red_alert_button_pressed(i);
		}
	}

	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	} 

	Ui_window.draw();
	// hud_anim_render(&Flash_anim, frametime);

	font::set_font(font::FONT1);

	if ( timestamp_elapsed(Text_delay) ) {
		int finished_wipe = 0;
		if ( Briefing->num_stages > 0 ) {
			finished_wipe = brief_render_text(0, Ra_brief_text_wnd_coords[gr_screen.res][RA_X_COORD], Ra_brief_text_wnd_coords[gr_screen.res][RA_Y_COORD], Ra_brief_text_wnd_coords[gr_screen.res][RA_H_COORD], frametime, 0);
		}

		if (finished_wipe) {
			red_alert_voice_play();
		}
	}

	// blit incoming transmission
	red_alert_blit_title();

	gr_flip();
}