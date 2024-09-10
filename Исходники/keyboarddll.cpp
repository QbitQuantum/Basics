KEYBOARDDLL_API int SendString(const HWND hwnd, const RECT rect, const CString s, const bool use_comma,
							   const HWND restore_focus, const POINT restore_cursor)
{
	INPUT			input[102];

	POINT pt = RandomizeClickLocation(rect);
	double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1;
	double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1;

	// Translate click point to screen/mouse coords
	ClientToScreen(hwnd, &pt);
	double fx = pt.x*(65535.0f/fScreenWidth);
	double fy = pt.y*(65535.0f/fScreenHeight);

	// Set up the input structure

	int input_count=0;

	// First click in the rect to select it, if rect is not passed in as {-1, -1, -1, -1}
	if (rect.left!=-1 || rect.top!=-1 || rect.right!=-1 || rect.bottom!=-1)
	{
		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_MOUSE;
		input[input_count].mi.dx = (LONG) fx;
		input[input_count].mi.dy = (LONG) fy;
		input[input_count].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN;
		input_count++;
		
		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_MOUSE;
		input[input_count].mi.dx = (LONG) fx;
		input[input_count].mi.dy = (LONG) fy;
		input[input_count].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
		input_count++;
	}

	// Set focus to target window
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);

	// Send input
	SendInput(input_count, input, sizeof(INPUT));

	// Send each character of the string via PlayKeyboardEvent
	char ch_str[100];
	sprintf_s(ch_str, 100, "%s", s.GetString());

	int	vkey = 0;

	int i = 0, strlength = (int)strlen(ch_str);
	short KeyScan;
	for (int i=0; i<strlength; i++)
	{
		Sleep(20);
		if (use_comma && ch_str[i]=='.')
			ch_str[i] = ',';
		KeyScan = VkKeyScan(ch_str[i]);
		PlayKeyboardEvent(LOBYTE(KeyScan), HIBYTE(KeyScan));
	}
	Sleep(20);

	// Restore previous window state and cursor position
	if (restore_focus!=NULL)
	{
		SetActiveWindow(restore_focus);
		SetForegroundWindow(restore_focus);
		SetFocus(restore_focus);
	}

	// Remove that code-block, if you don't want to restore the mouse-cursor!
	if (restore_cursor.x!=-1 && restore_cursor.y!=-1)
	{
		SetCursorPos(restore_cursor.x, restore_cursor.y);
	}

	return (int) true;
}