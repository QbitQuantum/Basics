Win32Window::Win32Window(long x, long y, long width, long height)
{
	if( handles.size() == 0 )
	{
		wc.cbSize			= sizeof(WNDCLASSEX);
		wc.style			= CS_OWNDC;
		wc.lpfnWndProc		= (WNDPROC)WndProc;
		wc.cbClsExtra		= 0L;
		wc.cbWndExtra		= 0L;
		wc.hInstance		= GetModuleHandle(NULL);
		wc.hIcon			= NULL;
		wc.hCursor			= LoadCursor(0, IDC_ARROW);
		wc.hbrBackground	= NULL;
		wc.lpszMenuName		= NULL;
		wc.lpszClassName	= "TestClass";
		wc.hIconSm			= NULL;

		RegisterClassEx(&wc);
	}

	KeyPressCallback	= 0;
	MouseMoveCallback	= 0;
	UpdateCallback		= 0;
	RenderCallback		= 0;
	CloseCallback		= 0;
	CreateCallback		= 0;

	RECT realrect;
	RECT rect = { x, y, width, height };
	DWORD style = WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_SYSMENU|WS_BORDER|WS_CAPTION|WS_MINIMIZEBOX;

	rect.left	= x;
	rect.top	= y;
	rect.right	= x + width;
	rect.bottom	= y + height;

	hwnd = CreateWindowA("TestClass", "Win32Window", style,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, wc.hInstance, NULL);

	DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &realrect, sizeof(RECT));

	rect.left	= rect.left + (rect.left - realrect.left);
	rect.right	= rect.right - (realrect.right - rect.right);
	rect.top	= rect.top + (rect.top - realrect.top);
	rect.bottom	= rect.bottom - (realrect.bottom - rect.bottom);

	MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);

	hdc			= 0;
	glcontextid	= -1;
	drawingitem	= 0;

	if( hwnd )
	{
		hdc = GetDC(hwnd);
		glcontextid = GetRenderingCore()->CreateUniverse(hdc);

		if( glcontextid != -1 )
		{
			drawingitem = new DrawingItem(
				glcontextid,
				(unsigned int)(rect.right - rect.left),
				(unsigned int)(rect.bottom - rect.top));
		}
	}

	handlesguard.Lock();
	handles.insert(windowmap::value_type(hwnd, this));
	handlesguard.Unlock();
}