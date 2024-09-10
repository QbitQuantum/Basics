// Downloads file from the net
unsigned __stdcall NetworkDownloadThreadProc(void* pParam)
{
	MeasureData* measure = (MeasureData*)pParam;
	const bool download = !measure->downloadFile.empty();
	bool ready = false;

	std::wstring url;

	if (measure->regExp.empty() && measure->resultString.empty())
	{
		if (!measure->url.empty() && measure->url[0] != L'[')
		{
			url = measure->url;
		}
	}
	else
	{
		EnterCriticalSection(&g_CriticalSection);
		url = measure->resultString;
		LeaveCriticalSection(&g_CriticalSection);

		std::wstring::size_type pos = url.find(L':');
		if (pos == std::wstring::npos && !url.empty())	// No protocol
		{
			// Add the base url to the string
			if (url[0] == L'/')
			{
				// Absolute path
				pos = measure->url.find(L'/', 7);	// Assume "http://" (=7)
				if (pos != std::wstring::npos)
				{
					std::wstring path(measure->url.substr(0, pos));
					url = path + url;
				}
			}
			else
			{
				// Relative path

				pos = measure->url.rfind(L'/');
				if (pos != std::wstring::npos)
				{
					std::wstring path(measure->url.substr(0, pos + 1));
					url = path + url;
				}
			}
		}
	}

	if (!url.empty())
	{
		// Create the filename
		WCHAR buffer[MAX_PATH] = {0};
		std::wstring fullpath, directory;

		if (download)  // download mode
		{
			PathCanonicalize(buffer, measure->downloadFile.c_str());

			std::wstring path = buffer;
			std::wstring::size_type pos = path.find_first_not_of(L'\\');
			if (pos != std::wstring::npos)
			{
				path.erase(0, pos);
			}

			PathCanonicalize(buffer, measure->downloadFolder.c_str());
			CreateDirectory(buffer, nullptr);	// Make sure that the folder exists

			wcscat(buffer, path.c_str());

			if (buffer[wcslen(buffer)-1] != L'\\')  // path is a file
			{
				fullpath = buffer;
				PathRemoveFileSpec(buffer);
			}
			PathAddBackslash(buffer);
		}
		else  // cache mode
		{
			GetTempPath(MAX_PATH, buffer);
			wcscat(buffer, L"Rainmeter-Cache\\");  // "%TEMP%\Rainmeter-Cache\"
		}
		CreateDirectory(buffer, nullptr);	// Make sure that the folder exists
		directory = buffer;

		if (fullpath.empty())
		{
			fullpath = directory;

			std::wstring::size_type pos2 = url.find_first_of(L"?#");
			std::wstring::size_type pos1 = url.find_last_of(L'/', pos2);
			pos1 = (pos1 != std::wstring::npos) ? pos1 + 1 : 0;

			std::wstring name;
			if (pos2 != std::wstring::npos)
			{
				name.assign(url, pos1, pos2 - pos1);
			}
			else
			{
				name.assign(url, pos1, url.length() - pos1);
			}

			if (!name.empty())
			{
				// Replace reserved characters to "_"
				pos1 = 0;
				while ((pos1 = name.find_first_of(L"\\/:*?\"<>|", pos1)) != std::wstring::npos)
				{
					name[pos1] = L'_';
				}
				fullpath += name;
			}
			else
			{
				fullpath += L"index";
			}
		}

		ready = true;

		if (download)  // download mode
		{
			if (!PathFileExists(directory.c_str()) || !PathIsDirectory(directory.c_str()))
			{
				ready = false;
				RmLogF(
					measure->rm, LOG_ERROR,
					L"WebParser: Directory does not exist: %s", directory.c_str());
			}
			else if (PathIsDirectory(fullpath.c_str()))
			{
				ready = false;
				RmLogF(
					measure->rm, LOG_ERROR,
					L"WebParser: Path is a directory, not a file: %s", fullpath.c_str());
			}
			else if (PathFileExists(fullpath.c_str()))
			{
				DWORD attr = GetFileAttributes(fullpath.c_str());
				if (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_READONLY))
				{
					ready = false;
					RmLogF(
						measure->rm, LOG_ERROR,
						L"WebParser: File is read-only: %s", fullpath.c_str());
				}
			}
		}
		else  // cache mode
		{
			EnterCriticalSection(&g_CriticalSection);

			if (PathFileExists(fullpath.c_str()))
			{
				std::wstring::size_type pos = fullpath.find_last_of(L'.');

				std::wstring path, ext;
				if (pos != std::wstring::npos)
				{
					path.assign(fullpath, 0, pos);
					ext.assign(fullpath, pos, fullpath.length() - pos);
				}
				else
				{
					path = fullpath;
				}

				// Assign a serial number
				int i = 1;
				do
				{
					wsprintf(buffer, L"_%i", i++);

					fullpath = path;
					fullpath += buffer;
					if (!ext.empty())
					{
						fullpath += ext;
					}
				} while (PathFileExists(fullpath.c_str()));
			}

			// Create empty file
			HANDLE hFile = CreateFile(fullpath.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

			LeaveCriticalSection(&g_CriticalSection);
		}

		if (ready)
		{
			// Delete IE cache before download if "SyncMode5" is not 3 (every visit to the page)
			{
				// Check "Temporary Internet Files" sync mode (SyncMode5)
				// Values:
				//   Every visit to the page                 3
				//   Every time you start Internet Explorer  2
				//   Automatically (default)                 4
				//   Never                                   0
				// http://support.microsoft.com/kb/263070/en

				HKEY hKey;
				LONG ret;
				DWORD mode;

				ret = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", 0, KEY_QUERY_VALUE, &hKey);
				if (ret == ERROR_SUCCESS)
				{
					DWORD size = sizeof(mode);
					ret = RegQueryValueEx(hKey, L"SyncMode5", nullptr, nullptr, (LPBYTE)&mode, &size);
					RegCloseKey(hKey);
				}

				if (ret != ERROR_SUCCESS || mode != 3)
				{
					std::wstring::size_type pos = url.find_first_of(L'#');

					if (pos != std::wstring::npos)
					{
						DeleteUrlCacheEntry(url.substr(0, pos).c_str());
					}
					else
					{
						DeleteUrlCacheEntry(url.c_str());
					}
				}
			}

			RmLogF(
				measure->rm, LOG_DEBUG,
				L"WebParser: Downloading url '%s' to: %s", url.c_str(), fullpath.c_str());

			HRESULT resultCoInitialize = CoInitialize(nullptr);  // requires before calling URLDownloadToFile function

			// Download the file
			HRESULT result = URLDownloadToFile(nullptr, url.c_str(), fullpath.c_str(), 0, nullptr);
			if (result == S_OK)
			{
				EnterCriticalSection(&g_CriticalSection);

				if (!download)  // cache mode
				{
					if (!measure->downloadedFile.empty())
					{
						// Delete old downloaded file
						DeleteFile(measure->downloadedFile.c_str());
					}
				}

				// Convert LFN to 8.3 filename if the path contains blank character
				if (fullpath.find_first_of(L' ') != std::wstring::npos)
				{
					DWORD size = GetShortPathName(fullpath.c_str(), buffer, MAX_PATH);
					if (size > 0 && size <= MAX_PATH)
					{
						fullpath = buffer;
					}
				}
				measure->downloadedFile = fullpath;

				LeaveCriticalSection(&g_CriticalSection);

				if (!measure->finishAction.empty())
				{
					RmExecute(measure->skin, measure->finishAction.c_str());
				}
			}
			else
			{
				ready = false;

				if (!download)  // cache mode
				{
					// Delete empty file
					DeleteFile(fullpath.c_str());
				}

				RmLogF(
					measure->rm, LOG_ERROR,
					L"WebParser: Download failed (res=0x%08X, COM=0x%08X): %s",
					result, resultCoInitialize, url.c_str());

				if (!measure->onDownloadErrAction.empty())
				{
					RmExecute(measure->skin, measure->onDownloadErrAction.c_str());
				}
			}

			if (SUCCEEDED(resultCoInitialize))
			{
				CoUninitialize();
			}
		}
		else
		{
			RmLogF(measure->rm, LOG_ERROR, L"WebParser: Download failed: %s", url.c_str());

			if (!measure->onDownloadErrAction.empty())
			{
				RmExecute(measure->skin, measure->onDownloadErrAction.c_str());
			}
		}
	}
	else
	{
		RmLog(measure->rm, LOG_ERROR, L"WebParser: Url is empty");
	}

	if (!ready) // download failed
	{
		EnterCriticalSection(&g_CriticalSection);

		if (!download) // cache mode
		{
			if (!measure->downloadedFile.empty())
			{
				// Delete old downloaded file
				DeleteFile(measure->downloadedFile.c_str());
			}
		}

		// Clear old downloaded filename
		measure->downloadedFile.clear();

		LeaveCriticalSection(&g_CriticalSection);
	}

	EnterCriticalSection(&g_CriticalSection);
	CloseHandle(measure->dlThreadHandle);
	measure->dlThreadHandle = 0;
	LeaveCriticalSection(&g_CriticalSection);

	return 0;   // thread completed successfully
}