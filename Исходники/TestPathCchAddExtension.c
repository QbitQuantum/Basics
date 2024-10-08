int TestPathCchAddExtension(int argc, char* argv[])
{
	HRESULT status;
	TCHAR Path[PATHCCH_MAX_CCH];
	
	/* Path: no extension, Extension: dot */

	_tcscpy(Path, testPathNoExtension);

	status = PathCchAddExtension(Path, PATHCCH_MAX_CCH, testExtDot);
	
	if (status != S_OK)
	{
		_tprintf(_T("PathCchAddExtension status: 0x%08X\n"), status);
		return -1;
	}

	if (_tcscmp(Path, testPathExtension) != 0)
	{
		_tprintf(_T("Path Mismatch: Actual: %s, Expected: %s\n"), Path, testPathExtension);
		return -1;
	}

	/* Path: no extension, Extension: no dot */

	_tcscpy(Path, testPathNoExtension);

	status = PathCchAddExtension(Path, PATHCCH_MAX_CCH, testExtNoDot);
	
	if (status != S_OK)
	{
		_tprintf(_T("PathCchAddExtension status: 0x%08X\n"), status);
		return -1;
	}

	if (_tcscmp(Path, testPathExtension) != 0)
	{
		_tprintf(_T("Path Mismatch: Actual: %s, Expected: %s\n"), Path, testPathExtension);
		return -1;
	}

	/* Path: extension, Extension: dot */

	_tcscpy(Path, testPathExtension);

	status = PathCchAddExtension(Path, PATHCCH_MAX_CCH, testExtDot);
	
	if (status != S_FALSE)
	{
		_tprintf(_T("PathCchAddExtension status: 0x%08X\n"), status);
		return -1;
	}

	if (_tcscmp(Path, testPathExtension) != 0)
	{
		_tprintf(_T("Path Mismatch: Actual: %s, Expected: %s\n"), Path, testPathExtension);
		return -1;
	}

	/* Path: extension, Extension: no dot */

	_tcscpy(Path, testPathExtension);

	status = PathCchAddExtension(Path, PATHCCH_MAX_CCH, testExtDot);
	
	if (status != S_FALSE)
	{
		_tprintf(_T("PathCchAddExtension status: 0x%08X\n"), status);
		return -1;
	}

	if (_tcscmp(Path, testPathExtension) != 0)
	{
		_tprintf(_T("Path Mismatch: Actual: %s, Expected: %s\n"), Path, testPathExtension);
		return -1;
	}

	return 0;
}