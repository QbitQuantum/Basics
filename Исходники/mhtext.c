LRESULT CALLBACK TextWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND control;
	HDC hdc;
	PNHTextWindow data;
	
	data = (PNHTextWindow)GetWindowLong(hWnd, GWL_USERDATA);
	switch (message) 
	{
	case WM_INITDIALOG:
	    /* set text control font */
		control = GetDlgItem(hWnd, IDC_TEXT_CONTROL);
		if( !control ) {
			panic("cannot get text view window");
		}

		hdc = GetDC(control);
		SendMessage(control, WM_SETFONT, (WPARAM)mswin_get_font(NHW_TEXT, ATR_NONE, hdc, FALSE), 0);
		ReleaseDC(control, hdc);

#if defined(WIN_CE_SMARTPHONE)
		/* special initialization for SmartPhone dialogs */ 
		NHSPhoneDialogSetup(hWnd, FALSE, GetNHApp()->bFullScreen);
#endif
		/* subclass edit control */
		editControlWndProc = (WNDPROC)GetWindowLong(control, GWL_WNDPROC);
		SetWindowLong(control, GWL_WNDPROC, (LONG)NHTextControlWndProc);

		if( !program_state.gameover && GetNHApp()->bWrapText ) {
			DWORD styles;
			styles = GetWindowLong(control, GWL_STYLE);
			if( styles ) {
				SetWindowLong(control, GWL_STYLE, styles & (~WS_HSCROLL));
				SetWindowPos(control, NULL, 0, 0, 0, 0, 
							  SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE );
			}
		}

		SetFocus(control);
	return FALSE;

	case WM_MSNH_COMMAND:
		onMSNHCommand(hWnd, wParam, lParam);
	break;

	case WM_SIZE:
		LayoutText(hWnd);
	return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) 
        { 
          case IDOK: 
		  case IDCANCEL:
			data->done = 1;
			return TRUE;
		}
	break;

	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSTATIC: { /* sent by edit control before it is drawn */
		HDC hdcEdit = (HDC) wParam; 
		HWND hwndEdit = (HWND) lParam;
		if( hwndEdit == GetDlgItem(hWnd, IDC_TEXT_CONTROL) ) {
			SetBkColor(hdcEdit, mswin_get_color(NHW_TEXT, MSWIN_COLOR_BG));
			SetTextColor(hdcEdit, mswin_get_color(NHW_TEXT, MSWIN_COLOR_FG)); 
			return (BOOL)mswin_get_brush(NHW_TEXT, MSWIN_COLOR_BG);
		}
	} return FALSE;

	case WM_DESTROY:
		if( data ) {
			mswin_free_text_buffer(data->window_text);
			free(data);
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)0);
		}
	break;

	}
	return FALSE;
}