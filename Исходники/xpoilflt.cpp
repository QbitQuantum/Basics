BOOL PluginOILFilter::GetImportFile(CCLexFile* pFile, CCLexFile** ppNewFile)
{
	ERROR2IF(pFile == NULL, FALSE,"PluginOILFilter::GetImportFile no file to import from");
	ERROR2IF(ppNewFile == NULL, FALSE,"PluginOILFilter::GetImportFile no newfile pointer");

	*ppNewFile = NULL;

	// Here we should really run the plugin asynchronously with the following options
	// -i -g -f <filename>

	// Redirect stdout to a CCLexFile
	// Check stderr during the Xar import and abort if an error is reported

	m_TempXarFile.SetPathName(_T("/tmp/xpftemp.xar"));

	CCDiskFile TempFile;
	if (!TempFile.open(m_TempXarFile, ios::out | ios::trunc | ios::binary))
	{
		// report an error here
		return FALSE;
	}

	PathName FileName = pFile->GetPathName();

	wxString sCommand(m_DoImport);
	sCommand.Replace(_T("%IN%"), (LPCTSTR)FileName.GetPath());

	TRACEUSER("Gerry", _T("Running '%s'"), sCommand.c_str());

	// Create a process with the TempFile as the stdout
	PluginFilterProcess* pTheProc = new PluginFilterProcess((PluginNativeFilter*)Parent, NULL, &TempFile);

	INT32 code = pTheProc->Execute(sCommand);
	TempFile.close();
	if (code != 0)
	{
		TRACEUSER("Gerry", _T("Execution of '%s' failed."), sCommand.c_str());
		// Extract error from a derived CamProcess class and report it
		pTheProc->ReportError();
		delete pTheProc;
		return(FALSE);
	}

	pTheProc->ReportWarning();
	delete pTheProc;
	pTheProc = NULL;

	CCDiskFile* pTempFile = new CCDiskFile();
	if (pTempFile)
	{
		if (pTempFile->open(m_TempXarFile, ios::in | ios::binary))
		{
			*ppNewFile = pTempFile;
			return(TRUE);
		}

		delete pTempFile;
	}

	return(FALSE);
}