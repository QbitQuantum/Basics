void CheckVersion(void* dummy)
{
	HINTERNET hRootHandle = InternetOpen(
		L"Rainmeter",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);

	if (hRootHandle == NULL)
	{
		return;
	}

	HINTERNET hUrlDump = InternetOpenUrl(hRootHandle, L"http://rainmeter.github.io/rainmeter/release", NULL, NULL, INTERNET_FLAG_RESYNCHRONIZE, 0);
	if (hUrlDump)
	{
		DWORD dwSize;
		char urlData[16] = {0};
		if (InternetReadFile(hUrlDump, (LPVOID)urlData, sizeof(urlData) - 1, &dwSize))
		{
			auto parseVersion = [](const WCHAR* str)->int
			{
				int version = _wtoi(str) * 1000000;
				const WCHAR* pos = wcschr(str, L'.');
				if (pos)
				{
					++pos;	// Skip .
					version += _wtoi(pos) * 1000;

					pos = wcschr(pos, '.');
					if (pos)
					{
						++pos;	// Skip .
						version += _wtoi(pos);
					}
				}
				return version;
			};

			std::wstring tmpSz = StringUtil::Widen(urlData);
			const WCHAR* version = tmpSz.c_str();

			int availableVersion = parseVersion(version);
			if (availableVersion > RAINMETER_VERSION ||
				(revision_beta && availableVersion == RAINMETER_VERSION))
			{
				Rainmeter->SetNewVersion();

				WCHAR buffer[32];
				const WCHAR* dataFile = Rainmeter->GetDataFile().c_str();
				GetPrivateProfileString(L"Rainmeter", L"LastCheck", L"0", buffer, _countof(buffer), dataFile);

				// Show tray notification only once per new version
				int lastVersion = parseVersion(buffer);
				if (availableVersion > lastVersion)
				{
					Rainmeter->GetTrayWindow()->ShowUpdateNotification(version);
					WritePrivateProfileString(L"Rainmeter", L"LastCheck", version, dataFile);
				}
			}
		}
		InternetCloseHandle(hUrlDump);
	}

	InternetCloseHandle(hRootHandle);
}