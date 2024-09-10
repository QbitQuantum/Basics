void main()
{
	DWORD   dwVersion;
	HRESULT hr;
	time_t	ttime;
	BOOL 	fOleInitialized = FALSE;
	char	ch;

	if (0 != fopen_s( &g_fpLogFile,"sampclnt.out", "at"))
	{
		DumpErrorMsg( "Warning: cannot open log file sampclnt.out\n" );
		goto error;
	}
  
  	time(&ttime);
    
    DumpStatusMsg( "\n-------------------------\n\n");

	char buf[26];
	ctime_s(buf,26,&ttime);
    DumpStatusMsg( "running sampclnt.exe\n%s\n\n",buf);

	dwVersion = OleBuildVersion();
	if (HIWORD(dwVersion) != rmm)
	{
		DumpErrorMsg( "Error: OLE version mismatch. Build version %ld, current version %ld\n",
			rmm, HIWORD(dwVersion) );
		goto error;    
	}

	hr = OleInitialize( NULL );
	if (FAILED(hr))
	{
		DUMP_ERROR_LINENUMBER();
		DumpErrorMsg("Error: OleInitialize failed\n");
		goto error;
	}
	fOleInitialized = TRUE;

	hr = CoGetMalloc( MEMCTX_TASK, &g_pIMalloc );
	if (FAILED(hr))
	{
		DUMP_ERROR_LINENUMBER();
		DumpErrorMsg("Error: CoGetMalloc failed\n");
		goto error;
	}

	hr = DoTests();
	if (FAILED(hr))
	{
		DUMP_ERROR_LINENUMBER();
		DumpErrorHResult( hr, "DoTests");
		goto error;
	}

    g_pIMalloc->Release();
	OleUninitialize();

	if (g_fpLogFile)
    	fclose(g_fpLogFile);

	/* Pause before we quit, in case user ran from an icon, so they can see our messages. */
	printf("\n\n>>> Output has gone into 'sampclnt.out'.");
	printf("\n>>> You may wish to use a wide-column editor to view this file.\n\n");
	printf("<press any key to continue>");
	ch = _getch();
	return;
    
error:
    if (g_pIMalloc)
    	g_pIMalloc->Release();    
	if (fOleInitialized)
    	OleUninitialize();
	if (g_fpLogFile)
    	fclose(g_fpLogFile);
	
	/* Pause before we quit, in case user ran from an icon, so they can see our messages. */
	printf("\n\n>>> Output has gone into 'sampclnt.out'.");
	printf("\n>>> You may wish to use a wide-column editor to view this file.\n\n");
	printf("<press any key to continue>");
	ch = _getch();

	return;    
}    