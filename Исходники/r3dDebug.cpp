static LONG WINAPI CreateMiniDump( EXCEPTION_POINTERS* pep ) 
{
	r3dOutToLog("Creating minidump!!\n");

	// Open the file 
	char miniDumpPath[1024];
	if(CreateConfigPath(miniDumpPath))
	{
		strcat( miniDumpPath, "MiniDump.dmp" );
		r3dOutToLog("Minidump path: %s\n", miniDumpPath);

		HANDLE hFile = CreateFile( miniDumpPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
		if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
		{
			// Create the minidump 
			MINIDUMP_EXCEPTION_INFORMATION mdei; 
			mdei.ThreadId           = GetCurrentThreadId(); 
			mdei.ExceptionPointers  = pep; 
			mdei.ClientPointers     = FALSE; 

			MINIDUMP_CALLBACK_INFORMATION mci; 
			mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MyMiniDumpCallback; 
			mci.CallbackParam       = 0; 

			MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory); 

			BOOL rv = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), 
				hFile, mdt, (pep != 0) ? &mdei : 0, 0, &mci ); 

			if( !rv ) 
				r3dOutToLog( "MiniDumpWriteDump failed. Error: %u \n", GetLastError() ); 
			else 
				r3dOutToLog( "Minidump created.\n" ); 

			// Close the file 
			CloseHandle( hFile ); 
		}
		else 
		{
			r3dOutToLog( "CreateFile failed. Error: %u \n", GetLastError() ); 
		}

		r3dOutToLog("\n!!!Crash!!!\nPlease send '%s' to support@localhost\nThank you.", miniDumpPath);
		// hide window, hopefully will work in fullscreen
		ShowWindow(win::hWnd, SW_FORCEMINIMIZE);
		
		// show message box to user
		char tempStr[2048];
		sprintf(tempStr, "Application crashed.\nPlease send '%s' and r3dLog.txt (in install folder of the game) to support@localhost along with description of what you were doing at the time of crash.\nThank you and sorry for inconvenience.", miniDumpPath);
		MessageBox(0, tempStr, "Crash", MB_OK);
	}
	r3dCloseLogFile(); 

	// call WINDOWS ERROR REPORTING, in case if user will not send us crashdump
	LONG lRet = EXCEPTION_CONTINUE_SEARCH;
	lRet = EXCEPTION_EXECUTE_HANDLER;
	return lRet ;
}