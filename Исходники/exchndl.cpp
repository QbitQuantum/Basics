void ExchndlSetup(const char *packageVersion)
{
# if defined(WZ_CC_MINGW)
	wchar_t miniDumpPath[PATH_MAX] = {'\0'};
	DWORD dwRetVal = 0;
#ifdef HAVE_BFD
	bfd_init();
#endif /* HAVE_BFD */

	// Install the unhandled exception filter function
	prevExceptionFilter = SetUnhandledExceptionFilter(TopLevelExceptionFilter);

	// Retrieve the current version
	formattedVersionString = strdup(packageVersion);
#ifndef WZ_PORTABLE
	// Because of UAC on vista / win7 we use this to write our dumps to (unless we override it via OverrideRPTDirectory())
	// NOTE: CSIDL_PERSONAL =  C:\Users\user name\Documents
	if ( SUCCEEDED( SHGetFolderPathW( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, miniDumpPath ) ))
	{
		PathAppendW( miniDumpPath, WSTRING(WZ_WRITEDIR));
		PathAppendW( miniDumpPath, L"\\logs" );

		if( !PathFileExistsW( miniDumpPath ) )
		{
			if( ERROR_SUCCESS != SHCreateDirectoryExW( NULL, miniDumpPath, NULL ) )
			{
				//last attempt to get a path
				dwRetVal = GetTempPathW(PATH_MAX, miniDumpPath);
				if (dwRetVal > MAX_PATH || (dwRetVal == 0))
				{
					MessageBox((HWND)MB_ICONEXCLAMATION, "Could not created a temporary directory!\nProgram will now exit." , _T("Error"), MB_OK);
					exit(1);
				}
			}
		}
	}
#else
	// we use where they installed it on, since this is a removeable drive (most likely), we will use where the program is located in.
	if (dwRetVal = GetCurrentDirectoryW(MAX_PATH, miniDumpPath))
	{
		if(dwRetVal > MAX_PATH)
		{
			MessageBox((HWND)MB_ICONEXCLAMATION, "Buffer exceeds maximum path to create directory.  Exiting.", _T("Error"), MB_OK);
			exit(1);
		}
		PathAppendW( miniDumpPath, WSTRING(WZ_WRITEDIR));
		PathAppendW( miniDumpPath, L"\\logs" );
	}
#endif
	else
	{	// should never fail, but if it does, we fall back to this
		dwRetVal = GetTempPathW(PATH_MAX, miniDumpPath);
		if (dwRetVal > MAX_PATH || (dwRetVal == 0))
		{
			MessageBox((HWND)MB_ICONEXCLAMATION, "Could not created a temporary directory!\nProgram will now exit." , _T("Error!"), MB_OK);
			exit(1);
		}
	}

	wcscat(szLogFileName, L"Warzone2100.RPT");
	wcscat(miniDumpPath, L"\\");
	wcscat(miniDumpPath,szLogFileName);
	wcscpy(szLogFileName, miniDumpPath);

	atexit(ExchndlShutdown);
#endif
}