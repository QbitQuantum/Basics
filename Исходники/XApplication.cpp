	BOOL Application::Error(BOOL Fatal, LPCTSTR Text, ...)
	{
		TCHAR CaptionText[12];
		TCHAR ErrorText[2048];
		va_list valist;

		// Build the message box caption based on fatal flag
		if(Fatal == FALSE)
			lstrcpy(CaptionText, L"Error");
		else 
			lstrcpy(CaptionText, L"Fatal Error");

		// Build variable text buffer
		va_start(valist, Text);
		vswprintf_s(ErrorText, sizeof(ErrorText), Text, valist);
		va_end(valist);

		// Display the message box
		MessageBox(NULL, ErrorText, CaptionText, MB_OK | MB_ICONEXCLAMATION);

		// Post a quit message if error was fatal
		if(Fatal == TRUE)
			PostQuitMessage(0);

		return TRUE;
	}