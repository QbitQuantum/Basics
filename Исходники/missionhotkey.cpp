// ---------------------------------------------------------------------
// mission_hotkey_do_frame()
//
// Called once per frame to process user input for the Hotkey Assignment Screen
//
void mission_hotkey_do_frame(float frametime)
{
	char buf[256];
	int i, k, w, h, y, z, line, hotkeys;
	int font_height = gr_get_font_height();
	int select_tease_line = -1;  // line mouse is down on, but won't be selected until button released
	color circle_color;

	if ( help_overlay_active(Hotkey_overlay_id) ) {
		Buttons[gr_screen.res][HELP_BUTTON].button.reset_status();
		Ui_window.set_ignore_gadgets(1);
	}

	k = Ui_window.process() & ~KEY_DEBUGGED;

	if ( (k > 0) || B1_JUST_RELEASED ) {
		if ( help_overlay_active(Hotkey_overlay_id) ) {
			help_overlay_set_state(Hotkey_overlay_id, gr_screen.res, 0);
			Ui_window.set_ignore_gadgets(0);
			k = 0;
		}
	}

	if ( !help_overlay_active(Hotkey_overlay_id) ) {
		Ui_window.set_ignore_gadgets(0);
	}

	switch (k) {
		case KEY_DOWN:  // scroll list down
			hotkey_scroll_line_down();
			break;

		case KEY_UP:  // scroll list up
			hotkey_scroll_line_up();
			break;

		case KEY_PAGEDOWN:  // scroll list down
			hotkey_scroll_screen_down();
			break;

		case KEY_PAGEUP:  // scroll list up
			hotkey_scroll_screen_up();
			break;

		case KEY_CTRLED | KEY_ENTER:
			save_hotkeys();
			// fall through to next state -- allender changed this behavior since ESC should always cancel, no?

		case KEY_ESC:			
			mission_hotkey_exit();
			break;

		case KEY_TAB:
		case KEY_ENTER:
		case KEY_PADENTER:
			expand_wing();
			break;

		case KEY_EQUAL:
		case KEY_PADPLUS:
			add_hotkey(Cur_hotkey);
			break;

		case KEY_MINUS:
		case KEY_PADMINUS:
			remove_hotkey();
			break;

		case KEY_F2:			
			gameseq_post_event(GS_EVENT_OPTIONS_MENU);			
			break;

		case KEY_CTRLED | KEY_R:
			reset_hotkeys();
			break;

		case KEY_CTRLED | KEY_C:
			clear_hotkeys();
			break;
	}	// end switch

	// ?
	for (i=0; i<MAX_KEYED_TARGETS; i++) {
		if (k == Key_sets[i])
			Cur_hotkey = i;

		if (k == (Key_sets[i] | KEY_SHIFTED))
			add_hotkey(i);
	}

	// handle pressed buttons
	for (i=0; i<NUM_BUTTONS; i++) {
		if (Buttons[gr_screen.res][i].button.pressed()) {
			hotkey_button_pressed(i);
			break;					// only need to handle 1 button @ a time
		}
	}

	for (i=0; i<LIST_BUTTONS_MAX; i++) {
		// check for tease line
		if (List_buttons[i].button_down()) {
			select_tease_line = i + Scroll_offset;
		}
	
		// check for selected list item
		if (List_buttons[i].pressed()) {
			Selected_line = i + Scroll_offset;
			List_buttons[i].get_mouse_pos(&z, NULL);
			z += Hotkey_list_coords[gr_screen.res][0];		// adjust to full screen space
			if ((z >= Hotkey_wing_icon_x[gr_screen.res]) && (z < (Hotkey_wing_icon_x[gr_screen.res]) + Hotkey_function_field_width[gr_screen.res])) {
				expand_wing();
			}
		}

		if (List_buttons[i].double_clicked()) {
			Selected_line = i + Scroll_offset;
			hotkeys = -1;
			switch (Hotkey_lines[Selected_line].type) {
				case HOTKEY_LINE_WING:
					hotkeys = get_wing_hotkeys(Hotkey_lines[Selected_line].index);
					break;

				case HOTKEY_LINE_SHIP:
				case HOTKEY_LINE_SUBSHIP:
					hotkeys = Hotkey_bits[Hotkey_lines[Selected_line].index];
					break;
			}

			if (hotkeys != -1) {
				if (hotkeys & (1 << Cur_hotkey))
					remove_hotkey();
				else
					add_hotkey(Cur_hotkey);
			}
		}
	}

	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);

	} else
		gr_clear();

	Ui_window.draw();
	gr_init_color(&circle_color, 160, 160, 0);

	// draw the big "F10" in the little box	
	font::set_font(font::FONT2);
	gr_set_color_fast(&Color_text_normal);
	strcpy_s(buf, Scan_code_text[Key_sets[Cur_hotkey]]);
	gr_get_string_size(&w, &h, buf);
	gr_printf_menu(Hotkey_function_name_coords[gr_screen.res][0] + (Hotkey_function_name_coords[gr_screen.res][2] - w) / 2, Hotkey_function_name_coords[gr_screen.res][1], buf);

	font::set_font(font::FONT1);
	line = Scroll_offset;
	while (hotkey_line_query_visible(line)) {
		z = Hotkey_lines[line].index;
		y = Hotkey_list_coords[gr_screen.res][1] + Hotkey_lines[line].y - Hotkey_lines[Scroll_offset].y;
		hotkeys = 0;
		switch (Hotkey_lines[line].type) {
			case HOTKEY_LINE_HEADING:
				gr_set_color_fast(&Color_text_heading);

				gr_get_string_size(&w, &h, Hotkey_lines[line].label);
				i = y + h / 2 - 1;
				gr_line(Hotkey_list_coords[gr_screen.res][0], i, Hotkey_ship_x[gr_screen.res] - 2, i, GR_RESIZE_MENU);
				gr_line(Hotkey_ship_x[gr_screen.res] + w + 1, i, Hotkey_list_coords[gr_screen.res][0] + Hotkey_list_coords[gr_screen.res][2], i, GR_RESIZE_MENU);
				break;

			case HOTKEY_LINE_WING:
				gr_set_bitmap(Wing_bmp);
				bm_get_info(Wing_bmp, NULL, &h, NULL);
				i = y + font_height / 2 - h / 2 - 1;
				gr_bitmap(Hotkey_wing_icon_x[gr_screen.res], i, GR_RESIZE_MENU);

//				i = y + font_height / 2 - 1;
//				gr_set_color_fast(&circle_color);
//				gr_circle(ICON_LIST_X + 4, i, 5, GR_RESIZE_MENU);

//				gr_set_color_fast(&Color_bright);
//				gr_line(ICON_LIST_X, i, ICON_LIST_X + 2, i, GR_RESIZE_MENU);
//				gr_line(ICON_LIST_X + 4, i - 4, ICON_LIST_X + 4, i - 2, GR_RESIZE_MENU);
//				gr_line(ICON_LIST_X + 6, i, ICON_LIST_X + 8, i, GR_RESIZE_MENU);
//				gr_line(ICON_LIST_X + 4, i + 2, ICON_LIST_X + 4, i + 4, GR_RESIZE_MENU);

				hotkeys = get_wing_hotkeys(Hotkey_lines[line].index);
				break;

			case HOTKEY_LINE_SHIP:
			case HOTKEY_LINE_SUBSHIP:
				hotkeys = Hotkey_bits[Hotkey_lines[line].index];
				break;

			default:
				Int3();
		}

		if (Hotkey_lines[line].type != HOTKEY_LINE_HEADING) {
			Assert( (line - Scroll_offset) < LIST_BUTTONS_MAX );
			List_buttons[line - Scroll_offset].update_dimensions(Hotkey_list_coords[gr_screen.res][0], y, Hotkey_list_coords[gr_screen.res][0] + Hotkey_list_coords[gr_screen.res][2] - Hotkey_list_coords[gr_screen.res][0], font_height);
			List_buttons[line - Scroll_offset].enable();
			if (hotkeys & (1 << Cur_hotkey)) {
				gr_set_color_fast(&Color_text_active);

			} else {
				if (line == Selected_line)
					gr_set_color_fast(&Color_text_selected);
				else if (line == select_tease_line)
					gr_set_color_fast(&Color_text_subselected);
				else
					gr_set_color_fast(&Color_text_normal);
			}

		} else {
			Assert( (line - Scroll_offset) < LIST_BUTTONS_MAX );
			List_buttons[line - Scroll_offset].disable();
		}

		// print active hotkeys associated for this line
		if (hotkeys) {
			for (i=0; i<MAX_KEYED_TARGETS; i++) {
				if (hotkeys & (1 << i)) {
					gr_printf_menu(Hotkey_list_coords[gr_screen.res][0] + Hotkey_function_field_width[gr_screen.res]*i, y, Scan_code_text[Key_sets[i]]);
				}
			}
/*
			*buf = 0;
			for (i=0; i<MAX_KEYED_TARGETS; i++) {
				if (hotkeys & (1 << i)) {
					strcat_s(buf, Scan_code_text[Key_sets[i]]);
					strcat_s(buf, ", ");
				}
			}

			Assert(strlen(buf) > 1);
			buf[strlen(buf) - 2] = 0;  // lose the ", " on the end

			font::force_fit_string(buf, 255, GROUP_LIST_W);
			gr_printf_menu(GROUP_LIST_X, y, buf);*/
		}
	
		// draw ship/wing name
		strcpy_s(buf, Hotkey_lines[line].label);
		end_string_at_first_hash_symbol(buf);
		if (Hotkey_lines[line].type == HOTKEY_LINE_SUBSHIP) {
			// indent
			font::force_fit_string(buf, 255, Hotkey_list_coords[gr_screen.res][0] + Hotkey_list_coords[gr_screen.res][2] - (Hotkey_ship_x[gr_screen.res]+20));
			gr_printf_menu(Hotkey_ship_x[gr_screen.res]+20, y, buf);
		} else {
			font::force_fit_string(buf, 255, Hotkey_list_coords[gr_screen.res][0] + Hotkey_list_coords[gr_screen.res][2] - Hotkey_ship_x[gr_screen.res]);
			gr_printf_menu(Hotkey_ship_x[gr_screen.res], y, buf);
		}

		line++;
	}

	i = line - Scroll_offset;
	while (i < LIST_BUTTONS_MAX)
		List_buttons[i++].disable();

	// blit help overlay if active
	help_overlay_maybe_blit(Hotkey_overlay_id, gr_screen.res);

	gr_flip();
}