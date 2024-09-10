	bool get_fontfile(const char* font_name,  gameswf::tu_string& file_name, bool is_bold, bool is_italic)
	// gets font file name by font name
	{

		if (font_name == NULL)
		{
			return false;
		}

#ifdef _WIN32

		//Vitaly: I'm not sure that this code works on all versions of Windows

		tu_stringi fontname = font_name;
		if (is_bold)
		{
			fontname += " Bold";
		}
		if (is_italic)
		{
			fontname +=  " Italic";
		}
		fontname += " (TrueType)";

		HKEY hKey;

		// try WinNT
		DWORD retCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts", 
			0, 
			KEY_ALL_ACCESS,
			&hKey);

		if (retCode != ERROR_SUCCESS)
		{
			// try Windows
			retCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				"Software\\Microsoft\\Windows\\CurrentVersion\\Fonts", 
				0, 
				KEY_ALL_ACCESS,
				&hKey);

			if (retCode != ERROR_SUCCESS)
			{
				return false;
			}
		}

		// Get the value of the 'windir' environment variable.
		 gameswf::tu_string windir(getenv("WINDIR"));

		// Get value count. 
		DWORD    cValues;              // number of values for key 
		retCode = RegQueryInfoKey(
			hKey,	// key handle 
			NULL,	// buffer for class name 
			NULL,	// size of class string 
			NULL,	// reserved 
			NULL,	// number of subkeys 
			NULL,	// longest subkey size 
			NULL,	// longest class string 
			&cValues,	// number of values for this key 
			NULL,	// longest value name 
			NULL,	// longest value data 
			NULL,	// security descriptor 
			NULL);	// last write time 

		// Enumerate the key values. 
		BYTE szValueData[MAX_PATH];
		TCHAR  achValue[MAX_PATH]; 
		for (DWORD i = 0, retCode = ERROR_SUCCESS; i < cValues; i++) 
		{ 
			DWORD cchValue = MAX_PATH; 
			DWORD dwValueDataSize = sizeof(szValueData) - 1;
			achValue[0] = '\0'; 
			retCode = RegEnumValueA(hKey, i, 
				achValue, 
				&cchValue, 
				NULL, 
				NULL,
				szValueData,
				&dwValueDataSize);

			if (retCode == ERROR_SUCCESS) 
			{ 
				if ((fontname == (char*) achValue) || ((strstr(achValue, font_name) != NULL) && !is_italic && !is_bold))
				{
					file_name = windir +  gameswf::tu_string("\\Fonts\\") + (char*) szValueData;
					RegCloseKey(hKey);
					return true;
				}
			} 
		}

		RegCloseKey(hKey);
		return false;

#else

	//TODO for Linux

	// hack
	if (strstr(font_name, "Times New Roman"))
	{
		file_name = "/usr/share/fonts/truetype/times";
	}
	else
	if (strstr(font_name, "Arial"))
	{
		file_name = "/usr/share/fonts/truetype/arial";
	}
	else
	{
		return false;
	}

	if (is_bold && is_italic)
	{
		file_name += "bi";
	}
	else
	if (is_bold)
	{
		file_name +=  "b";
	}
	else
	if (is_italic)
	{
		file_name +=  "b";
	}
	file_name += ".ttf";

	return true;

#endif
	}