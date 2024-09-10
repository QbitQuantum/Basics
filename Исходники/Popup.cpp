// exit: -1						=>	error
//			0..nchoices-1		=> choice
int popup_do(popup_info *pi, int flags)
{
	int screen_id, choice = -1, done = 0;

	if ( popup_init(pi, flags) == -1 ){
		return -1;
	}

	screen_id = gr_save_screen();

	int old_max_w_unscaled = gr_screen.max_w_unscaled;
	int old_max_h_unscaled = gr_screen.max_h_unscaled;
	int old_max_w_unscaled_zoomed = gr_screen.max_w_unscaled_zoomed;
	int old_max_h_unscaled_zoomed = gr_screen.max_h_unscaled_zoomed;

	gr_reset_screen_scale();

	while(!done) {
		int k;

		os_poll();

		// if we were killed by a call to popup_kill_any_active(), kill the popup
		if(Popup_should_die){
			choice = -1;
			break;
		}

		// if we're flagged as should be running the state underneath, then do so
		if(flags & PF_RUN_STATE){
			game_do_state(gameseq_get_state());
		}
		// otherwise just run the common functions (for networking,etc)
		else {
			game_set_frametime(-1);
			game_do_state_common(gameseq_get_state(),flags & PF_NO_NETWORKING);	// do stuff common to all states 
		}

		k = Popup_window.process();						// poll for input, handle mouse
		choice = popup_process_keys(pi, k, flags);
		if ( choice != POPUP_NOCHANGE ) {
			done=1;
		}

		if ( !done ) {
			choice = popup_check_buttons(pi);
			if ( choice != POPUP_NOCHANGE ) {
				done=1;
			}
		}

		// don't draw anything 
		if(!(flags & PF_RUN_STATE)){
			gr_restore_screen(screen_id);
		}

		// if this is an input popup, store the input text
		if(flags & PF_INPUT){
			Popup_input.get_text(pi->input_text);
		}

		Popup_window.draw();
		popup_force_draw_buttons(pi);
		popup_draw_msg_text(pi, flags);
		popup_draw_button_text(pi, flags);
		gr_flip();
	}

	gr_set_screen_scale(old_max_w_unscaled, old_max_h_unscaled, old_max_w_unscaled_zoomed, old_max_h_unscaled_zoomed);

	popup_close(pi,screen_id);
	return choice;
}