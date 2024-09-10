/*
** Entry point
**
*/
int SkinInstallerMain(LPWSTR lpCmdLine)
{
	// Avoid loading a dll from current directory
	SetDllDirectory(L"");

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	InitCommonControls();

	if (lpCmdLine[0] == L'"')
	{
		// Strip quotes
		++lpCmdLine;
		WCHAR* pos = wcsrchr(lpCmdLine, L'"');
		if (pos)
		{
			*pos = L'\0';
		}
	}

	WCHAR buffer[MAX_PATH];
	GetModuleFileName(GetInstanceHandle(), buffer, MAX_PATH);

	// Remove the module's name from the path
	WCHAR* pos = wcsrchr(buffer, L'\\');
	if (pos)
	{
		*(pos + 1) = L'\0';
	}

	g_Data.programPath = g_Data.settingsPath = buffer;
	wcscat(buffer, L"Rainmeter.ini");

	// Find the settings file and read skins path off it
	if (_waccess(buffer, 0) == 0)
	{
		g_Data.iniFile = buffer;
		if (GetPrivateProfileString(L"Rainmeter", L"SkinPath", L"", buffer, MAX_LINE_LENGTH, buffer) > 0)
		{
			g_Data.skinsPath = buffer;
			if (g_Data.skinsPath.back() != L'\\' && g_Data.skinsPath.back() != L'/')
			{
				g_Data.skinsPath += L'\\';
			}
		}
		else
		{
			g_Data.skinsPath = g_Data.programPath;
			g_Data.skinsPath += L"Skins\\";
		}
	}
	else
	{
		HRESULT hr = SHGetFolderPath(nullptr, CSIDL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, buffer);
		wcscat(buffer, L"\\Rainmeter\\");
		g_Data.settingsPath = buffer;
		wcscat(buffer, L"Rainmeter.ini");
		g_Data.iniFile = buffer;
		if (SUCCEEDED(hr) && _waccess(buffer, 0) == 0)
		{
			if (GetPrivateProfileString(L"Rainmeter", L"SkinPath", L"", buffer, MAX_LINE_LENGTH, buffer) > 0)
			{
				g_Data.skinsPath = buffer;
				if (g_Data.skinsPath.back() != L'\\' && g_Data.skinsPath.back() != L'/')
				{
					g_Data.skinsPath += L'\\';
				}
			}
			else
			{
				std::wstring error = L"SkinPath not found.\nMake sure that Rainmeter has been run at least once.";
				MessageBox(nullptr, error.c_str(), L"Rainmeter Skin Installer", MB_ERROR);
				return 1;
			}
		}
		else
		{
			std::wstring error = L"Rainmeter.ini not found.\nMake sure that Rainmeter has been run at least once.";
			MessageBox(nullptr, error.c_str(), L"Rainmeter Skin Installer", MB_ERROR);
			return 1;
		}
	}

	std::wstring layoutsPath = g_Data.settingsPath + L"Layouts\\";
	if (_waccess(layoutsPath.c_str(), 0) == -1)
	{
		// Migrate Themes into Layouts for backwards compatibility and rename
		// Rainmeter.thm to Rainmeter.ini and RainThemes.bmp to Wallpaper.bmp.
		std::wstring themesPath = g_Data.settingsPath + L"Themes";
		if (_waccess(themesPath.c_str(), 0) != -1)
		{
			// Migrate Themes into Layouts for backwards compatibility and rename
			// Rainmeter.thm to Rainmeter.ini and RainThemes.bmp to Wallpaper.bmp.
			MoveFile(themesPath.c_str(), layoutsPath.c_str());

			layoutsPath += L'*';  // For FindFirstFile.
			WIN32_FIND_DATA fd;
			HANDLE hFind = FindFirstFile(layoutsPath.c_str(), &fd);
			layoutsPath.pop_back();  // Remove '*'.

			if (hFind != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
						wcscmp(L".", fd.cFileName) != 0 &&
						wcscmp(L"..", fd.cFileName) != 0)
					{
						std::wstring layoutFolder = layoutsPath + fd.cFileName;
						layoutFolder += L'\\';

						std::wstring file = layoutFolder + L"Rainmeter.thm";
						if (_waccess(file.c_str(), 0) != -1)
						{
							std::wstring newFile = layoutFolder + L"Rainmeter.ini";
							MoveFile(file.c_str(), newFile.c_str());
						}

						file = layoutFolder + L"RainThemes.bmp";
						if (_waccess(file.c_str(), 0) != -1)
						{
							std::wstring newFile = layoutFolder + L"Wallpaper.bmp";
							MoveFile(file.c_str(), newFile.c_str());
						}
					}
				}
				while (FindNextFile(hFind, &fd));

				FindClose(hFind);
			}
		}
	}

	if (_wcsnicmp(lpCmdLine, L"/LoadTheme ", 11) == 0)
	{
		// For backwards compatibility.
		std::wstring args = L"!LoadLayout \"";
		args += &lpCmdLine[11];  // Skip "/LoadTheme ".
		args += L'"';

		std::wstring file = g_Data.programPath + L"Rainmeter.exe";
		SHELLEXECUTEINFO sei = {0};
		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.fMask = SEE_MASK_UNICODE;
		sei.lpFile = file.c_str();
		sei.lpParameters = args.c_str();
		sei.lpDirectory = g_Data.programPath.c_str();
		sei.nShow = SW_SHOWNORMAL;
		ShellExecuteEx(&sei);

		return 0;
	}
	else if (wcscmp(lpCmdLine, L"/Packager") == 0)
	{
		DialogPackage::Create(GetInstanceHandle(), lpCmdLine);
	}
	else
	{
		DialogInstall::Create(GetInstanceHandle(), lpCmdLine);
	}

	return 0;
}