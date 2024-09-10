/**************************************************************************
 * DoOpenProperties
 */
static void DoOpenProperties(ItemCmImpl *This, HWND hwnd)
{
	static const UINT MAX_PROP_PAGES = 99;
	static const WCHAR wszFolder[] = {'F','o','l','d','e','r', 0};
	static const WCHAR wszFiletypeAll[] = {'*',0};
	LPSHELLFOLDER lpDesktopSF;
	LPSHELLFOLDER lpSF;
	LPDATAOBJECT lpDo;
	WCHAR wszFiletype[MAX_PATH];
	WCHAR wszFilename[MAX_PATH];
	PROPSHEETHEADERW psh;
	HPROPSHEETPAGE hpages[MAX_PROP_PAGES];
	HPSXA hpsxa;
	UINT ret;

	TRACE("(%p)->(wnd=%p)\n", This, hwnd);

	ZeroMemory(&psh, sizeof(PROPSHEETHEADERW));
	psh.dwSize = sizeof (PROPSHEETHEADERW);
	psh.hwndParent = hwnd;
	psh.dwFlags = PSH_PROPTITLE;
	psh.nPages = 0;
	psh.u3.phpage = hpages;
	psh.u2.nStartPage = 0;

	_ILSimpleGetTextW(This->apidl[0], (LPVOID)&wszFilename, MAX_PATH);
	psh.pszCaption = (LPCWSTR)&wszFilename;

	/* Find out where to look for the shell extensions */
	if (_ILIsValue(This->apidl[0]))
	{
	    char sTemp[64];
	    sTemp[0] = 0;
	    if (_ILGetExtension(This->apidl[0], sTemp, 64))
	    {
		HCR_MapTypeToValueA(sTemp, sTemp, 64, TRUE);
		MultiByteToWideChar(CP_ACP, 0, sTemp, -1, wszFiletype, MAX_PATH);
	    }
	    else
	    {
		wszFiletype[0] = 0;
	    }
	}
	else if (_ILIsFolder(This->apidl[0]))
	{
	    lstrcpynW(wszFiletype, wszFolder, 64);
	}
	else if (_ILIsSpecialFolder(This->apidl[0]))
	{
	    LPGUID folderGUID;
	    static const WCHAR wszclsid[] = {'C','L','S','I','D','\\', 0};
	    folderGUID = _ILGetGUIDPointer(This->apidl[0]);
	    lstrcpyW(wszFiletype, wszclsid);
	    StringFromGUID2(folderGUID, &wszFiletype[6], MAX_PATH - 6);
	}
	else
	{
	    FIXME("Requested properties for unknown type.\n");
	    return;
	}

	/* Get a suitable DataObject for accessing the files */
	SHGetDesktopFolder(&lpDesktopSF);
	if (_ILIsPidlSimple(This->pidl))
	{
	    ret = IShellFolder_GetUIObjectOf(lpDesktopSF, hwnd, This->cidl, (LPCITEMIDLIST*)This->apidl,
					     &IID_IDataObject, NULL, (LPVOID *)&lpDo);
	    IShellFolder_Release(lpDesktopSF);
	}
	else
	{
	    IShellFolder_BindToObject(lpDesktopSF, This->pidl, NULL, &IID_IShellFolder, (LPVOID*) &lpSF);
	    ret = IShellFolder_GetUIObjectOf(lpSF, hwnd, This->cidl, (LPCITEMIDLIST*)This->apidl,
					     &IID_IDataObject, NULL, (LPVOID *)&lpDo);
	    IShellFolder_Release(lpSF);
	    IShellFolder_Release(lpDesktopSF);
	}

	if (SUCCEEDED(ret))
	{
	    hpsxa = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, wszFiletype, MAX_PROP_PAGES - psh.nPages, lpDo);
	    if (hpsxa != NULL)
	    {
		SHAddFromPropSheetExtArray(hpsxa, Properties_AddPropSheetCallback, (LPARAM)&psh);
		SHDestroyPropSheetExtArray(hpsxa);
	    }
	    hpsxa = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, wszFiletypeAll, MAX_PROP_PAGES - psh.nPages, lpDo);
	    if (hpsxa != NULL)
	    {
		SHAddFromPropSheetExtArray(hpsxa, Properties_AddPropSheetCallback, (LPARAM)&psh);
		SHDestroyPropSheetExtArray(hpsxa);
	    }
	    IDataObject_Release(lpDo);
	}

	if (psh.nPages)
	    PropertySheetW(&psh);
	else
	    FIXME("No property pages found.\n");
}