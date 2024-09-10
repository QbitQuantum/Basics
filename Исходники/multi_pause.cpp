void multi_pause_do()
{
	int k;
	
	// make sure we don't enter this state unless we're in the mission itself	
	Netgame.game_state = NETGAME_STATE_PAUSED;

	// server of the game should periodically be sending pause packets for good measure
	if (Net_player->flags & NETINFO_FLAG_AM_MASTER) {		
	}

	if (!(Game_mode & GM_STANDALONE_SERVER)) {
		// restore saved screen data if any
		if (Multi_paused_screen_id >= 0) {
			gr_restore_screen(Multi_paused_screen_id);
		}

		// set the background image
		if (Multi_paused_background >= 0) {
			gr_set_bitmap(Multi_paused_background);
			gr_bitmap(0, 0, GR_RESIZE_MENU);
		}

		// if we're inside of popup code right now, don't process the window
		if(!popup_active()){
			// process chatbox and window stuff
			k = chatbox_process();
			k = Multi_paused_window.process(k);	
		
			switch (k) {
			case KEY_ESC:			
			case KEY_PAUSE:									
				multi_pause_request(0);
				break;
			}
		}

		// check for any button presses
		multi_pause_check_buttons();

		// render the callsign of the guy who paused
		multi_pause_render_callsign();
				
		// render the chatbox
		chatbox_render();
		
		// draw tooltips
		// Multi_paused_window.draw_tooltip();
		Multi_paused_window.draw();

		// display the voice status indicator
		multi_common_voice_display_status();

		// don't flip screen if we are in the popup code right now
		if (!popup_active()) {
			gr_flip();
		}
	}
	// standalone pretty much does nothing here
	else {
		os_sleep(1);
	}
}