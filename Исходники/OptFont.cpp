void COptFont::OnBrowseFont() 
{
	BROWSEINFO brw;
	LPMALLOC pMalloc;
	LPITEMIDLIST ret;
	char dir[MAX_PATH];

	if (NOERROR == ::SHGetMalloc(&pMalloc) ) {

		m_BrowseFont.GetWindowText(szCacheDir, MAX_PATH);

		memset(&brw, 0, sizeof(BROWSEINFO));
		brw.hwndOwner = this->GetSafeHwnd();
		brw.pszDisplayName = dir;
		brw.lpszTitle = "Select Font Directory...";
		brw.ulFlags = 0L;
		brw.lpfn = LocCbck;

		ret = SHBrowseForFolder(&brw);
		if (ret != NULL) {
			if (::SHGetPathFromIDList(ret, dir)) {
				m_BrowseFont.SetWindowText(dir);
			}
			pMalloc->Free(ret);
		}
		pMalloc->Release();
	}
}