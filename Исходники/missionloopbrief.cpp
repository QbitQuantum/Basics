// do
void loop_brief_do(float frametime)
{
	int k;
	int idx;

	// process keys
	k = Loop_brief_window.process();	

	switch (k) {
	case KEY_ESC:
		int do_loop = 0;

		// this popup should be straight forward, and also not allow you to get out
		// of it without actually picking one of the two options
		do_loop = popup(PF_USE_NEGATIVE_ICON | PF_USE_AFFIRMATIVE_ICON | PF_IGNORE_ESC | PF_BODY_BIG, 2, XSTR("Decline", 1467), XSTR("Accept", 1035), XSTR("You must either Accept or Decline before returning to the Main Hall", 1618));

		// if we accepted moving into loop then set it up for the next time the user plays
		if (do_loop == 1) {
			// select the loop mission		
			Campaign.loop_enabled = 1;
			Campaign.loop_reentry = Campaign.next_mission;			// save reentry pt, so we can break out of loop
			Campaign.next_mission = Campaign.loop_mission;
		}

		gameseq_post_event(GS_EVENT_MAIN_MENU);
		return;
	}

	// process button presses
	for (idx=0; idx<NUM_LOOP_BRIEF_BUTTONS; idx++){
		if (Loop_buttons[gr_screen.res][idx].button.pressed()){
			loop_brief_button_pressed(idx);
		}
	}
	
	common_music_do();

	// clear
	GR_MAYBE_CLEAR_RES(Loop_brief_bitmap);
	if (Loop_brief_bitmap >= 0) {
		gr_set_bitmap(Loop_brief_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	} 
	
	// draw the window
	Loop_brief_window.draw();		

	// render the briefing text
	brief_render_text(0, Loop_brief_text_coords[gr_screen.res][0], Loop_brief_text_coords[gr_screen.res][1], Loop_brief_text_coords[gr_screen.res][3], flFrametime);

	if(Loop_anim.num_frames > 0) {
		int x;
		int y;

		bm_get_info((Loop_anim.streaming) ? Loop_anim.bitmap_id : Loop_anim.first_frame, &x, &y, NULL, NULL, NULL);
		x = Loop_brief_anim_center_coords[gr_screen.res][0] - x / 2;
		y = Loop_brief_anim_center_coords[gr_screen.res][1] - y / 2;
		generic_anim_render(&Loop_anim, frametime, x, y, true);
	}

	// render all anims
	anim_render_all(GS_STATE_LOOP_BRIEF, flFrametime);

	gr_flip();
}