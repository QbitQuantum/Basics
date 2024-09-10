HANDLE CLyricsDlg::OpenLyricsFile(HWND hDlg)
{
	//first, we get a key to the current user:
	HKEY hKey;
	char strError[30];
	
	if (0 != RegOpenCurrentUser(KEY_WRITE | KEY_READ, &hKey))
	{
		sprintf_s(strError, 30, "Error 0x%x.", GetLastError());
		MessageBoxA(genDll.m_hWinamp, strError, "Fatal Error!", MB_ICONERROR);
#ifdef _DEBUG
			DebugBreak();
#endif
		return INVALID_HANDLE_VALUE;
	}

	if (0 != RegOpenKeyEx(hKey, L"Volatile Environment", 0, KEY_READ, &hKey))
	{
		sprintf_s(strError, 30, "Error 0x%x.", GetLastError());
		MessageBoxA(genDll.m_hWinamp, strError, "Fatal Error!", MB_ICONERROR);
#ifdef _DEBUG
			DebugBreak();
#endif
		return INVALID_HANDLE_VALUE;
	}

	DWORD dwType;
	DWORD dwSize;
	wchar_t str[MAX_PATH];
	if (ERROR_SUCCESS != RegQueryValueEx(hKey, L"APPDATA", 0, &dwType, (LPBYTE)str, &dwSize))
//	if (ERROR_SUCCESS != RegGeValue(hKey, 0, L"APPDATA", RRF_RT_REG_SZ, &dwType, str, &dwSize))
	{
		sprintf_s(strError, 30, "Error 0x%x.", GetLastError());
		MessageBoxA(genDll.m_hWinamp, strError, "Fatal Error!", MB_ICONERROR);
#ifdef _DEBUG
			DebugBreak();
#endif
		return INVALID_HANDLE_VALUE;
	}

	RegCloseKey(hKey);

	//create or open the directory:
	wstring wsPath = str;
	wsPath += L"\\Winamp";
	CreateDirectory(wsPath.data(), 0);
	wsPath += L"\\Plugins";
	CreateDirectory(wsPath.data(), 0);
	wsPath += L"\\Feoggou App";
	CreateDirectory(wsPath.data(), 0);
	wstring wsPath2 = wsPath;
	wsPath += L"\\*.lyr";

	//filename: 1.lyr, 2.lyr, ...

	//if the file does not exist, we create it. but we must make sure that that lyric does not exist.
	//file format:
	//HEADER:				'LYR'
	//						artist[30]
	//						album[30]
	//						song[30]
	//						.............
	//BODY:					sec (word)
	//						text len(byte)
	//						text (char*)

	//Get the data from the dialog. at least "Song" must be specified.
	char sSong[30], sArtist[30], sAlbum[30];
	GetDlgItemTextA(hDlg, IDC_SONGNAME, sSong, 30);
	GetDlgItemTextA(hDlg, IDC_ARTISTNAME, sArtist, 30);
	GetDlgItemTextA(hDlg, IDC_ALBUMNAME, sAlbum, 30);

	if (strlen(sSong) == 0)
	{
		MessageBoxA(hDlg, "Trebuie să specifici numele melodiei în caseta \"Melodie:\". ", "Salvare versuri", MB_ICONEXCLAMATION);
		return INVALID_HANDLE_VALUE;
	}
	
	if (strlen(sArtist) == 0)
	{
		int nResult = MessageBoxA(hDlg, "Este o idee bună să specifici numele artistului, dacă îl știi. Vrei să te întorci să îl scrii?", "Lipsește numele artistului", MB_ICONEXCLAMATION | MB_YESNO);
		if (nResult == IDYES) return INVALID_HANDLE_VALUE;
	}

	if (strlen(sAlbum) == 0)
	{
		int nResult = MessageBoxA(hDlg, "Este o idee bună să specifici numele albumului, dacă îl știi. Vrei să te întorci să îl scrii?", "Lipsește numele albumului", MB_ICONEXCLAMATION | MB_YESNO);
		if (nResult == IDYES) return INVALID_HANDLE_VALUE;
	}

	WIN32_FIND_DATA f_data;
	BOOL bResult =0;
	memset(&f_data, 0, sizeof(f_data));
	int fileNr = 0;
	HANDLE hSearch = FindFirstFile(wsPath.data(), &f_data);
	while (hSearch != INVALID_HANDLE_VALUE)
	{
		//make sure it is <number>.lyr
		wstring wsFileName = f_data.cFileName;
		wsFileName = wsFileName.erase(wsFileName.length() - 4, 4);
		fileNr = _wtoi(wsFileName.c_str());
		if (fileNr == 0) {FindNextFile(hSearch, &f_data); continue;}
		//we open the file:
		wstring sfn = wsPath2;
		sfn += '\\';
		sfn += f_data.cFileName;
		HANDLE hFile = CreateFile(sfn.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		if (hFile == INVALID_HANDLE_VALUE) 
		{
			sprintf_s(strError, 30, "Error 0x%x has occured.", GetLastError());
			MessageBoxA(genDll.m_hWinamp, strError, "Error!", MB_ICONERROR);
#ifdef _DEBUG
			DebugBreak();
#endif
			bResult = FindNextFile(hSearch, &f_data);
			if (bResult == 0 && GetLastError() == ERROR_NO_MORE_FILES) break;
			continue;
		}

		//we read the content
		char song[30] = "", artist[30] = "", album[30] = "", sLyr[3] = "";
		DWORD dwRead;
		ReadFile(hFile, sLyr, 3, &dwRead, 0);
		if (sLyr[0] != 'L' && sLyr[1] != 'Y' && sLyr[2] != 'R')
		{
			CloseHandle(hFile);
			bResult = FindNextFile(hSearch, &f_data);
			if (bResult == 0 && GetLastError() == ERROR_NO_MORE_FILES) break;
			continue;
		}

		ReadFile(hFile, artist, 30, &dwRead, 0);
		ReadFile(hFile, album, 30, &dwRead, 0);
		ReadFile(hFile, song, 30, &dwRead, 0);
		//now, how to check: first, song name: both must have it. check non-case sensitive.
		if (_stricmp(song, sSong) != 0)
		{
			CloseHandle(hFile);
			bResult = FindNextFile(hSearch, &f_data);
			if (bResult == 0 && GetLastError() == ERROR_NO_MORE_FILES) break;
			continue;
		}
		//otherwise, at least album or artist must exist and differ.
		bool art_dif = false, alb_dif = false;
		if (strlen(artist) == 0 || strlen(sArtist) == 0) art_dif = true;
		if (strlen(album) == 0 || strlen(sAlbum) == 0) alb_dif = true;

		if (!art_dif && !alb_dif)
		{
			string mesaj = "Un fișier de versuri cu același nume de melodie există deja.\n";
			if (strlen(artist)) {mesaj += "Numele artistului: "; mesaj += artist; mesaj += '\n';}
			if (strlen(album)) {mesaj += "Numele albumului: "; mesaj += album; mesaj += '\n';}
			mesaj += "Vrei să îl înlocuiești?";
			int nResult = MessageBoxA(hDlg, mesaj.data(), "Versuri deja existente", MB_ICONINFORMATION | MB_YESNO);
			CloseHandle(hFile);
			if (nResult == IDYES)
			{
				fileNr--;
				break;
			}
			else return INVALID_HANDLE_VALUE;
		}
		CloseHandle(hFile);

		bResult = FindNextFile(hSearch, &f_data);
		if (bResult == 0 && GetLastError() == ERROR_NO_MORE_FILES) break;
	}
	FindClose(hSearch);

	fileNr++;
	wchar_t file_name[10];
	_itow_s(fileNr, file_name, 10, 10);
	wsPath2 += L"\\";
	wsPath2 += file_name;
	wsPath2 += L".lyr";

	//we create the file
	HANDLE hNewFile = CreateFile(wsPath2.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwWritten;
	WriteFile(hNewFile, "LYR", 3, &dwWritten, 0);
	WriteFile(hNewFile, sArtist, 30, &dwWritten, 0);
	WriteFile(hNewFile, sAlbum, 30, &dwWritten, 0);
	WriteFile(hNewFile, sSong, 30, &dwWritten, 0);

	return hNewFile;
}