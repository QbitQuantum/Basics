	void IntroDialog::InstallLocationClicked()
	{
		BROWSEINFO bi = { 0 };
		bi.lpszTitle =  (LPCWSTR) L"Pick installation directory";
		LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
		if (pidl != 0)
		{
			TCHAR pathW[MAX_PATH];
			if (SHGetPathFromIDList(pidl, pathW))
			{
				std::string path = KrollUtils::WideToUTF8(pathW);
				appInstallPath = FileUtils::Join(path.c_str(), app->name.c_str(), NULL);
				std::wstring wideAppInstallPath = KrollUtils::UTF8ToWide(appInstallPath);
				SendMessage(installLocationText, WM_SETTEXT, 0, (LPARAM) wideAppInstallPath.c_str());
			}

			IMalloc * imalloc = 0;
			if (SUCCEEDED(SHGetMalloc(&imalloc)))
			{
				imalloc->Free(pidl);
				imalloc->Release();
			}

		}
	}