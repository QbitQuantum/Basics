HWND myGetConsoleWindow()
{
	HWND hConWnd = NULL;

	// If we are in ConEmuHk than gfGetRealConsoleWindow may be set
	if (gfGetRealConsoleWindow)
	{
		hConWnd = gfGetRealConsoleWindow();
		// If the function pointer was set - it must be proper function
		_ASSERTEX(hConWnd==NULL || isConsoleWindow(hConWnd));
		return hConWnd;
	}

	_ASSERTE(ghWorkingModule != 0);
	HMODULE hOurModule = (HMODULE)(DWORD_PTR)ghWorkingModule;

	if (!hConWnd)
	{
		if (!hkFunc.isConEmuHk())
		{
			// Must be already called, but JIC
			hkFunc.Init(L"Unknown", hOurModule);
		}

		hConWnd = GetConsoleWindow();
		// Current process may be GUI and have no console at all
		if (!hConWnd)
			return NULL;

		// RealConsole handle is stored in the Window DATA
		if (!hkFunc.isConEmuHk())
		{
			#ifdef _DEBUG
			wchar_t sClass[64] = L""; GetClassName(hConWnd, sClass, countof(sClass));
			#endif

			// Regardless of GetClassName result, it may be VirtualConsoleClass
			HWND h = (HWND)GetWindowLongPtr(hConWnd, 0);
			if (h && IsWindow(h) && isConsoleWindow(h))
			{
				hConWnd = h;
			}
		}
	}

	return hConWnd;

#if 0
	// Смысла звать GetProcAddress для "GetConsoleWindow" мало, все равно хукается
	typedef HWND (APIENTRY *FGetConsoleWindow)();
	static FGetConsoleWindow fGetConsoleWindow = NULL;

	if (!fGetConsoleWindow)
	{
		HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");

		if (hKernel32)
		{
			fGetConsoleWindow = (FGetConsoleWindow)GetProcAddress(hKernel32, "GetConsoleWindow");
		}
	}

	if (fGetConsoleWindow)
		hConWnd = fGetConsoleWindow();

	return hConWnd;
#endif
}