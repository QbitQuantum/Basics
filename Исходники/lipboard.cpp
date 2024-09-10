void Clipboard::CopyToClipboard(HWND h)
{
	if ( !OpenClipboard(h) )
	{
		MessageBox(NULL,  "Cannot open the Clipboard", "Error", MB_OK);
		return;
	}
	// Remove the current Clipboard contents
	if( !EmptyClipboard() )
	{
		MessageBox(NULL, "Cannot empty the Clipboard", "Error", MB_OK);
		return;
	}
	// ...
	// Get the currently selected data

/*************
	INCCRunTimeEnvironment::tEnvInfo info;
	GetEnvironmentInfoList(info);
	int tlen = 0;
	int i;


	const int ic = eMAXPATHCFGNAMES/2 + eMAXAPPINFONAMES;

	PTCHAR *foo = new PTCHAR[ic];
	for (i = 0; i < ic; i++)
	{
		foo[i] = new TCHAR[512];
		foo[i][0] = 0;
	}

	for (i = 0; i < (eMAXPATHCFGNAMES/2); i++)
	{
		sprintf(foo[i],"%s\t\t%s\t\t%s\t\t%s\r\n",
			info.pIniFile->m_Entry[i].name, 
			info.pIniFile->m_Entry[i].iniValue,  
			info.pIniFile->m_Entry[i].defIniValue,  
			info.pIniFile->m_Entry[i].szDesc);
		tlen += strlen(foo[i]);
	}
	for (i = 0; i < (eMAXAPPINFONAMES); i++)
	{
		sprintf(foo[i + (eMAXPATHCFGNAMES/2)],"%s\t\t%s\t\t%s\t\t%s\r\n",
			info.info[i].name, 
			info.info[i].iniValue,  
			info.info[i].defIniValue,  
			info.info[i].szDesc);    
		tlen += strlen(foo[i]);
	}



	// Allocate a global memory object for the text. 
	LPTSTR  lptstrCopy; 
	HGLOBAL hglbCopy; 
	hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (tlen + 1) * sizeof(TCHAR)); 
	if (hglbCopy == NULL) 
	{ 
		goto cleanup;
	} 

	// Lock the handle and copy the text to the buffer. 
	lptstrCopy = (LPSTR)GlobalLock(hglbCopy);
	lptstrCopy[0] = (TCHAR) 0;    // null character 
	for (i = 0; i < ic; i++)
	{
		LPSTR b = foo[i];
		size_t l = strlen(b);
		strncat(lptstrCopy, b, l);
	}
	lptstrCopy[tlen] = (TCHAR) 0;    // null character 
	GlobalUnlock(hglbCopy); 

	// Place the handle on the clipboard. 

	// For the appropriate data formats...
	if ( ::SetClipboardData( CF_TEXT, hglbCopy ) == NULL )
	{
		MessageBox(NULL, "Unable to set Clipboard data", "Error", MB_OK);
		goto cleanup;
	}

cleanup:
	CloseClipboard();

	for (i = 0; i < ic; i++)
	{
		delete [] foo[i];
	}
	delete [] foo;
		*/
}