    //TODO: 
    //  http://support.microsoft.com/kb/314853
    //  strParam.Format( _T( "/n, \"%s\"" ), szDirPath ); 或 .Format( _T( "/n, /select, \"%s\"" ), szFilePath );
    //  ::ShellExecute( NULL, _T( "open" ), _T( "explorer.exe" ), strParam, NULL, SW_SHOWNORMAL ); 
	HRESULT CFShellUtil::ExplorerToSpecialFile(LPCTSTR pszFilePath)
	{
		HRESULT hr = E_FAIL;

		PIDLIST_RELATIVE pidl = NULL;
		//ULONG attributes = 0;
		SFGAOF sfgaofIn = 0, sfgaofOut = 0;
        CFConversion conv;
		COM_VERIFY(SHParseDisplayName(conv.TCHAR_TO_UTF16(pszFilePath), NULL, &pidl, sfgaofIn, &sfgaofOut));
		if (SUCCEEDED(hr))
		{
			COM_VERIFY(SHOpenFolderAndSelectItems(pidl, 0, NULL, 0));
			//ILFree(pidl);
			CoTaskMemFree(pidl);
			pidl = NULL;
		}
		return hr;
	}