void cutscenes_screen_do_frame()
{
	int i, k, y, z;
	int font_height = gr_get_font_height();
	int select_tease_line = -1;

	k = Ui_window.process();
	switch (k) {
		case KEY_DOWN:  // select next line
			cutscenes_screen_scroll_line_down();
			break;

		case KEY_UP:  // select previous line
			cutscenes_screen_scroll_line_up();
			break;

		case KEY_TAB:
		case KEY_CTRLED | KEY_DOWN:
			cutscenes_screen_button_pressed(CREDITS_BUTTON);
			break;

		case KEY_SHIFTED | KEY_TAB:
		case KEY_CTRLED | KEY_UP:
			cutscenes_screen_button_pressed(SIMULATOR_BUTTON);
			break;

		case KEY_ENTER:
			cutscenes_screen_play();
			break;

		case KEY_ESC:  // cancel
			gameseq_post_event(GS_EVENT_MAIN_MENU);
			game_flush();
			break;

		case KEY_F1:  // show help overlay
			break;

		case KEY_F2:  // goto options screen
			gameseq_post_event(GS_EVENT_OPTIONS_MENU);
			break;

		// the "show-all" hotkey
		case KEY_CTRLED | KEY_SHIFTED | KEY_S:
		{
            Cutscene_list.clear();
			size_t size = Cutscenes.size();
			for (size_t t = 0; t < size; t++) {
                Cutscene_list.push_back((int)t);
			}

			break;
		}
	}	// end switch

	for (i=0; i<NUM_BUTTONS; i++){
		if (Buttons[gr_screen.res][i].button.pressed()){
			if (cutscenes_screen_button_pressed(i)){
				return;
			}
		}
	}

	if (List_region.button_down()) {
		List_region.get_mouse_pos(NULL, &y);
		z = Scroll_offset + y / font_height;
		if ((z >= 0) && (z < (int)Cutscene_list.size()))
			select_tease_line = z;
	}
	
	if (List_region.pressed()) {
		List_region.get_mouse_pos(NULL, &y);
		z = Scroll_offset + y / font_height;
		if ((z >= 0) && (z < (int)Cutscene_list.size()))
			Selected_line = z;
	}

	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0);
	} 

	Ui_window.draw();

	for (i=TECH_DATABASE_BUTTON; i<=CREDITS_BUTTON; i++){
		if (Buttons[gr_screen.res][i].button.button_down()){
			break;
		}
	}

	if (i > CREDITS_BUTTON){
		Buttons[gr_screen.res][CUTSCENES_BUTTON].button.draw_forced(2);
	}

	y = 0;
	z = Scroll_offset;
	while (y + font_height <= Cutscene_list_coords[gr_screen.res][3]) {
		if (z >= (int)Cutscene_list.size()){
			break;
		}

		if (z == Selected_line){
			gr_set_color_fast(&Color_text_selected);
		} else if (z == select_tease_line) {
			gr_set_color_fast(&Color_text_subselected);
		} else {
			gr_set_color_fast(&Color_text_normal);
		}

		gr_printf(Cutscene_list_coords[gr_screen.res][0], Cutscene_list_coords[gr_screen.res][1] + y, Cutscenes[Cutscene_list[z]].name);

		y += font_height;
		z++;
	}

	if (Description_index != Selected_line) {
		char *src = NULL;

		Description_index = Selected_line;
		Text_size = 0;
		if ( Description_index < (int)Cutscene_list.size( ) &&
			 (int)Cutscene_list[ Description_index ] < (int)Cutscenes.size( ) ) {
			src = Cutscenes[Cutscene_list[Description_index]].description;
			if (src) {
				Text_size = split_str(src, Cutscene_desc_coords[gr_screen.res][2], Text_line_size, Text_lines, Cutscene_max_text_lines[gr_screen.res]);
				Assert(Text_size >= 0 && Text_size < Cutscene_max_text_lines[gr_screen.res]);
			}
		}
	}

	if (Description_index >= 0) {
		int len;
		char line[MAX_TEXT_LINE_LEN + 1];

		gr_set_color_fast(&Color_text_normal);

		y = 0;
		z = Text_offset;
		while (y + font_height <= Cutscene_desc_coords[gr_screen.res][3]) {
			if (z >= Text_size || z >= MAX_TEXT_LINES-1)
				break;

			len = Text_line_size[z];
			if (len > MAX_TEXT_LINE_LEN)
				len = MAX_TEXT_LINE_LEN;

			strncpy(line, Text_lines[z], len);
			line[len] = 0;
			gr_string(Cutscene_desc_coords[gr_screen.res][0], Cutscene_desc_coords[gr_screen.res][1] + y, line);

			y += font_height;
			z++;
		}
	}

	gr_flip();
}