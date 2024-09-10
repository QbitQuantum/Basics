void WindowsHost::SetWindowTitle(const char *message)
{
	std::string title = std::string("PPSSPP ") + PPSSPP_GIT_VERSION + " - " + message;

	int size = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), (int) title.size(), NULL, 0);
	if (size > 0)
	{
		// VC++6.0 any more?
		wchar_t *utf16_title = new(std::nothrow) wchar_t[size + 1];
		if (utf16_title)
			size = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), (int) title.size(), utf16_title, size);
		else
			size = 0;

		if (size > 0)
		{
			utf16_title[size] = 0;
			// Don't use SetWindowTextW because it will internally use DefWindowProcA.
			DefWindowProcW(mainWindow_, WM_SETTEXT, 0, (LPARAM) utf16_title);
			delete[] utf16_title;
		}
	}

	// Something went wrong, fall back to using the local codepage.
	if (size <= 0)
		SetWindowTextA(mainWindow_, title.c_str());
}