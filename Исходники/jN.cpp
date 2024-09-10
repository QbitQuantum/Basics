void loadInitScript(){

	TCHAR scriptfile[MAX_PATH];

	GetModuleFileName(Statics::instance().hInstance, scriptfile, MAX_PATH);
	
	BOOL res = PathRemoveFileSpec((LPWSTR)scriptfile);
	PathAppend((LPWSTR)scriptfile, START_SCRIPT_FILE_NAME); 

	if (PathFileExists(scriptfile)== TRUE){

		HANDLE hFile = CreateFile(
			scriptfile, // name of the write
			GENERIC_READ,			// open for writing
			0,                      // do not share
			NULL,                   // default security
			OPEN_ALWAYS,			// overwrite existing
			FILE_ATTRIBUTE_NORMAL,  // normal file
			NULL
		);                  // no attr. template

		if (hFile == INVALID_HANDLE_VALUE) 
		{ 
			::MessageBox(0,TEXT("Could not open file (error %d)\n"),TEXT("Error"), MB_OK);
			return;
		}

		char* buf = NULL;
		DWORD fSize, fRead;
		fSize = GetFileSize(hFile, NULL);

		if (fSize == INVALID_FILE_SIZE){
			::MessageBox(0,TEXT("Could not open file (error %d)\n"),TEXT("Error"), MB_OK);
			CloseHandle(hFile);
			return;
		}

		buf = new char[fSize+1]; 
		buf[fSize] = 0;

		ReadFile(hFile, buf, fSize,& fRead, NULL);
		CloseHandle(hFile);


		// assume file is UTF8 encoded
		int newlen = MultiByteToWideChar(CP_UTF8, 0, buf, fSize, NULL,0);
		BSTR wbuf = SysAllocStringLen(NULL, newlen);
		int res = MultiByteToWideChar(CP_UTF8, 0, buf, fSize, wbuf, newlen);

		if (buf!=NULL)	
		  delete[] buf;

		g_editor = new CEditor(nppData._nppHandle);
		LocRef<System> system = new System(scriptfile, *MyActiveSite::getInstance());

		MyActiveSite::getInstance()->addNamedItem(TEXT("Editor"), static_cast<IUnknown*>(g_editor));
		MyActiveSite::getInstance()->addNamedItem(TEXT("System"), static_cast<IUnknown*>(system));

		MyActiveSite::getInstance()->Connect();

		MyActiveSite::getInstance()->runScript(wbuf, scriptfile);

		SysFreeString(wbuf);
	}
}