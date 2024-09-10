int CFolderDialog::DoModal()
{
	int nReturn = IDOK;

	// initialize the result to the starting folder value
	m_strFinalFolderName = m_strInitialFolderName;

	ITEMIDLIST* piid = NULL;

	// call the shell function
	piid = ::SHBrowseForFolder(&m_bi);

	// process the result
	if (piid && ::SHGetPathFromIDList(piid, m_szPath)) {
		m_strFinalFolderName = m_szPath;
		nReturn = IDOK;
	} else {
		nReturn = IDCANCEL;
	}

	// Release the ITEMIDLIST if we got one
	if (piid) {
		LPMALLOC lpMalloc;
		VERIFY(::SHGetMalloc(&lpMalloc) == NOERROR);
		lpMalloc->Free(piid);
		lpMalloc->Release();
	}

	return nReturn;
}