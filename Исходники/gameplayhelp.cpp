// gameplay_help_do_frame() is the function that displays help when acutally playing the game
void gameplay_help_do_frame(float frametime)
{
	int i, k;	

	// ensure the gameplay help interface has been initialized
	if (!Gameplay_help_inited) {
		Int3();
		return;
	}

	// make sure game sounds are paused
	weapon_pause_sounds();
	audiostream_pause_all();

	k = Ui_window.process() & ~KEY_DEBUGGED;
	gameplay_help_process_key(k);

	for (i=0; i<NUM_BUTTONS; i++){
		if (Buttons[gr_screen.res][i].button.pressed()){
			gameplay_help_button_pressed(i);
		}
	}
	
	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0, GR_RESIZE_MENU);
	}

	Ui_window.draw();

	gameplay_help_draw_text();
	gr_flip();
}