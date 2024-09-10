// Called once per frame to run the dead popup
int popupdead_do_frame(float frametime)
{
	int k, choice;

	if ( !Popupdead_active ) {
		return -1;
	}

	// maybe show skip mission popup
	if ((!Popupdead_skip_already_shown) && (Player->show_skip_popup) && (Game_mode & GM_NORMAL) && (Game_mode & GM_CAMPAIGN_MODE) && (Player->failures_this_session >= PLAYER_MISSION_FAILURE_LIMIT)) {
		int popup_choice = popup(0, 3, XSTR("Do Not Skip This Mission", 1473),
												 XSTR("Advance To The Next Mission", 1474),
												 XSTR("Don't Show Me This Again", 1475),
												 XSTR("You have failed this mission five times.  If you like, you may advance to the next mission.", 1472) );
		switch (popup_choice) {
		case 0:
			// stay on this mission, so proceed to normal death popup
			// in other words, do nothing.
			break;
		case 1:
			// skip this mission
			Popupdead_active = 0;
			mission_campaign_skip_to_next();
			gameseq_post_event(GS_EVENT_START_GAME);
			return -1;
		case 2:
			// don't show this again
			Player->show_skip_popup = 0;
			break;
		}

		Popupdead_skip_already_shown = 1;
	}

	
	k = Popupdead_window.process();

	choice = popupdead_process_keys(k);
	if ( choice >= 0 ) {
		// do something different for single/multiplayer
		if ( Game_mode & GM_NORMAL ) {
			Popupdead_choice=choice;
		} else {
			Assert( Popupdead_multi_type != -1 );
			switch ( Popupdead_multi_type ) {
				
			case POPUPDEAD_OBS_ONLY:
			case POPUPDEAD_OBS_QUIT:
				Popupdead_choice = POPUPDEAD_DO_OBSERVER;
				if ( (Popupdead_multi_type == POPUPDEAD_OBS_QUIT) && (choice == 1) )
					Popupdead_choice = POPUPDEAD_DO_MAIN_HALL;
				break;

			case POPUPDEAD_RESPAWN_ONLY:
			case POPUPDEAD_RESPAWN_QUIT:
				Popupdead_choice = POPUPDEAD_DO_RESPAWN;
				if ( (Popupdead_multi_type == POPUPDEAD_RESPAWN_QUIT) && (choice == 1) )
					Popupdead_choice = POPUPDEAD_DO_MAIN_HALL;
				break;

			default:
				Int3();
				break;
			}
		}
	}

	choice = popupdead_check_buttons();
	if ( choice >= 0 ) {
		// do something different for single/multiplayer
		if ( Game_mode & GM_NORMAL ) {
			Popupdead_choice=choice;
		} else {
			Assert( Popupdead_multi_type != -1 );
			switch ( Popupdead_multi_type ) {
				
			case POPUPDEAD_OBS_ONLY:
			case POPUPDEAD_OBS_QUIT:
				Popupdead_choice = POPUPDEAD_DO_OBSERVER;
				if ( (Popupdead_multi_type == POPUPDEAD_OBS_QUIT) && (choice == 1) )
					Popupdead_choice = POPUPDEAD_DO_MAIN_HALL;
				break;

			case POPUPDEAD_RESPAWN_ONLY:
			case POPUPDEAD_RESPAWN_QUIT:
				Popupdead_choice = POPUPDEAD_DO_RESPAWN;
				if ( (Popupdead_multi_type == POPUPDEAD_RESPAWN_QUIT) && (choice == 1) )
					Popupdead_choice = POPUPDEAD_DO_MAIN_HALL;
				break;

			default:
				Int3();
				break;
			}
		}
	}

	Popupdead_window.draw();
	popupdead_force_draw_buttons();
	popupdead_draw_button_text();

	// maybe force the player to respawn if they've taken too long to choose
	if (( Game_mode & GM_MULTIPLAYER ) && (The_mission.max_respawn_delay >= 0) && (timestamp_elapsed(Popupdead_timer)) && (choice < 0)) {
		if (( Popupdead_multi_type == POPUPDEAD_RESPAWN_ONLY) || ( Popupdead_multi_type == POPUPDEAD_RESPAWN_QUIT)) {
			Popupdead_choice = POPUPDEAD_DO_RESPAWN; 
		}
	}

	return Popupdead_choice;
}