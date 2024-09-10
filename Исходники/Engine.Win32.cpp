	void MessageBox(const wchar_t* caption, const wchar_t* message)
	{
		MessageBoxW(0, message, caption, MB_OK | MB_ICONINFORMATION);
	}