void techroom_do_frame(float frametime)
{
	
	int i, k;	

	// turn off controls when overlay is on
	if ( help_overlay_active(Techroom_overlay_id) ) {
		Buttons[gr_screen.res][HELP_BUTTON].button.reset_status();
		Ui_window.set_ignore_gadgets(1);
	}

	// turn off controls in trackball mode
	if (Trackball_active) {
		Ui_window.set_ignore_gadgets(1);
	} else {
		Ui_window.set_ignore_gadgets(0);
	}

	k = Ui_window.process() & ~KEY_DEBUGGED;

	if ( (k > 0) || B1_JUST_RELEASED ) {
		if ( help_overlay_active(Techroom_overlay_id) ) {
			help_overlay_set_state(Techroom_overlay_id, gr_screen.res, 0);
			Ui_window.set_ignore_gadgets(0);
			k = 0;
		}
	}

	if ( !help_overlay_active(Techroom_overlay_id) ) {
		Ui_window.set_ignore_gadgets(0);
	}

	switch (k) {
		case KEY_SHIFTED | KEY_TAB:  // activate previous tab
			i = Tab - 1;
			if (i < 0) {
				i = NUM_TABS - 1;
			}

			techroom_change_tab(i);
			break;

		case KEY_TAB:  // activate next tab
			i = Tab + 1;
			if (i >= NUM_TABS) {
				i = 0;
			}

			techroom_change_tab(i);
			break;

		case KEY_CTRLED | KEY_DOWN:
			if ( !(Player->flags & PLAYER_FLAGS_IS_MULTI) ) {
				techroom_button_pressed(SIMULATOR_TAB);
				break;
			}
			// fall through

		case KEY_CTRLED | KEY_UP:
			techroom_button_pressed(CREDITS_TAB);
			break;

		case KEY_CTRLED | KEY_ENTER:
		case KEY_ESC:
			gameseq_post_event(GS_EVENT_MAIN_MENU);
			break;

		case KEY_CTRLED | KEY_SHIFTED | KEY_S:
			Techroom_show_all = 1;
			techroom_lists_reset();
			techroom_change_tab(Tab);
			break;

	}	

	// check ship model window for activity
	if (View_window.pressed()) {
		Trackball_active = 1;
		Trackball_mode = 1;
	}
	if (B1_RELEASED) {
		Trackball_active = 0;
	}

	// check all da buttons
	for (i=0; i<NUM_BUTTONS; i++) {
		if (Buttons[gr_screen.res][i].button.pressed()) {
			if (techroom_button_pressed(i)) {
				return;
			}
		}
	}

	// check for mouseovers/clicks on the selection list
	Select_tease_line = -1;
	for (i=0; i<LIST_BUTTONS_MAX; i++) {
		if (List_buttons[i].is_mouse_on()) {
			Select_tease_line = i + List_offset;
		}
	
		if (List_buttons[i].pressed()) {
			Cur_entry = i + List_offset;
			gamesnd_play_iface(SND_USER_SELECT);
			techroom_select_new_entry();
		}
	}

	// clear & draw bg bitmap
	GR_MAYBE_CLEAR_RES(Tech_background_bitmap);
	if (Tech_background_bitmap >= 0) {
		gr_set_bitmap(Tech_background_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	}

	// render
	switch (Tab) {
		case SHIPS_DATA_TAB:
			techroom_ships_render(frametime);
			break;

		case WEAPONS_DATA_TAB:
		case INTEL_DATA_TAB:
			techroom_anim_render(frametime);
			break;
	}

	Ui_window.draw();

	for (i=TECH_DATABASE_TAB; i<=CREDITS_TAB; i++) {
		if (Buttons[gr_screen.res][i].button.button_down()) {
			break;
		}
	}
	if (i > CREDITS_TAB) {
		Buttons[gr_screen.res][TECH_DATABASE_TAB].button.draw_forced(2);
	}

	for (i=0; i<NUM_TABS; i++){
		if (Buttons[gr_screen.res][i].button.button_down()){
			break;
		}
	}
	if (i == NUM_TABS){
		Buttons[gr_screen.res][Tab].button.draw_forced(2);
	}

	// blit help overlay if active
	help_overlay_maybe_blit(Techroom_overlay_id, gr_screen.res);

	gr_flip();
}