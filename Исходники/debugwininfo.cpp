LRESULT debugwin_info::window_proc(UINT message, WPARAM wparam, LPARAM lparam)
{
	// handle a few messages
	switch (message)
	{
	// paint: draw bezels as necessary
	case WM_PAINT:
		{
			PAINTSTRUCT pstruct;
			HDC dc = BeginPaint(m_wnd, &pstruct);
			draw_contents(dc);
			EndPaint(m_wnd, &pstruct);
			break;
		}

	// keydown: handle debugger keys
	case WM_KEYDOWN:
		if (handle_key(wparam, lparam))
			set_ignore_char_lparam(lparam);
		break;

	// char: ignore chars associated with keys we've handled
	case WM_CHAR:
		if (check_ignore_char_lparam(lparam))
		{
			if (waiting_for_debugger() || !seq_pressed())
				return DefWindowProc(m_wnd, message, wparam, lparam);
		}
		break;

	// activate: set the focus
	case WM_ACTIVATE:
		if (wparam != WA_INACTIVE)
			set_default_focus();
		break;

	// get min/max info: set the minimum window size
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *minmax = (MINMAXINFO *)lparam;
			minmax->ptMinTrackSize.x = m_minwidth;
			minmax->ptMinTrackSize.y = m_minheight;
			minmax->ptMaxSize.x = minmax->ptMaxTrackSize.x = m_maxwidth;
			minmax->ptMaxSize.y = minmax->ptMaxTrackSize.y = m_maxheight;
			break;
		}

	// sizing: recompute child window locations
	case WM_SIZE:
	case WM_SIZING:
		recompute_children();
		InvalidateRect(m_wnd, NULL, FALSE);
		break;

	// mouse wheel: forward to the first view
	case WM_MOUSEWHEEL:
		{
			static int units_carryover = 0;

			UINT lines_per_click;
			if (!SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &lines_per_click, 0))
				lines_per_click = 3;

			int const units = GET_WHEEL_DELTA_WPARAM(wparam) + units_carryover;
			int const clicks = units / WHEEL_DELTA;
			units_carryover = units % WHEEL_DELTA;

			int const delta = clicks * lines_per_click;
			int viewnum = 0;
			POINT point;

			// figure out which view we are hovering over
			GetCursorPos(&point);
			ScreenToClient(m_wnd, &point);
			HWND const child = ChildWindowFromPoint(m_wnd, point);
			if (child)
			{
				for (viewnum = 0; viewnum < MAX_VIEWS; viewnum++)
				{
					if ((m_views[viewnum] != NULL) && m_views[viewnum]->owns_window(child))
						break;
				}
				if (viewnum == MAX_VIEWS)
					break;
			}

			// send the appropriate message to this view's scrollbar
			if (m_views[viewnum] != NULL)
				m_views[viewnum]->send_vscroll(delta);

			break;
		}

	// activate: set the focus
	case WM_INITMENU:
		update_menu();
		break;

	// command: handle a comment
	case WM_COMMAND:
		if (!handle_command(wparam, lparam))
			return DefWindowProc(m_wnd, message, wparam, lparam);
		break;

	// close: close the window if it's not the main console
	case WM_CLOSE:
		if (m_is_main_console)
		{
			debugger().hide_all();
			debug_cpu_get_visible_cpu(machine())->debug()->go();
		}
		else
		{
			destroy();
		}
		break;

	// destroy: close down the window
	case WM_NCDESTROY:
		m_wnd = NULL;
		debugger().remove_window(*this);
		break;

	// everything else: defaults
	default:
		return DefWindowProc(m_wnd, message, wparam, lparam);
	}

	return 0;
}