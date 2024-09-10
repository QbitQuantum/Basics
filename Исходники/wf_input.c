BOOL wf_peer_extended_mouse_event(rdpInput* input, UINT16 flags, UINT16 x, UINT16 y)
{
	if ((flags & PTR_XFLAGS_BUTTON1) || (flags & PTR_XFLAGS_BUTTON2))
	{
		INPUT mouse_event;
		ZeroMemory(&mouse_event, sizeof(INPUT));
		mouse_event.type = INPUT_MOUSE;

		if (flags & PTR_FLAGS_MOVE)
		{
			float width, height;
			wfInfo* wfi;
			wfi = wf_info_get_instance();

			if (!wfi)
				return FALSE;

			//width and height of primary screen (even in multimon setups
			width = (float) GetSystemMetrics(SM_CXSCREEN);
			height = (float) GetSystemMetrics(SM_CYSCREEN);
			x += wfi->servscreen_xoffset;
			y += wfi->servscreen_yoffset;
			mouse_event.mi.dx = (LONG)((float) x * (65535.0f / width));
			mouse_event.mi.dy = (LONG)((float) y * (65535.0f / height));
			mouse_event.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
			SendInput(1, &mouse_event, sizeof(INPUT));
		}

		mouse_event.mi.dx = mouse_event.mi.dy = mouse_event.mi.dwFlags = 0;

		if (flags & PTR_XFLAGS_DOWN)
			mouse_event.mi.dwFlags |= MOUSEEVENTF_XDOWN;
		else
			mouse_event.mi.dwFlags |= MOUSEEVENTF_XUP;

		if (flags & PTR_XFLAGS_BUTTON1)
			mouse_event.mi.mouseData = XBUTTON1;
		else if (flags & PTR_XFLAGS_BUTTON2)
			mouse_event.mi.mouseData = XBUTTON2;

		SendInput(1, &mouse_event, sizeof(INPUT));
	}
	else
	{
		wf_peer_mouse_event(input, flags, x, y);
	}

	return TRUE;
}