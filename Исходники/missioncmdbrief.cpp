void cmd_brief_do_frame(float frametime)
{
	char buf[40];
	int i, k, w, h, x, y;

	// if no command briefing exists, skip this screen.
	if (!Cmd_brief_inited) {
		cmd_brief_exit();
		return;
	}

	if ( help_overlay_active(CMD_BRIEF_OVERLAY) ) {
		Cmd_brief_buttons[gr_screen.res][CMD_BRIEF_BUTTON_HELP].button.reset_status();
		Ui_window.set_ignore_gadgets(1);
	}

	k = Ui_window.process() & ~KEY_DEBUGGED;

	if ( (k > 0) || B1_JUST_RELEASED ) {
		if ( help_overlay_active(CMD_BRIEF_OVERLAY) ) {
			help_overlay_set_state(CMD_BRIEF_OVERLAY, 0);
			Ui_window.set_ignore_gadgets(0);
			k = 0;
		}
	}

	if ( !help_overlay_active(CMD_BRIEF_OVERLAY) ) {
		Ui_window.set_ignore_gadgets(0);
	}

	switch (k) {
	case KEY_ESC:
		common_music_close();
		gameseq_post_event(GS_EVENT_MAIN_MENU);
		break;
	}	// end switch

	for (i=0; i<NUM_CMD_BRIEF_BUTTONS; i++){
		if (Cmd_brief_buttons[gr_screen.res][i].button.pressed()){
			cmd_brief_button_pressed(i);
		}
	}

	cmd_brief_voice_play(Cur_stage);
	common_music_do();

	if (cmd_brief_check_stage_done() && Player->auto_advance && (Cur_stage < Cur_cmd_brief->num_stages - 1)){
		if((Cur_Anim.num_frames <= 1) || Cur_Anim.done_playing) {
			cmd_brief_new_stage(Cur_stage + 1);
		}
	}

	GR_MAYBE_CLEAR_RES(Cmd_brief_background_bitmap);
	if (Cmd_brief_background_bitmap >= 0) {
		gr_set_bitmap(Cmd_brief_background_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	} 

	if(Cur_Anim.num_frames > 0) {
		bm_get_info((Cur_Anim.streaming) ? Cur_Anim.bitmap_id : Cur_Anim.first_frame, &x, &y, NULL, NULL, NULL);
		x = Cmd_image_center_coords[gr_screen.res][CMD_X_COORD] - x / 2;
		y = Cmd_image_center_coords[gr_screen.res][CMD_Y_COORD] - y / 2;
		generic_anim_render(&Cur_Anim, (Cmd_brief_paused) ? 0 : frametime, x, y, true);
	}

	Ui_window.draw();

	if (!Player->auto_advance){
		Cmd_brief_buttons[gr_screen.res][CMD_BRIEF_BUTTON_PAUSE].button.draw_forced(2);
	}

	gr_set_font(FONT1);
	gr_set_color_fast(&Color_text_heading);

	sprintf(buf, XSTR( "Stage %d of %d", 464), Cur_stage + 1, Cur_cmd_brief->num_stages);
	gr_get_string_size(&w, NULL, buf);
	gr_string(Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_X_COORD] + Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_W_COORD] - w, Cmd_stage_y[gr_screen.res], buf, GR_RESIZE_MENU);

	if (brief_render_text(Top_cmd_brief_text_line, Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_X_COORD], Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_Y_COORD], Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_H_COORD], frametime, 0, 1)){
		Voice_good_to_go = 1;
	}

	if (gr_screen.res == 1) {
		Max_cmdbrief_Lines = 166/gr_get_font_height(); //Make the max number of lines dependent on the font height. 225 and 85 are magic numbers, based on the window size in retail. 
	} else {
		Max_cmdbrief_Lines = 116/gr_get_font_height();
	}

	// maybe output the "more" indicator
	if ( Max_cmdbrief_Lines < Num_brief_text_lines[0] ) {
		// can be scrolled down
		int more_txt_x = Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_X_COORD] + (Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_W_COORD]/2) - 10;
		int more_txt_y = Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_Y_COORD] + Cmd_text_wnd_coords[Uses_scroll_buttons][gr_screen.res][CMD_H_COORD] - 2;				// located below brief text, centered

		gr_get_string_size(&w, &h, XSTR("more", 1469), strlen(XSTR("more", 1469)));
		gr_set_color_fast(&Color_black);
		gr_rect(more_txt_x-2, more_txt_y, w+3, h, GR_RESIZE_MENU);
		gr_set_color_fast(&Color_red);
		gr_string(more_txt_x, more_txt_y, XSTR("more", 1469), GR_RESIZE_MENU);  // base location on the input x and y?
	}

	// blit help overlay if active
	help_overlay_maybe_blit(CMD_BRIEF_OVERLAY);

	gr_flip();
}