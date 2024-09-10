void unregister_running_hooks() {
	// Stop the event hook and any timer still running.
	if (win_event_hhook != NULL) {
		UnhookWinEvent(win_event_hhook);
		win_event_hhook = NULL;
	}

	// Destroy the native hooks.
	if (keyboard_event_hhook != NULL) {
		UnhookWindowsHookEx(keyboard_event_hhook);
		keyboard_event_hhook = NULL;
	}

	if (mouse_event_hhook != NULL) {
		UnhookWindowsHookEx(mouse_event_hhook);
		mouse_event_hhook = NULL;
	}
}