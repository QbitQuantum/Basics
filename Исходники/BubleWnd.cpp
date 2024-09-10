BOOL CBubleWnd::SetSkin(LPCTSTR szFileName,short red,short green,short blue)
{
	BITMAP bm;
	HBITMAP hBmp;

	hBmp=(HBITMAP) ::LoadImage(AfxGetInstanceHandle(),szFileName,IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
	if (!hBmp)
		return FALSE;

	m_biSkinBackground.DeleteObject();
	m_biSkinBackground.Attach(hBmp);
	GetObject(m_biSkinBackground.GetSafeHandle(), sizeof(bm), &bm);
	m_nSkinWidth=bm.bmWidth;
	m_nSkinHeight=bm.bmHeight;
	m_rcText.SetRect(0,0,bm.bmWidth,bm.bmHeight);

	if (red!=-1 && green!=-1 && blue!=-1)
	{
		// No need to delete the HRGN,  SetWindowRgn() owns it after being called
		m_hSkinRegion=GenerateRegion((HBITMAP)m_biSkinBackground.GetSafeHandle(),(BYTE) red,(BYTE) green,(BYTE) blue);
		SetWindowRgn(m_hSkinRegion, true);
	}

	return TRUE;
}