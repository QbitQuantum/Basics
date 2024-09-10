int WINAPI
WinMain (HINSTANCE hThisInstance,
         HINSTANCE hPrevInstance,
         LPSTR lpCmdLine,
         int nCmdShow)
{
	int argc;
	WCHAR** argv;
	WCHAR szFileName[MAX_PATH] = L"";
	DWORD dwSize;
	HWND hMainWnd;
	MSG msg;
	WNDCLASSEXW wincl;
	LPCWSTR fileName;

    switch (GetUserDefaultUILanguage())
    {
    case MAKELANGID(LANG_HEBREW, SUBLANG_DEFAULT):
      SetProcessDefaultLayout(LAYOUT_RTL);
      break;

    default:
      break;
    }

	g_hInstance = hThisInstance;

	/* Get unicode command line */
	argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argc < 2)
	{
		OPENFILENAMEW fontOpen;
        WCHAR filter[MAX_PATH], dialogTitle[MAX_PATH];

		LoadStringW(NULL, IDS_OPEN, dialogTitle, MAX_PATH);
		LoadStringW(NULL, IDS_FILTER_LIST, filter, MAX_PATH);

		/* Clears out any values of fontOpen before we use it */
		ZeroMemory(&fontOpen, sizeof(fontOpen));

		/* Sets up the open dialog box */
		fontOpen.lStructSize = sizeof(fontOpen);
		fontOpen.hwndOwner = NULL;
		fontOpen.lpstrFilter = filter;
		fontOpen.lpstrFile = szFileName;
		fontOpen.lpstrTitle = dialogTitle;
		fontOpen.nMaxFile = MAX_PATH;
		fontOpen.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		fontOpen.lpstrDefExt = L"ttf";

		/* Opens up the Open File dialog box in order to chose a font file. */
		if(GetOpenFileNameW(&fontOpen))
		{
			fileName = fontOpen.lpstrFile;
			g_fileName = fileName;
		} else {
			/* If the user decides to close out of the open dialog effectively
			exiting the program altogether */
			return 0;
		}
	}
	else
	{
		/* Try to add the font resource from command line */
		fileName = argv[1];
		g_fileName = fileName;
	}

	if (!AddFontResourceW(fileName))
	{
		ErrorMsgBox(0, IDS_ERROR_NOFONT, fileName);
		return -1;
	}

	/* Get the font name */
	dwSize = sizeof(g_ExtLogFontW.elfFullName);
	if (!GetFontResourceInfoW(fileName, &dwSize, g_ExtLogFontW.elfFullName, 1))
	{
		ErrorMsgBox(0, IDS_ERROR_NOFONT, fileName);
		return -1;
	}

	dwSize = sizeof(LOGFONTW);
	if (!GetFontResourceInfoW(fileName, &dwSize, &g_ExtLogFontW.elfLogFont, 2))
	{
		ErrorMsgBox(0, IDS_ERROR_NOFONT, fileName);
		return -1;
	}

	if (!Display_InitClass(hThisInstance))
	{
		ErrorMsgBox(0, IDS_ERROR_NOCLASS);
		return -1;
	}

	/* The main window class */
	wincl.cbSize = sizeof (WNDCLASSEXW);
	wincl.style = CS_DBLCLKS;
	wincl.lpfnWndProc = MainWndProc;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hInstance = hThisInstance;
	wincl.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_TT));
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wincl.lpszMenuName = NULL;
	wincl.lpszClassName = g_szFontViewClassName;
	wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_TT));

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassExW (&wincl))
	{
		ErrorMsgBox(0, IDS_ERROR_NOCLASS);
		return 0;
	}

	/* The class is registered, let's create the main window */
	hMainWnd = CreateWindowExW(
				0,						/* Extended possibilites for variation */
				g_szFontViewClassName,	/* Classname */
				g_ExtLogFontW.elfFullName,/* Title Text */
				WS_OVERLAPPEDWINDOW,	/* default window */
				CW_USEDEFAULT,			/* Windows decides the position */
				CW_USEDEFAULT,			/* where the window ends up on the screen */
				544,					/* The programs width */
				375,					/* and height in pixels */
				HWND_DESKTOP,			/* The window is a child-window to desktop */
				NULL,					/* No menu */
				hThisInstance,			/* Program Instance handler */
				NULL					/* No Window Creation data */
			);
	ShowWindow(hMainWnd, nCmdShow);

	/* Main message loop */
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	RemoveFontResourceW(argv[1]);

	return (int)msg.wParam;
}