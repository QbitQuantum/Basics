// pause do frame - will handle running multiplayer operations if necessary
void pause_do()
{
	int k;
	const char *pause_str = XSTR("Paused", 767);
	int str_w, str_h;
	// next two are for view resetting
	static int previous_Viewer_mode = -1;
	static int previous_hud_state = -1;

	Assert( !(Game_mode & GM_MULTIPLAYER) );
	
	//	RENDER A GAME FRAME HERE AS THE BACKGROUND (if normal pause)

	if(Pause_type == PAUSE_TYPE_NORMAL)	{			
		// Fall back to viewer just incase saved screen is invalid
		if(Pause_saved_screen == -1){
			Pause_type = PAUSE_TYPE_VIEWER;
		}
		else if(Pause_type == PAUSE_TYPE_NORMAL)	{
			gr_restore_screen(Pause_saved_screen);
		}
	}

	if(Pause_type == PAUSE_TYPE_NORMAL){
		if (Pause_background_bitmap >= 0) {
			gr_set_bitmap(Pause_background_bitmap);

			// draw the bitmap
			gr_bitmap(Please_wait_coords[gr_screen.res][0], Please_wait_coords[gr_screen.res][1], GR_RESIZE_MENU);
			
			// draw "Paused" on it
			gr_set_color_fast(&Color_normal);
			gr_set_font(FONT2);
			gr_get_string_size(&str_w, &str_h, pause_str);
			gr_string((gr_screen.max_w_unscaled - str_w) / 2, (gr_screen.max_h_unscaled - str_h) / 2, pause_str, GR_RESIZE_MENU);
			gr_set_font(FONT1);
		}
	}

	if (Pause_type == PAUSE_TYPE_VIEWER) {
		if (previous_Viewer_mode < 0)
			previous_Viewer_mode = Viewer_mode;

		if (previous_hud_state < 0)
			previous_hud_state = hud_disabled();
	}

	// process the ui window here
	k = Pause_win.process() & ~KEY_DEBUGGED;
	switch (k)
	{ 
		case KEY_TAB:
			hud_toggle_draw();
			break;

		// view from outside of the ship
	   	case KEY_ENTER:
			if (Pause_type == PAUSE_TYPE_VIEWER) {
				button_function_demo_valid(VIEW_EXTERNAL);
			}
			break;

		// view from target
		case KEY_PADDIVIDE:
			if (Pause_type == PAUSE_TYPE_VIEWER) {
				button_function_demo_valid(VIEW_OTHER_SHIP);
			}
			break;

		// change target
		case KEY_PADMULTIPLY:
			if (Pause_type == PAUSE_TYPE_VIEWER) {
				button_function(TARGET_NEXT);
			}
			break;

		case KEY_ESC:
		case KEY_ALTED + KEY_PAUSE:
		case KEY_PAUSE:
			// reset previous view if we happened to be playing around with it during pause
			if (Pause_type == PAUSE_TYPE_VIEWER) {
				if (previous_Viewer_mode >= 0) {
					Viewer_mode = previous_Viewer_mode;
				}

				// NOTE remember that hud state is reversed here (0 == on, 1 == off)
				if ( (previous_hud_state >= 0) && (hud_disabled() != previous_hud_state) ) {
					hud_set_draw( !previous_hud_state );
				}
			}

			gameseq_post_event(GS_EVENT_PREVIOUS_STATE);		
			break;
	}	// end switch

	// draw the background window
	Pause_win.draw();

	// a very unique case where we shouldn't be doing the page flip because we're inside of popup code
	if(!popup_active()){
		if(Pause_type == PAUSE_TYPE_NORMAL) {
			gr_flip();
		}
	} else {
		// this should only be happening in a very unique multiplayer case
		Int3();
	}
}