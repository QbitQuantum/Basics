BOOL CALLBACK
WndProc (HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
    static HBRUSH hBrush = NULL;

    switch (umsg)
    {
    case WM_CREATE:
	if (!render_init (hwnd, g_gui_prefs.default_skin)) {
	    MessageBox(hwnd, "Failed to find the skin bitmap", "Error", 0);
	    break;
	}
	stop_button_disable();
	if (OPT_FLAG_ISSET(g_rmo.flags, OPT_MAKE_RELAY)) {
	    render_relay_button_enable ();
	} else {
	    render_relay_button_disable ();
	}

	SetTimer (hwnd, 1, 500, (TIMERPROC)UpdateDisplay);
	dock_init (hwnd);

	return 0;

    case WM_PAINT:
	{
	    PAINTSTRUCT pt;
	    HDC hdc = BeginPaint(hwnd, &pt);
	    render_do_paint(hdc);
	    EndPaint(hwnd, &pt);
	}
	return 0;
		
    case WM_MOUSEMOVE:
	render_do_mousemove (hwnd, wParam, lParam);
	dock_do_mousemove (hwnd, wParam, lParam);
	break;

    case WM_COMMAND:
	switch(wParam)
	{
	case ID_MENU_STARTRIPPING:
	    start_button_pressed();
	    break;
	case ID_MENU_STOPRIPPING:
	    stop_button_pressed();
	    break;
	case ID_MENU_OPTIONS:
	    options_button_pressed();
	    break;
	case ID_MENU_OPEN:
	    PostMessage(hwnd, WM_MY_TRAY_NOTIFICATION, (WPARAM)NULL, WM_LBUTTONDBLCLK);
	    break;
	case ID_MENU_RESET_URL:
	    strcpy(g_rmo.url, "");
	    set_ripping_url (0);
	    break;
	case ID_MENU_LOAD_URL:
	    debug_printf ("Load URL dialog box\n");
	    open_load_url_dialog ();
	    break;
	case ID_MENU_EXIT:
	    debug_printf ("User requested exit\n");
	    quit ();
	    PostQuitMessage( 0 );
	    break;
	default:
	    if (wParam >= ID_MENU_HISTORY_LIST && wParam < ID_MENU_HISTORY_LIST + RIPLIST_LEN) {
		int i = wParam - ID_MENU_HISTORY_LIST;
		char* url = g_gui_prefs.riplist[i];
		debug_printf ("Setting URL through history list\n");
		strcpy(g_rmo.url, url);
		set_ripping_url (url);
	    }
	    break;
	}
	break;

    case WM_MY_TRAY_NOTIFICATION:
	switch(lParam)
	{
	case WM_LBUTTONDBLCLK:
	    dock_show_window(m_hwnd, SW_NORMAL);
	    SetForegroundWindow(hwnd);
	    g_gui_prefs.m_start_minimized = FALSE;
	    break;

	case WM_RBUTTONDOWN:
	    {
		int item;
		POINT pt;
		GetCursorPos(&pt);
		SetForegroundWindow(hwnd);
		item = TrackPopupMenu(m_hmenu_systray_sub, 
				      0,
				      pt.x,
				      pt.y,
				      (int)NULL,
				      hwnd,
				      NULL);
	    }
	    break;
	}
	break;

    case WM_LBUTTONDOWN:
	dock_do_lbuttondown(hwnd, wParam, lParam);
	render_do_lbuttondown(hwnd, wParam, lParam);
	break;

    case WM_LBUTTONUP:
	dock_do_lbuttonup(hwnd, wParam, lParam);
	render_do_lbuttonup(hwnd, wParam, lParam);
	{
	    BOOL rc;
	    RECT rt;
	    rc = GetWindowRect(hwnd, &rt);
	    if (rc) {
		g_gui_prefs.oldpos_x = rt.left;
		g_gui_prefs.oldpos_y = rt.top;
	    }
	}
	break;
	
    case WM_RBUTTONDOWN:
	{
	    int item;
	    POINT pt;
	    if (!m_bRipping) {
		GetCursorPos (&pt);
		SetForegroundWindow (hwnd);
		item = TrackPopupMenu (m_hmenu_context_sub, 
					0,
					pt.x,
					pt.y,
					(int)NULL,
					hwnd,
					NULL);
	    }
	}
	break;
	
    case WM_APP+0:
	handle_wm_app (hwnd, wParam, lParam);
	break;
    case WM_APP+1:
	/* Exit request from thread */
	quit ();
	PostQuitMessage( 0 );
	break;
    case WM_DESTROY:
	debug_printf ("Got WM_DESTROY\n");
	PostQuitMessage( 0 );
	break;
    case WM_QUIT:
	debug_printf ("Got WM_QUIT\n");
	break;
    }
    return DefWindowProc (hwnd, umsg, wParam, lParam);
}