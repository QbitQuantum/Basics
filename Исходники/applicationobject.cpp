void ApplicationObject::InitializeWindow(int width, int height, const bool& fullscreen)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	DWORD ExStyle, Style;
	RECT WindowSize;

	ExStyle = WS_EX_APPWINDOW;
	Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUP;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_instance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_name;
	wc.cbSize = sizeof(WNDCLASSEX);
	
	RegisterClassEx(&wc);

	if(fullscreen)
	{
		width  = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)width;
		dmScreenSettings.dmPelsHeight = (unsigned long)height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		WindowSize.left = 0;
		WindowSize.top = 0;
		WindowSize.right = GetSystemMetrics(SM_CXSCREEN);
		WindowSize.bottom = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		width  = 1280;
		height = 720;
		
		WindowSize.left = (GetSystemMetrics(SM_CXSCREEN) - width)  / 2;
		WindowSize.top = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		WindowSize.right = WindowSize.left + width;
		WindowSize.bottom = WindowSize.top + height;
	}

	m_fullscreen = fullscreen;
	m_width = width;
	m_height = height;
	
	AdjustWindowRectEx(&WindowSize, Style, FALSE, ExStyle);
	m_hwnd = CreateWindowEx(ExStyle, m_name, m_name, Style, WindowSize.left, WindowSize.top, WindowSize.right-WindowSize.left, WindowSize.bottom-WindowSize.top, NULL, NULL, m_instance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	m_graphics = new GraphicsObject(m_hwnd, m_width, m_height, m_fullscreen);
	
	m_input = new InputObject();
	if (!m_input->Initialize(m_instance, m_hwnd, m_width, m_height))
		MessageBox(m_hwnd, L"HEY SOMETHING WENT WRONG", L"ERROR OR SOMETHING", 0);

	return;
}