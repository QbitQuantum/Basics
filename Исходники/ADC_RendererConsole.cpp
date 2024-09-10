	// Sets the console font properties.
	void SetFontProperties(int fontX, int fontY, wchar_t *fontName)
	{
		HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		/* Retrieving pointers for Windows Vista/7 Functions */
		PGetCurrentConsoleFontEx pGetCurrentConsoleFontEx = (PGetCurrentConsoleFontEx)
			GetProcAddress(GetModuleHandle("kernel32.dll"), "GetCurrentConsoleFontEx");
		PSetCurrentConsoleFontEx pSetCurrentConsoleFontEx = (PSetCurrentConsoleFontEx)
			GetProcAddress(GetModuleHandle("kernel32.dll"), "SetCurrentConsoleFontEx");

		/* Check for pointers: if they exist, we have Vista/7 and we can use them */
		if (pGetCurrentConsoleFontEx && pSetCurrentConsoleFontEx)
		{
			CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };

			/* Tell the font info how big it is, to avoid memory corruption */
			cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
			pGetCurrentConsoleFontEx(hOutput, TRUE, &cfi);

			/* Set the font type to name indicated by wide string literal */
			/* Set to 0 to keep current settings */
			lstrcpyW(cfi.FaceName, fontName);
			cfi.dwFontSize.X = fontX;
			cfi.dwFontSize.Y = fontY;
			cfi.FontFamily = 0; /* Set to 0x30 for Terminal font */
			cfi.FontWeight = 0;

			/* Set the console font info */
			pSetCurrentConsoleFontEx(hOutput, TRUE, &cfi);
		}
		else  /* We don't have access to the vista functions */
		{
			CONSOLE_INFO2 ci = { sizeof(ci) };
			HWND hwndConsole = GetConsoleWindow();

			GetConsoleSizeInfo(&ci, hOutput);

			/* Set to 0 to keep current settings */
			ci.FontSize.X = fontX;
			ci.FontSize.Y = fontY;
			ci.FontFamily = 0; /* Set to 0x30 for Terminal font */
			ci.FontWeight = 0;

			lstrcpyW(ci.FaceName, fontName);
			ci.CursorSize = 100;
			ci.FullScreen = FALSE;
			ci.QuickEdit = FALSE;
			ci.AutoPosition = 0x10000;
			ci.InsertMode = TRUE;
			ci.ScreenColors = MAKEWORD(0x7, 0x0);
			ci.PopupColors = MAKEWORD(0x5, 0xf);
			ci.HistoryNoDup = TRUE;
			ci.HistoryBufferSize = 50;
			ci.NumberOfHistoryBuffers = 4;

			ci.CodePage = 0;
			ci.Hwnd = hwndConsole;
			lstrcpyW(ci.ConsoleTitle, L"");

			SetConsoleInfo(hwndConsole, &ci);
		}
	}