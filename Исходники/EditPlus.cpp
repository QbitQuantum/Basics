	EditPlus()
	{
		installed_ = false;
		HKEY key;
		LPCWSTR szEditPlusHive = L"Software\\ES-Computing\\EditPlus 3\\Install";
		LONG lRet = RegOpenKeyW(HKEY_CURRENT_USER, szEditPlusHive, &key);
		if( lRet == ERROR_SUCCESS ) 
		{
			DWORD dwType = REG_SZ;
			DWORD dwSize = sizeof(szPath_);
			lRet = RegQueryValueExW(key, L"Path", NULL, &dwType, (LPBYTE)szPath_, &dwSize);
			if( lRet == ERROR_SUCCESS ) installed_ = true;
		}
	}