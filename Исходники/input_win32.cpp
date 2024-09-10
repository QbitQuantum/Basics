	void poll() override
	{
		event_based_device::poll();

		CURSORINFO cursor_info = {0};
		cursor_info.cbSize = sizeof(CURSORINFO);
		GetCursorInfo(&cursor_info);

		// We only take over the mouse if the cursor isn't showing
		// This should happen anyway in mouse mode
		if (!(cursor_info.flags & CURSOR_SHOWING))
		{
			// We measure the position change from the previously set center position
			mouse.lX = (cursor_info.ptScreenPos.x - win32_mouse.last_point.x) * INPUT_RELATIVE_PER_PIXEL;
			mouse.lY = (cursor_info.ptScreenPos.y - win32_mouse.last_point.y) * INPUT_RELATIVE_PER_PIXEL;

			RECT window_pos = {0};
			GetWindowRect(osd_common_t::s_window_list.front()->platform_window<HWND>(), &window_pos);

			// We reset the cursor position to the middle of the window each frame
			win32_mouse.last_point.x = window_pos.left + (window_pos.right - window_pos.left) / 2;
			win32_mouse.last_point.y = window_pos.top + (window_pos.bottom - window_pos.top) / 2;

			SetCursorPos(win32_mouse.last_point.x, win32_mouse.last_point.y);
		}
	}