	NotepadPlusPlus()
	{
		installed_ = false;
		HKEY key;
		LPCWSTR szNotepadPlusPlusHive = L"SOFTWARE\\Notepad++";
		LONG lRet = RegOpenKeyW(HKEY_LOCAL_MACHINE, szNotepadPlusPlusHive, &key);
		if( lRet == ERROR_SUCCESS ) 
		{
			DWORD dwType = REG_SZ;
			DWORD dwSize = sizeof(szPath_);
			lRet = RegQueryValueExW(key, NULL, NULL, &dwType, (LPBYTE)szPath_, &dwSize);
			if( lRet == ERROR_SUCCESS ) installed_ = true;
		}
	}