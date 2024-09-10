void mht_do()
{	
	int k = Mht_window.process();

	// need to ensure ambient is playing, since it may be stopped by a playing movie
	main_hall_start_ambient();

	// process any keypresses
	switch(k){
	case KEY_ESC :		
		mht_exit_game();
		break;

	case KEY_B:
		gameseq_post_event( GS_EVENT_BARRACKS_MENU );
		break;	

	case KEY_G:
		if(Player->flags & PLAYER_FLAGS_IS_MULTI){
			break;
		}

		if (Num_recent_missions > 0)	{
			strcpy_s( Game_current_mission_filename, Recent_missions[0] );
		} else {
			mission_load_up_campaign();
			strcpy_s( Game_current_mission_filename, Campaign.missions[0].name );
		}

		Campaign.current_mission = -1;
		gameseq_post_event(GS_EVENT_START_GAME_QUICK);
		break;

	case KEY_L:
		gameseq_post_event( GS_EVENT_LOAD_MISSION_MENU );
		break;

	case KEY_F2:
		gameseq_post_event(GS_EVENT_OPTIONS_MENU);
		break;

	case KEY_M:
		if (Player->flags & PLAYER_FLAGS_IS_MULTI){
			main_hall_do_multi_ready();
		}
		break;
	}	

	// process button presses
	mht_check_buttons();

	// draw the background, etc
	gr_reset_clip();
	GR_MAYBE_CLEAR_RES(Mht_bitmap);
	if(Mht_bitmap != -1){		
		gr_set_bitmap(Mht_bitmap);
		gr_bitmap(0,0,GR_RESIZE_MENU);
	}
	Mht_window.draw();	
	
	// flip the buffer
	gr_flip();	
}