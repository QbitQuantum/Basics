void pilot_manage_do(void)
{
	int k = Ui_window.process();
	int i;

	
	if ( k > 0 ) {
// put back in when overlay stuff is fixed
		//		if ( help_overlay_active(PILOT_MANAGE_OVERLAY) ) {
//			help_overlay_set_state(PILOT_MANAGE_OVERLAY,0);
//			k = 0;
//		}
	}

	
	switch (k)
	{
		case KEY_ESC:  // cancel only if not trying to enter a pilot name
			if (!pilot_manage_callsign_enter_mode)
				gameseq_post_event(GS_EVENT_BARRACKS_MENU);//GS_EVENT_PREVIOUS_STATE
			break;
	} // end switch
	
	int prospective_pilot = -1;
	// Entering pilot callsign
	if (pilot_manage_callsign_enter_mode) {
		// set focus to inputbox
		Inputbox.set_focus();

		switch (k) {
			case KEY_ESC:
				// cancel create pilot
				Num_pilots--;
				for (i=0; i<Num_pilots; i++) {
					strcpy(Pilots[i], Pilots[i + 1]);
					Pilot_ranks[i] = Pilot_ranks[i + 1];
				}

				pilot_manage_set_callsign_enter_mode(false);
				break;
			
					
			case KEY_ENTER: 
				pilot_manage_accept_new_pilot_callsign();
				break;
		} 
	} 

	// process buttons
		for (i=0; i<PM_NUM_BUTTONS; i++) {
			if (Buttons[gr_screen.res][i].button.pressed()) {
				pilot_manage_button_pressed(i);
			}
		}
	
	// pilot that mouse is over

// if mouse is over a pilot, find index into Pilots array
	if (List_region.is_mouse_on()) {
		int y;
		List_region.get_mouse_pos(NULL, &y);
		int pilot_index = List_scroll_offset + (y / gr_get_font_height());
		if ((pilot_index >= 0) && (pilot_index < Num_pilots)) {
			prospective_pilot = pilot_index;
		}
	}
		
	// if mouse clicked in list region, find index into Pilots array 
	if (List_region.pressed()) {
		if (prospective_pilot != -1) {
			Selected_line = prospective_pilot;
			gamesnd_play_iface(SND_USER_SELECT);
		}
	}

	gr_reset_clip();	
	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0);	
	}
		
	Ui_window.draw();

	 //light up the correct mode button (single or multi)	
	if (Player_sel_mode == PLAYER_SELECT_MODE_SINGLE) {
		Buttons[gr_screen.res][PM_SINGLE_MODE_BUTTON].button.draw_forced(2);
	} else {
		Buttons[gr_screen.res][PM_MULTI_MODE_BUTTON].button.draw_forced(2);
	}	

	pilot_manage_display_pilot_callsigns(prospective_pilot);

	pilot_manage_force_button_frame();
	pilot_manage_maybe_show_button_text();

// needs to be fixed	help_overlay_maybe_blit(PILOT_MANAGE_OVERLAY);
	
	gr_flip();
}