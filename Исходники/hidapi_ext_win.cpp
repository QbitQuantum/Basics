int hid_event_read_cancellable(hid_event_monitor* monitor, hid_event* event, hid_cancel_token* cancel_token) {
	auto current_thread_id = GetCurrentThreadId();
	auto monitor_thread_id = GetWindowThreadProcessId(monitor->hwnd, NULL);

	if (current_thread_id != monitor_thread_id) {
		printf("hid_event_read_cancellable failed, monitor have to be created" \
			   " in the same thread which is calling this function.");

		return -1;
	}

	DWORD res = 0;

	DWORD handle_count = 0;
	HANDLE handle = NULL;

	if (cancel_token) {
		handle_count = 1;
		handle = cancel_token->event_handle;
	}

	while (true) {
		//will wait for cancel event and events send/posted to this thread
		res = MsgWaitForMultipleObjects(handle_count, &handle, FALSE, INFINITE, QS_ALLINPUT);

		if (cancel_token && res == WAIT_OBJECT_0) {
			return READ_CANCELLED;
		}

		if (res != WAIT_OBJECT_0 + handle_count) {
			if (res == WAIT_FAILED) {
				DWORD last_error = GetLastError();
				printf("hid_event_read_cancellable failed, WAIT_FAILED, last error: %ul", last_error);
				return -1;
			}

			//some other error with no last error set
			return -1;
		}

		MSG msg;
		//PeekMesssage will call WindowProc where monitor->event struct is set
		//Because device messages are send not posted to queue, PeekMessage
		// will return as if there wasn't any messages, so msg struct & return
		// value is useless
		PeekMessage(&msg, monitor->hwnd, 0, 0, PM_REMOVE);

		//There might be messages other than what we want, if message was what we
		// wanted we set proc_real_event to true in WindowProc, else false
		if (monitor->proc_real_event) {
			//monitors event is reused on every WindowProc so we have to copy all of its contents
			event->action = monitor->proc_event.action;
			event->device_info->path = monitor->proc_event.device_info->path;

			if (event->action == EVENT_ADD) {
				parse_info_from_path(event, monitor->proc_event.device_info->path);
			}

			//we don't free string allocated in WindowProc here, its now part
			// of event and therefore caller of this function has the
			// responsibility of freeing event & its stuff (path)
			monitor->proc_event.device_info->path = NULL;

			monitor->proc_real_event = false;
			break;
		}
	}

	return 0;
}