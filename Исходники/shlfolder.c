/***********************************************************************
 *	SHELL32_CoCreateInitSF
 *
 * Creates a shell folder and initializes it with a pidl and a root folder
 * via IPersistFolder3 or IPersistFolder.
 *
 * NOTES
 *   pathRoot can be NULL for Folders being a drive.
 *   In this case the absolute path is built from pidlChild (eg. C:)
 */
static HRESULT SHELL32_CoCreateInitSF (LPCITEMIDLIST pidlRoot, LPCWSTR pathRoot,
                LPCITEMIDLIST pidlChild, REFCLSID clsid, LPVOID * ppvOut)
{
    HRESULT hr;

    TRACE ("(%p %s %p %s %p)\n", pidlRoot, debugstr_w(pathRoot), pidlChild, debugstr_guid(clsid), ppvOut);

    hr = SHCoCreateInstance(NULL, clsid, NULL, &IID_IShellFolder, ppvOut);
    if (SUCCEEDED (hr))
    {
	LPITEMIDLIST pidlAbsolute = ILCombine (pidlRoot, pidlChild);
	IPersistFolder *pPF;
	IPersistFolder3 *ppf;

        if (_ILIsFolder(pidlChild) &&
            SUCCEEDED (IUnknown_QueryInterface ((IUnknown *) * ppvOut, &IID_IPersistFolder3, (LPVOID *) & ppf))) 
        {
	    PERSIST_FOLDER_TARGET_INFO ppfti;

	    ZeroMemory (&ppfti, sizeof (ppfti));

	    /* fill the PERSIST_FOLDER_TARGET_INFO */
	    ppfti.dwAttributes = -1;
	    ppfti.csidl = -1;

	    /* build path */
	    if (pathRoot) {
		lstrcpynW (ppfti.szTargetParsingName, pathRoot, MAX_PATH - 1);
		PathAddBackslashW(ppfti.szTargetParsingName); /* FIXME: why have drives a backslash here ? */
	    }

	    if (pidlChild) {
                int len = lstrlenW(ppfti.szTargetParsingName);

		if (!_ILSimpleGetTextW(pidlChild, ppfti.szTargetParsingName + len, MAX_PATH - len))
			hr = E_INVALIDARG;
	    }

	    IPersistFolder3_InitializeEx (ppf, NULL, pidlAbsolute, &ppfti);
	    IPersistFolder3_Release (ppf);
	}
	else if (SUCCEEDED ((hr = IUnknown_QueryInterface ((IUnknown *) * ppvOut, &IID_IPersistFolder, (LPVOID *) & pPF)))) {
	    IPersistFolder_Initialize (pPF, pidlAbsolute);
	    IPersistFolder_Release (pPF);
	}
	ILFree (pidlAbsolute);
    }
    TRACE ("-- (%p) ret=0x%08x\n", *ppvOut, hr);
    return hr;
}