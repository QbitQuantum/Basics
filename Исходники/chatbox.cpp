// process this frame for the chatbox
int chatbox_process(int key_in)
{	
	int key_out;

	key_out = key_in;

	// if the chatbox hasn't explicitly been created, we can't do any processing
	if(!Chatbox_created){
		return key_out;
	}

	// process the incoming key appropriately
	if (key_in == -1) {
		key_out = Chat_window.process();
	} else {
		key_out = Chat_window.process(key_in);
	}

	// look for special keypresses
	switch(key_out){
	// line recall up one
	case KEY_UP:
		chatbox_recall_up();
		key_out = 0;
		break;
	
	// line recall down one
	case KEY_DOWN:
		chatbox_recall_down();
		key_out = 0;
		break;
	}

	// if we're supposed to be checking our own scroll buttons
	if((Chatbox_mode_flags & CHATBOX_FLAG_BUTTONS) && (Chatbox_mode_flags & CHATBOX_FLAG_DRAW_BOX)){
		if ( Chatbox_buttons[gr_screen.res][CHATBOX_SCROLL_UP].button.pressed() ) {
			chatbox_scroll_up();
		}

		if ( Chatbox_buttons[gr_screen.res][CHATBOX_SCROLL_DOWN].button.pressed() ) {
			chatbox_scroll_down();
		}

		if ( Chatbox_buttons[gr_screen.res][CHATBOX_TOGGLE_SIZE].button.pressed() ){
			chatbox_toggle_size();
		}
	}

	// check to see if the enter text button has been pressed
	if ( Chat_enter_text.pressed() ) {
		Chat_inputbox.set_focus();
	}

	// check to see if the current input text needs to be split up and sent automaticall
	chatbox_autosplit_line();	

	return key_out;
}