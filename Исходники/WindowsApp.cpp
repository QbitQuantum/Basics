	bool CWindowsApp::Init(wchar_t *windowName, int width, int height)
	{
		m_wndClassEx.cbSize = sizeof(WNDCLASSEX);
		m_wndClassEx.style = CS_CLASSDC;
		m_wndClassEx.lpfnWndProc = MsgProc;
		m_wndClassEx.cbClsExtra = 0L;
		m_wndClassEx.cbWndExtra = 0L;
		m_wndClassEx.hInstance = m_instanceHandle;
		m_wndClassEx.hIcon = nullptr;
		m_wndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_wndClassEx.hbrBackground = nullptr;
		m_wndClassEx.lpszMenuName = nullptr;
		m_wndClassEx.lpszClassName = L"framework_9";
		m_wndClassEx.hIconSm = nullptr;
		//RegisterClassEx(&m_wndClassEx);
		RegisterClassExW(&m_wndClassEx);

		int screenX = GetSystemMetrics(SM_CXSCREEN);
		int screenY = GetSystemMetrics(SM_CYSCREEN);

		RECT windowRect;
		ZeroMemory(&windowRect, sizeof(windowRect));
		windowRect.left = (screenX - width) / 2;
		windowRect.top = (screenY - height) / 2;
		windowRect.right = windowRect.left + width;
		windowRect.bottom = windowRect.top + height;
		AdjustWindowRectEx(&windowRect, WindowStyle, 0, 0);

		//m_windowHandle = CreateWindowEx(
		m_windowHandle = CreateWindowExW(
			0L, m_wndClassEx.lpszClassName, windowName,
			WindowStyle,
			windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			nullptr, nullptr, m_wndClassEx.hInstance, nullptr
			);

		m_width = width;
		m_height = height;

		if (!AllocDevice())
			return false;

		return true;
	}