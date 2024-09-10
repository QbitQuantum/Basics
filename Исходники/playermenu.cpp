void player_select_do()
{
	int k;

	// Goober5000 - display a popup warning about problems in the mod
	if ((Global_warning_count > 10 || Global_error_count > 0) && !Startup_warning_dialog_displayed) {
		char text[512];
		sprintf(text, "Warning!\n\nThe currently active mod has generated %d warnings and/or errors during program startup.  These could have been caused by anything from incorrectly formated table files to corrupt models.  While FreeSpace Open will attempt to compensate for these issues, it cannot guarantee a trouble-free gameplay experience.  Source Code Project staff cannot provide assistance or support for these problems, as they are caused by the mod's data files, not FreeSpace Open's source code.", Global_warning_count + Global_error_count);
		popup(PF_TITLE_BIG | PF_TITLE_RED | PF_USE_AFFIRMATIVE_ICON, 1, POPUP_OK, text);
		Startup_warning_dialog_displayed = true;
	}
		
	// set the input box at the "virtual" line 0 to be active so the player can enter a callsign
	if (Player_select_input_mode) {
		Player_select_input_box.set_focus();
	}

	// process any ui window stuff
	k = Player_select_window.process();

	if (k) {
		extern void game_process_cheats(int k);
		game_process_cheats(k);
	}

	switch (k) {
		// switch between single and multiplayer modes
		case KEY_TAB: {
			if (Player_select_input_mode) {
				gamesnd_play_iface(SND_GENERAL_FAIL);
				break;
			}

			// play a little sound
			gamesnd_play_iface(SND_USER_SELECT);

			if (Player_select_mode == PLAYER_SELECT_MODE_MULTI) {
				player_select_set_bottom_text(XSTR( "Single-Player Mode", 376));

				// reinitialize as single player mode
				player_select_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
			} else if (Player_select_mode == PLAYER_SELECT_MODE_SINGLE) {
				player_select_set_bottom_text(XSTR( "Multiplayer Mode", 377));

				// reinitialize as multiplayer mode
				player_select_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
			}

			break;
		}

		case KEY_ESC: {
			// we can hit ESC to get out of text input mode, and we don't want
			// to set this var in that case since it will crash on a NULL Player
			// ptr when going to the mainhall
			if ( !Player_select_input_mode ) {
				Player_select_no_save_pilot = 1;
			}

			break;
		}
	}

	// draw the player select pseudo-dialog over it
	GR_MAYBE_CLEAR_RES(Player_select_background_bitmap);
	gr_set_bitmap(Player_select_background_bitmap);
	gr_bitmap(0,0,GR_RESIZE_MENU);

	// press the accept button
	if (Player_select_autoaccept) {
		Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].button.press_button();
	}
	
	// draw any ui window stuf
	Player_select_window.draw();

	// light up the correct mode button (single or multi)
	if (Player_select_mode == PLAYER_SELECT_MODE_SINGLE) {
		Player_select_buttons[gr_screen.res][SINGLE_BUTTON].button.draw_forced(2);
	} else {
		Player_select_buttons[gr_screen.res][MULTI_BUTTON].button.draw_forced(2);
	}

	// draw the pilot list text
	player_select_draw_list();

	// draw copyright message on the bottom on the screen
	player_select_display_copyright();

	if (!Player_select_input_mode) {
		player_select_process_noninput(k);
	} else {
		player_select_process_input(k);
	}
	
	// draw any pending messages on the bottom or middle of the screen
	player_select_display_all_text();

	gr_flip();
}