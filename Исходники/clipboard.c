/**************************************************************************
 * RenderHDROP
 *
 * creates a CF_HDROP structure
 */
HGLOBAL RenderHDROP(LPITEMIDLIST pidlRoot, LPITEMIDLIST * apidl, UINT cidl)
{
	UINT i;
	int rootlen = 0,size = 0;
	WCHAR wszRootPath[MAX_PATH];
	WCHAR wszFileName[MAX_PATH];
	HGLOBAL hGlobal;
	DROPFILES *pDropFiles;
	int offset;

	TRACE("(%p,%p,%u)\n", pidlRoot, apidl, cidl);

	/* get the size needed */
	size = sizeof(DROPFILES);

	SHGetPathFromIDListW(pidlRoot, wszRootPath);
	PathAddBackslashW(wszRootPath);
	rootlen = strlenW(wszRootPath);

	for (i=0; i<cidl;i++)
	{
	  _ILSimpleGetTextW(apidl[i], wszFileName, MAX_PATH);
	  size += (rootlen + strlenW(wszFileName) + 1) * sizeof(WCHAR);
	}

	size += sizeof(WCHAR);

	/* Fill the structure */
	hGlobal = GlobalAlloc(GHND|GMEM_SHARE, size);
	if(!hGlobal) return hGlobal;

        pDropFiles = (DROPFILES *)GlobalLock(hGlobal);
	offset = (sizeof(DROPFILES) + sizeof(WCHAR) - 1) / sizeof(WCHAR);
        pDropFiles->pFiles = offset * sizeof(WCHAR);
        pDropFiles->fWide = TRUE;

	strcpyW(wszFileName, wszRootPath);

	for (i=0; i<cidl;i++)
	{

	  _ILSimpleGetTextW(apidl[i], wszFileName + rootlen, MAX_PATH - rootlen);
	  strcpyW(((WCHAR*)pDropFiles)+offset, wszFileName);
	  offset += strlenW(wszFileName) + 1;
	}

	((WCHAR*)pDropFiles)[offset] = 0;
	GlobalUnlock(hGlobal);

	return hGlobal;
}