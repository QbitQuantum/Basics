void max_window(HWND window)
{
	RECT main_rect,wind_rect;
	short width,height;

	cursor_shown = true;
	showcursor(true);

	GetWindowRect(GetDesktopWindow(),&main_rect);
	GetWindowRect(window,&wind_rect);
	width = main_rect.right - main_rect.left;
	height = main_rect.bottom - main_rect.top;
	MoveWindow(window,0,0,width,height,true);
}