void PerformUpdateCheck(HWND hDlg)
{
	TCHAR TempPath[MAX_PATH];
	DWORD PathRes = GetTempPath(SIZEOF_ARRAY(TempPath),TempPath);

	if(PathRes == 0)
	{
		PostMessage(hDlg,CUpdateCheckDialog::WM_APP_UPDATE_CHECK_COMPLETE,
			CUpdateCheckDialog::UPDATE_CHECK_ERROR,0);
		return;
	}

	TCHAR TempFileName[MAX_PATH];
	UINT FileRes = GetTempFileName(TempPath,_T("exp"),0,TempFileName);

	if(FileRes == 0)
	{
		PostMessage(hDlg,CUpdateCheckDialog::WM_APP_UPDATE_CHECK_COMPLETE,
			CUpdateCheckDialog::UPDATE_CHECK_ERROR,0);
		return;
	}

	bool VersionRetrieved = false;

	/* Not that any cached version of this file
	will be deleted first. This ensures that the
	version check is not performed against an
	outdated file. */
	DeleteUrlCacheEntry(CUpdateCheckDialog::VERSION_FILE_URL);
	HRESULT hr = URLDownloadToFile(NULL,CUpdateCheckDialog::VERSION_FILE_URL,TempFileName,0,NULL);

	if(SUCCEEDED(hr))
	{
		HANDLE hFile = CreateFile(TempFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);

		if(hFile != INVALID_HANDLE_VALUE)
		{
			char VersionNumber[16];
			DWORD NumBytesRead;
			BOOL ReadRes = ReadFile(hFile,VersionNumber,sizeof(VersionNumber) - 1,&NumBytesRead,NULL);

			if(ReadRes && NumBytesRead > 0)
			{
				VersionNumber[NumBytesRead] = '\0';

				std::string VersionNumberString(VersionNumber);
				std::vector<std::string> VersionNumberComponents;
				boost::split(VersionNumberComponents,VersionNumberString,boost::is_any_of("."));

				try
				{
					CUpdateCheckDialog::Version_t Version;
					Version.MajorVersion = boost::lexical_cast<int>(VersionNumberComponents.at(0));
					Version.MinorVersion = boost::lexical_cast<int>(VersionNumberComponents.at(1));
					Version.MicroVersion = boost::lexical_cast<int>(VersionNumberComponents.at(2));
					MultiByteToWideChar(CP_ACP,0,VersionNumber,-1,Version.VersionString,SIZEOF_ARRAY(Version.VersionString));

					SendMessage(hDlg,CUpdateCheckDialog::WM_APP_UPDATE_CHECK_COMPLETE,
						CUpdateCheckDialog::UPDATE_CHECK_SUCCESS,reinterpret_cast<LPARAM>(&Version));

					VersionRetrieved = true;
				}
				catch(std::out_of_range)
				{
					/* VersionRetrieved won't be set, so an error
					will be returned below. Nothing needs to be done
					here. */
				}
			}

			CloseHandle(hFile);
		}
	}

	if(!VersionRetrieved)
	{
		PostMessage(hDlg,CUpdateCheckDialog::WM_APP_UPDATE_CHECK_COMPLETE,
			CUpdateCheckDialog::UPDATE_CHECK_ERROR,0);
	}

	DeleteFile(TempFileName);
}