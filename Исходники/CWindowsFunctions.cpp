BOOL CALLBACK CWindowsFunctions::CB_EnumChildProc(HWND hwnd, LPARAM lParam)
{
	int length = GetWindowTextLengthA(hwnd);

	if (length > 0)
	{
		length++; // NULL character

		char* jpn = new char[length];
	
		length = GetWindowTextA(hwnd, jpn, length);

		if (length > 0)
		{
			char className[6];
			GetClassNameA(hwnd, className, sizeof(className));

			if (strcmp(className, "Edit") != 0)
			{
				bool result = m_resources->TranslateUserInterface(jpn, m_uiBuffer, UI_BUFFER);

				if (result)
				{
					SetWindowTextA(hwnd, m_uiBuffer);
				}
			}
		}

		delete[] jpn;
	}

	return TRUE;
}