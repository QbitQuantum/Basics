bool FileSystemManager::getShortcutTarget(QString shortcutFileName, QString * targetOut, QString * argsOut, QString * workingDirOut)
{
	assert(targetOut);

	// return true if _any_ of the attributes can be resolved

	bool targetResolved = false;
	bool result = false;
	IShellLink * psl = NULL; 

	// Accounting for the newer "Advertised Shortcuts" which refer to MSI operations which may pre-empt the 
	// launching of the specified shortcut
	DWORD targetPathLen = MAX_PATH;
	TCHAR targetPath[MAX_PATH];
	TCHAR productCode[MAX_PATH];
	TCHAR featureId[MAX_PATH];
	TCHAR componentCode[MAX_PATH];
	if (pfnMsiGetShortcutTarget && pfnMsiGetComponentPath)
	{
		if (ERROR_SUCCESS == pfnMsiGetShortcutTarget((LPCTSTR) shortcutFileName.utf16(), productCode, featureId, componentCode)) 
		{
			if (INSTALLSTATE_LOCAL == pfnMsiGetComponentPath(productCode, componentCode, targetPath, &targetPathLen))
			{
				*targetOut = QString::fromUtf16((const ushort *) targetPath);
				targetResolved = true;
				result = true;
			}
		}
	}

	// Get a pointer to the IShellLink interface. 
	TCHAR args[MAX_PATH];
	TCHAR workingDir[MAX_PATH];

	HRESULT hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl); 
	if (SUCCEEDED(hres)) 
	{ 
		IPersistFile * ppf = NULL; 

		// Get a pointer to the IPersistFile interface. 
		if (SUCCEEDED(psl->QueryInterface(IID_IPersistFile, (LPVOID *) &ppf))) 
		{ 
			// Load the shortcut. 
			if (SUCCEEDED(ppf->Load((LPCOLESTR) shortcutFileName.utf16(), STGM_READ))) 
			{ 
				// Resolve the link. 
				if (SUCCEEDED(psl->Resolve(winOS->GetWindowsHandle(), SLR_NOUPDATE | SLR_NO_UI))) 
				{ 
					// Get the path to the link target. 
					if (!targetResolved && SUCCEEDED(psl->GetPath(targetPath, MAX_PATH, NULL, 0))) 
					{
						*targetOut = QString::fromUtf16((const ushort *) targetPath);
						result = true;
					}
					if (argsOut && SUCCEEDED(psl->GetArguments(args, MAX_PATH)))
					{
						*argsOut = QString::fromUtf16((const ushort *) args);
						result = true;
					}
					if (workingDirOut && SUCCEEDED(psl->GetWorkingDirectory(workingDir, MAX_PATH)))
					{
						*workingDirOut = QString::fromUtf16((const ushort *) workingDir);
						result = true;
					}
				} 
			} 

			// Release the pointer to the IPersistFile interface. 
			ppf->Release(); 
		} 

		// Release the pointer to the IShellLink interface. 
		psl->Release(); 
	} 
	return result;
}