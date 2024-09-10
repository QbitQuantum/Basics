void DoMain (HINSTANCE hInstance)
{
	LONG WinWidth, WinHeight;
	int height, width;
	RECT cRect;
	TIMECAPS tc;

	try
	{
#ifdef _MSC_VER
		_set_new_handler (NewFailure);
#endif

		Args.SetArgs (__argc, __argv);

		// Under XP, get our session ID so we can know when the user changes/locks sessions.
		// Since we need to remain binary compatible with older versions of Windows, we
		// need to extract the ProcessIdToSessionId function from kernel32.dll manually.
		HMODULE kernel = GetModuleHandle ("kernel32.dll");

		// NASM does not support creating writeable code sections (even though this
		// is a perfectly valid configuration for Microsoft's COFF format), so I
		// need to make the self-modifying code writeable after it's already loaded.
#ifdef USEASM
	{
		BYTE *module = (BYTE *)GetModuleHandle (NULL);
		IMAGE_DOS_HEADER *dosHeader = (IMAGE_DOS_HEADER *)module;
		IMAGE_NT_HEADERS *ntHeaders = (IMAGE_NT_HEADERS *)(module + dosHeader->e_lfanew);
		IMAGE_SECTION_HEADER *sections = IMAGE_FIRST_SECTION (ntHeaders);
		int i;
		LPVOID *start = NULL;
		SIZE_T size = 0;
		DWORD oldprotect;

		for (i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
		{
			if (memcmp (sections[i].Name, ".rtext\0", 8) == 0)
			{
				start = (LPVOID *)(sections[i].VirtualAddress + module);
				size = sections[i].Misc.VirtualSize;
				break;
			}
		}

		// I think these pages need to be mapped PAGE_EXECUTE_WRITECOPY (based on the
		// description of PAGE_WRITECOPY), but PAGE_EXECUTE_READWRITE seems to work
		// just as well; two instances of the program can be running with different
		// resolutions at the same time either way. Perhaps the file mappings for
		// executables are created with PAGE_WRITECOPY, so any attempts to give them
		// write access are automatically transformed to copy-on-write?
		//
		// This used to be PAGE_EXECUTE_WRITECOPY until Timmie found out Win9x doesn't
		// support it, although the MSDN does not indicate it.
		if (!VirtualProtect (start, size, PAGE_EXECUTE_READWRITE, &oldprotect))
		{
			I_FatalError ("The self-modifying code section code not be made writeable.");
		}
	}
#endif

		// Set the timer to be as accurate as possible
		if (timeGetDevCaps (&tc, sizeof(tc)) != TIMERR_NOERROR)
			TimerPeriod = 1;	// Assume minimum resolution of 1 ms
		else
			TimerPeriod = tc.wPeriodMin;

		timeBeginPeriod (TimerPeriod);

		/*
		killough 1/98:

		This fixes some problems with exit handling
		during abnormal situations.

		The old code called I_Quit() to end program,
		while now I_Quit() is installed as an exit
		handler and exit() is called to exit, either
		normally or abnormally.
		*/

		atexit (call_terms);

		atterm (I_Quit);

		// Figure out what directory the program resides in.
		GetModuleFileName (NULL, progdir, 1024);
		*(strrchr (progdir, '\\') + 1) = 0;
		FixPathSeperator (progdir);

		// [BC] When hosting, spawn a console dialog box instead of creating a window.
		if ( Args.CheckParm( "-host" ))
		{
			// This never returns.
			DialogBox( g_hInst, MAKEINTRESOURCE( IDD_SERVERDIALOG ), NULL/*(HWND)Window*/, SERVERCONSOLE_ServerDialogBoxCallback );
		}
		else
		{
			height = GetSystemMetrics (SM_CYFIXEDFRAME) * 2 +
					GetSystemMetrics (SM_CYCAPTION) + 12 * 32;
			width  = GetSystemMetrics (SM_CXFIXEDFRAME) * 2 + 8 * 78;

			TheInvisibleCursor = LoadCursor (hInstance, MAKEINTRESOURCE(IDC_INVISIBLECURSOR));
			TheArrowCursor = LoadCursor (NULL, IDC_ARROW);

			WndClass.style			= 0;
			WndClass.lpfnWndProc	= WndProc;
			WndClass.cbClsExtra		= 0;
			WndClass.cbWndExtra		= 0;
			WndClass.hInstance		= hInstance;
			WndClass.hIcon			= LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON5));
			WndClass.hCursor		= TheArrowCursor;
			WndClass.hbrBackground	= NULL;
			WndClass.lpszMenuName	= NULL;
			WndClass.lpszClassName	= (LPCTSTR)WinClassName;
			
			/* register this new class with Windows */
			if (!RegisterClass((LPWNDCLASS)&WndClass))
				I_FatalError ("Could not register window class");
			
			/* create window */
			Window = CreateWindow((LPCTSTR)WinClassName,
					(LPCTSTR) GAMESIG " v" DOTVERSIONSTR " (" __DATE__ ")",
					WS_OVERLAPPEDWINDOW,
					0/*CW_USEDEFAULT*/, 1/*CW_USEDEFAULT*/, width, height,
					(HWND)   NULL,
					(HMENU)  NULL,
							hInstance,
					NULL);

			if (!Window)
				I_FatalError ("Could not open window");

			WndClass.lpfnWndProc = LConProc;
			WndClass.lpszClassName = (LPCTSTR)ConClassName;
			if (RegisterClass ((LPWNDCLASS)&WndClass))
			{
				ConWindow = CreateWindowEx (
					WS_EX_PALETTEWINDOW & (~WS_EX_TOPMOST),
					(LPCTSTR)ConClassName,
					(LPCTSTR) "Skulltag Startup Viewer",
					WS_OVERLAPPEDWINDOW/* | WS_VISIBLE*/,
					CW_USEDEFAULT, CW_USEDEFAULT,
					512, 384,
					Window, NULL, hInstance, NULL);
			}

			if (kernel != 0)
			{
				typedef BOOL (WINAPI *pts)(DWORD, DWORD *);
				pts pidsid = (pts)GetProcAddress (kernel, "ProcessIdToSessionId");
				if (pidsid != 0)
				{
					if (!pidsid (GetCurrentProcessId(), &SessionID))
					{
						SessionID = 0;
					}
					hwtsapi32 = LoadLibraryA ("wtsapi32.dll");
					if (hwtsapi32 != 0)
					{
						FARPROC reg = GetProcAddress (hwtsapi32, "WTSRegisterSessionNotification");
						if (reg == 0 || !((BOOL(WINAPI *)(HWND, DWORD))reg) (Window, NOTIFY_FOR_THIS_SESSION))
						{
							FreeLibrary (hwtsapi32);
							hwtsapi32 = 0;
						}
						else
						{
							atterm (UnWTS);
						}
					}
				}
			}

			GetClientRect (Window, &cRect);

			WinWidth = cRect.right;
			WinHeight = cRect.bottom;
		}

		CoInitialize (NULL);
		atterm (UnCOM);

		C_InitConsole (((WinWidth / 8) + 2) * 8, (WinHeight / 12) * 8, false);

		I_DetectOS ();
		D_DoomMain ();
	}
	catch (class CDoomError &error)
	{
		I_ShutdownHardware ();
		SetWindowPos (Window, NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
		if (ConWindow != NULL)
		{
			ShowWindow (ConWindow, SW_SHOW);
		}
		if (error.GetMessage ())
			MessageBox (Window, error.GetMessage(),
				"Skulltag Fatal Error", MB_OK|MB_ICONSTOP|MB_TASKMODAL);
		exit (-1);
	}
}