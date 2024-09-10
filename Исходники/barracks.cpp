// -----------------------------------------------------------------------------
void barracks_do_frame(float frametime)
{
	int k = Ui_window.process();

	if ( k > 0 ) {
		if ( help_overlay_active(Barracks_overlay_id) ) {
			help_overlay_set_state(Barracks_overlay_id,gr_screen.res,0);
			k = 0;
		}
	}

	// pilot that mouse is over
	int prospective_pilot = -1;
	int i;

	// Entering pilot callsign
	if (Barracks_callsign_enter_mode) {
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

				barracks_set_callsign_enter_mode(false);
				break;

			case KEY_ENTER: 
				barracks_accept_new_pilot_callsign();
				break;
		} 
	} else {
		// not entering pilot callsign
		switch (k) {
			case KEY_ENTER:
				if (barracks_new_pilot_selected()) {
					gamesnd_play_iface(SND_GENERAL_FAIL);
				} else {
					gamesnd_play_iface(SND_USER_SELECT);
				}
				break;

			case KEY_ESC:  // cancel
				if (!help_overlay_active(Barracks_overlay_id)) {
					if (Num_pilots && !barracks_pilot_accepted()) {
						gameseq_post_event(GS_EVENT_MAIN_MENU);
					} else {
						gamesnd_play_iface(SND_GENERAL_FAIL);
					}
				} else {
					// kill the overlay
					help_overlay_set_state(Barracks_overlay_id,gr_screen.res,0);
				}
				break;

			case KEY_TAB:  // switch mode (simgle/multi)
				if ( Networking_disabled ) {
					game_feature_disabled_popup();
					break;
				}

				if (Player_sel_mode == PLAYER_SELECT_MODE_SINGLE) {
					Cur_pilot->flags |= PLAYER_FLAGS_IS_MULTI;
					Pilot.save_player(Cur_pilot);
					barracks_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
				} else {
					// make sure we don't carry over the multi flag
					Cur_pilot->flags &= ~PLAYER_FLAGS_IS_MULTI;
					Pilot.save_player(Cur_pilot);
					barracks_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
				}

				gamesnd_play_iface(SND_USER_SELECT);
				break;

			case KEY_F1:  // show help overlay
				gamesnd_play_iface(SND_HELP_PRESSED);
				break;

			case KEY_F2:  // goto options screen
				gamesnd_play_iface(SND_SWITCH_SCREENS);
				gameseq_post_event(GS_EVENT_OPTIONS_MENU);
				break;
		}	// end switch

		// process buttons
		for (i=0; i<BARRACKS_NUM_BUTTONS; i++) {
			if (Buttons[gr_screen.res][i].button.pressed()) {
				barracks_button_pressed(i);
			}
		}

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
	}

	// check mouse over help
	if (mouse_down(MOUSE_LEFT_BUTTON)) {
		help_overlay_set_state(Barracks_overlay_id, gr_screen.res, 0);
	}

	// do pilot pic stuff
	if ((Pic_number >= 0) && (Pic_number < Num_pilot_images)) {
		if (Pilot_images[Pic_number] == BARRACKS_IMAGE_NOT_LOADED) {  // haven't tried loading it yet
			Pilot_images[Pic_number] = bm_load(Pilot_image_names[Pic_number]);
			if (Pilot_images[Pic_number] >= 0) {
				int w, h;

				bm_get_info(Pilot_images[Pic_number], &w, &h, NULL);
				// check for invalid pilot pic file
				if ((w != PLAYER_PILOT_PIC_W) || (h != PLAYER_PILOT_PIC_H)) {
					bm_release(Pilot_images[Pic_number]);
					Pilot_images[Pic_number] = -1;
				}
			}
		}		
	} else {
		Pic_number = -1;
	}

	// do squad pic stuff
	if ((Pic_squad_number >= 0) && (Pic_squad_number < Num_pilot_squad_images)) {
		if (Pilot_squad_images[Pic_squad_number] == BARRACKS_IMAGE_NOT_LOADED) {  // haven't tried loading it yet
			Pilot_squad_images[Pic_squad_number] = bm_load_duplicate(Pilot_squad_image_names[Pic_squad_number]);
			if (Pilot_squad_images[Pic_squad_number] >= 0) {
				int w, h;

				bm_get_info(Pilot_squad_images[Pic_squad_number], &w, &h, NULL);
				// check for invalid pilot pic file
				if ((w != PLAYER_SQUAD_PIC_W) || (h != PLAYER_SQUAD_PIC_H)) {
					bm_release(Pilot_squad_images[Pic_squad_number]);
					Pilot_squad_images[Pic_squad_number] = -1;
				}
			}
		}
	} else {
		Pic_squad_number = -1;
	}

	// draw the background, etc
	gr_reset_clip();	
	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);	
	}		

	// draw pilot image and clean up afterwards
	barracks_draw_pilot_pic();
	barracks_draw_squad_pic();

	// draw the window	
	Ui_window.draw();	

	// light up the correct mode button (single or multi)	
	if (Player_sel_mode == PLAYER_SELECT_MODE_SINGLE) {
		Buttons[gr_screen.res][B_PILOT_SINGLE_MODE_BUTTON].button.draw_forced(2);
	} else {
		Buttons[gr_screen.res][B_PILOT_MULTI_MODE_BUTTON].button.draw_forced(2);
	}	

	// write out pilot call signs
	barracks_display_pilot_callsigns(prospective_pilot);

	// write out current pilot stats
	barracks_display_pilot_stats();

	// blit help overlay if active
	help_overlay_maybe_blit(Barracks_overlay_id, gr_screen.res);
	
	// flip the page
	gr_flip();
}