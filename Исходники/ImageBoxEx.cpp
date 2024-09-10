BOOL CImageBoxEx::SetIcon(HICON hIconIn, HICON hIconOut, HICON hIconDisable)
{
	if (hIconIn == NULL && hIconOut == NULL && hIconDisable == NULL)
		return FALSE;
	
	this->FreeResources();
	
	ICONINFO ii;
	
	this->m_Icons[0].m_hIcon = hIconIn;
	::ZeroMemory(&ii, sizeof(ICONINFO));
	if (!GetIconInfo(hIconIn, &ii))
		return FALSE;
	
	this->m_Icons[0].m_nIconX = (DWORD) (ii.xHotspot * 2);
	this->m_Icons[0].m_nIconY = (DWORD) (ii.yHotspot * 2);
	::DeleteObject(ii.hbmMask);
	::DeleteObject(ii.hbmColor);
	
	this->m_Icons[1].m_hIcon = hIconOut;
	::ZeroMemory(&ii, sizeof(ICONINFO));
	if (!GetIconInfo(hIconOut, &ii))
		return FALSE;
	
	this->m_Icons[1].m_nIconX = (DWORD) (ii.xHotspot * 2);
	this->m_Icons[1].m_nIconY = (DWORD) (ii.yHotspot * 2);
	::DeleteObject(ii.hbmMask);
	::DeleteObject(ii.hbmColor);
	
	this->m_Icons[2].m_hIcon = hIconDisable;
	::ZeroMemory(&ii, sizeof(ICONINFO));
	if (!GetIconInfo(hIconDisable, &ii))
		return FALSE;
	
	this->m_Icons[2].m_nIconX = (DWORD) (ii.xHotspot * 2);
	this->m_Icons[2].m_nIconY = (DWORD) (ii.yHotspot * 2);
	::DeleteObject(ii.hbmMask);
	::DeleteObject(ii.hbmColor);
	
	this->Invalidate();
	
	return TRUE;
}