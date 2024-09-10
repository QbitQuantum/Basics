/* Retrieve pending events, and return the number of events */
static int getPendingEvents(void) {
	int count = 0;
	while (1) {
		Mouse mouse;
		Rune rune;
		int charCode, modifiers;
		int mouse_event = nbrecv(mousectl->c, (void*)&mouse);
		int resize_event = nbrecv(mousectl->resizec, NULL);
		int kbd_event = nbrecv(keyboardctl->c, (void*)&rune);
		
		if (mouse_event) {
			//Process mouse event
			mouse_position.x = mouse.xy.x - screen->r.min.x;
			mouse_position.y = mouse.xy.y - screen->r.min.y;
			mouse_button_state = mouse.buttons;
			qlock(&evt_buf_lock);
			if ((evts_end+2)%EVT_BUFFER_SIZE != evts_start) {
				sqMouseEvent* evt = (sqMouseEvent*)&evts[evts_end++];
				evts_end %= EVT_BUFFER_SIZE;
				evt->type = EventTypeMouse;
				evt->timeStamp = ioMSecs();
				evt->x = mouse_position.x;
				evt->y = mouse_position.y;
				evt->buttons = ioGetButtonState();
				evt->modifiers = 0;
				evt->reserved1 = evt->windowIndex = 0;
				count++;
			}
			qunlock(&evt_buf_lock);
		}

		if (resize_event) {
			getwindow(display, Refnone);
			fullDisplayUpdate();
		}

		if (kbd_event && splitRune(rune, &charCode, &modifiers)) {
			//Process keyboard event
			qlock(&evt_buf_lock);
			if ((evts_end+2)%EVT_BUFFER_SIZE != evts_start) {
				sqKeyboardEvent* evt = (sqKeyboardEvent*)&evts[evts_end++];
				evts_end %= EVT_BUFFER_SIZE;
				evt->type = EventTypeKeyboard;
				evt->timeStamp = ioMSecs();
				evt->pressCode = EventKeyChar;
				evt->charCode = charCode;
				evt->modifiers = modifiers;
				evt->reserved1 = evt->windowIndex = 0;
				count++;
			}
			qunlock(&evt_buf_lock);
		}
		if (!(resize_event || kbd_event || mouse_event))
			break;
	}
	return count;
}