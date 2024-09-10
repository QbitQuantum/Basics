LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg,
			     WPARAM wParam, LPARAM lParam)
{
    // Window dimensions

    RECT rWnd;
    RECT rClt;

    switch (uMsg)
    {
    case WM_CREATE:

	// Get the window and client dimensions

	GetWindowRect(hWnd, &rWnd);
	GetClientRect(hWnd, &rClt);

	// Calculate desired window width and height

	int border = (rWnd.right - rWnd.left) - rClt.right;
	int width  = WIDTH + border;
	int height = HEIGHT;

	// Set new dimensions

	SetWindowPos(hWnd, NULL, 0, 0,
		     width, height,
		     SWP_NOMOVE | SWP_NOZORDER);

	// Get client dimensions

	GetWindowRect(hWnd, &rWnd);
	GetClientRect(hWnd, &rClt);

	width = rClt.right - rClt.left;
	height = rClt.bottom - rClt.top;

	// Create scale

	scale.hwnd =
	    CreateWindow(WC_STATIC, NULL,
			 WS_VISIBLE | WS_CHILD |
			 SS_NOTIFY | SS_OWNERDRAW,
			 8, 8, 160, 40, hWnd,
			 (HMENU)SCALE_ID, hInst, NULL);

	// Create tooltip

	tooltip.hwnd =
	    CreateWindow(TOOLTIPS_CLASS, NULL,
			 WS_POPUP | TTS_ALWAYSTIP,
			 CW_USEDEFAULT, CW_USEDEFAULT,
			 CW_USEDEFAULT, CW_USEDEFAULT,
			 hWnd, NULL, hInst, NULL);

	SetWindowPos(tooltip.hwnd, HWND_TOPMOST, 0, 0, 0, 0,
		     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	// Add scale to tooltip

	tooltip.info.cbSize = sizeof(tooltip.info);
	tooltip.info.hwnd = hWnd;
	tooltip.info.uFlags = TTF_IDISHWND | TTF_SUBCLASS;

	tooltip.info.uId = (UINT_PTR)scale.hwnd;
	tooltip.info.lpszText = "Frequency scale";

	SendMessage(tooltip.hwnd, TTM_ADDTOOL, 0,
		    (LPARAM) &tooltip.info);

	// Create display

	display.hwnd =
	    CreateWindow(WC_STATIC, NULL,
			 WS_VISIBLE | WS_CHILD |
			 SS_NOTIFY | SS_OWNERDRAW,
			 176, 8, 136, 60, hWnd,
			 (HMENU)DISPLAY_ID, hInst, NULL);

	// Add display to tooltip

	tooltip.info.uId = (UINT_PTR)display.hwnd;
	tooltip.info.lpszText = "Frequency and level display";

	SendMessage(tooltip.hwnd, TTM_ADDTOOL, 0,
		    (LPARAM) &tooltip.info);

	// Create knob

	knob.hwnd =
	    CreateWindow(KNOBCLASS, NULL,
			 WS_VISIBLE | WS_CHILD,
			 4, 52, 168, 168, hWnd,
			 (HMENU)KNOB_ID, hInst, NULL);

	// Add knob to tooltip

	tooltip.info.uId = (UINT_PTR)knob.hwnd;
	tooltip.info.lpszText = "Frequency adjustment knob";

	SendMessage(tooltip.hwnd, TTM_ADDTOOL, 0,
		    (LPARAM) &tooltip.info);

	// Create frequency slider

	fine.hwnd =
	    CreateWindow(TRACKBAR_CLASS, NULL,
			 WS_VISIBLE | WS_CHILD |
			 TBS_VERT | TBS_NOTICKS,
			 176, 76, 24, 140, hWnd,
			 (HMENU)FINE_ID, hInst, NULL);

	SendMessage(fine.hwnd, TBM_SETRANGE, TRUE,
		    MAKELONG(FINE_MIN, FINE_MAX));
	SendMessage(fine.hwnd, TBM_SETPAGESIZE, 0, FINE_STEP);
	SendMessage(fine.hwnd, TBM_SETPOS, TRUE, FINE_REF);

	// Add slider to tooltip

	tooltip.info.uId = (UINT_PTR)fine.hwnd;
	tooltip.info.lpszText = "Fine frequency adjustment";

	SendMessage(tooltip.hwnd, TTM_ADDTOOL, 0,
		    (LPARAM) &tooltip.info);

	// Create level slider

	level.hwnd =
	    CreateWindow(TRACKBAR_CLASS, NULL,
			 WS_VISIBLE | WS_CHILD |
			 TBS_VERT | TBS_NOTICKS | TBS_LEFT,
			 208, 76, 24, 140, hWnd,
			 (HMENU)LEVEL_ID, hInst, NULL);

	SendMessage(level.hwnd, TBM_SETRANGE, TRUE,
		    MAKELONG(LEVEL_MIN, LEVEL_MAX));
	SendMessage(level.hwnd, TBM_SETPAGESIZE, 0, LEVEL_STEP);
	SendMessage(level.hwnd, TBM_SETPOS, TRUE, LEVEL_REF);

	// Add slider to tooltip

	tooltip.info.uId = (UINT_PTR)level.hwnd;
	tooltip.info.lpszText = "Level adjustment";

	SendMessage(tooltip.hwnd, TTM_ADDTOOL, 0,
		    (LPARAM) &tooltip.info);

	// Create sine button

	buttons.sine.hwnd =
	    CreateWindow(WC_BUTTON, "Sine",
			 WS_VISIBLE | WS_CHILD | WS_GROUP |
			 BS_AUTORADIOBUTTON | BS_PUSHLIKE,
			 240, 76, 72, 24, hWnd,
			 (HMENU)SINE_ID, hInst, NULL);

	SendMessage(buttons.sine.hwnd, BM_SETCHECK, BST_CHECKED, 0);

	// Create square button

	buttons.square.hwnd =
	    CreateWindow(WC_BUTTON, "Square",
			 WS_VISIBLE | WS_CHILD |
			 BS_AUTORADIOBUTTON | BS_PUSHLIKE,
			 240, 105, 72, 24, hWnd,
			 (HMENU)SQUARE_ID, hInst, NULL);

	// Create sawtooth button

	buttons.sawtooth.hwnd =
	    CreateWindow(WC_BUTTON, "Sawtooth",
			 WS_VISIBLE | WS_CHILD |
			 BS_AUTORADIOBUTTON | BS_PUSHLIKE,
			 240, 134, 72, 24, hWnd,
			 (HMENU)SAWTOOTH_ID, hInst, NULL);

	// Create mute button

	buttons.mute.hwnd =
	    CreateWindow(WC_BUTTON, "Mute",
			 WS_VISIBLE | WS_CHILD |
			 BS_AUTOCHECKBOX | BS_PUSHLIKE,
			 240, 161, 72, 24, hWnd,
			 (HMENU)MUTE_ID, hInst, NULL);

	// Create quit button

	buttons.quit.hwnd =
	    CreateWindow(WC_BUTTON, "Quit",
			 WS_VISIBLE | WS_CHILD,
			 240, 192, 72, 24, hWnd,
			 (HMENU)QUIT_ID, hInst, NULL);

	// Create status bar

	status.hwnd =
	    CreateWindow(STATUSCLASSNAME,
			 " Turn knob to adjust frequency,"
			 " fine left, level right slider",
			 WS_VISIBLE | WS_CHILD,
			 0, 0, 0, 0, hWnd,
			 (HMENU)STATUS_ID, hInst, NULL);

	// Start audio thread

	audio.thread = CreateThread(NULL, 0, AudioThread,
				    hWnd, 0, &audio.id);
	break;

    // Colour static text

    case WM_CTLCOLORSTATIC:
	return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
	break;

	// Draw item

    case WM_DRAWITEM:
	return DrawItem(wParam, lParam);
	break;

	// Disable menus by capturing this message

    case WM_INITMENU:
	break;

	// Capture system character key to stop pop up menus and other
	// nonsense

    case WM_SYSCHAR:
	break;

	// Char pressed

    case WM_CHAR:
	CharPressed(wParam, lParam);
	break;

	// Key pressed

    case WM_KEYDOWN:
	KeyDown(wParam, lParam);
	break;

	// Buttons

    case WM_COMMAND:
	switch (LOWORD(wParam))
	{
	    // Sine
	case SINE_ID:
	    audio.waveform = SINE;
	    break;

	    // Square

	case SQUARE_ID:
	    audio.waveform = SQUARE;
	    break;

	    // Sawtooth

	case SAWTOOTH_ID:
	    audio.waveform = SAWTOOTH;
	    break;

	    // Mute

	case MUTE_ID:
	    audio.mute = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
	    break;

	    // Quit

	case QUIT_ID:
	    waveOutReset(audio.hwo);
	    waveOutClose(audio.hwo);
	    PostQuitMessage(0);
	    break;
	}

	// Set the focus back to the window

	SetFocus(hWnd);
	break;

	// Slider change

    case WM_VSCROLL:
	SliderChange(wParam, lParam);

	// Set the focus back to the window

	SetFocus(hWnd);
	break;

	// Set the focus back to the window by clicking

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
	SetFocus(hWnd);
	break;

    case WM_RBUTTONDOWN:
	// Not used
	break;

	// Notify

    case WM_NOTIFY:
	switch (((LPNMHDR)lParam)->code)
	{
	    // Tooltip

	case TTN_SHOW:
	    TooltipShow(wParam, lParam);
	    break;

	case TTN_POP:
	    TooltipPop(wParam, lParam);
	    break;
	}
	break;

        // Process other messages.

    case WM_DESTROY:

	PostQuitMessage(0);
	waveOutReset(audio.hwo);
	waveOutClose(audio.hwo);
	break;

	// Everything else

    default:
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}