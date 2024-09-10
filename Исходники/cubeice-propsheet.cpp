STDMETHODIMP CShellPropSheetExt::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID)
{
	HRESULT   hr;
	FORMATETC formatetc;
	STGMEDIUM medium;
	LPTSTR    lpszFilePath;

	formatetc.cfFormat = RegisterClipboardFormat(CFSTR_FILENAME);
	formatetc.ptd      = NULL;
	formatetc.dwAspect = DVASPECT_CONTENT;
	formatetc.lindex   = -1;
	formatetc.tymed    = TYMED_HGLOBAL;

	hr = pdtobj->GetData(&formatetc, &medium);
	if (FAILED(hr))
		return E_FAIL;

	lpszFilePath = (LPTSTR)GlobalLock(medium.hGlobal);
	filepath = lpszFilePath;
	GlobalUnlock(medium.hGlobal);

	ReleaseStgMedium(&medium);

	return S_OK;
}