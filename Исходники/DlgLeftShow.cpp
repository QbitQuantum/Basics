void CDlgLeftShow::LoadSkin()
{
	TCHAR		path[MAX_PATH];
	CString		s = "..\\";
	CBcfFile f( s + "..\\" + m_skinmgr.GetGameSkinPath() + m_skinmgr.GetGameSkinBcfFileName());
	CString SkinFolder	= f.GetKeyVal("config", "skinfolder", m_skinmgr.GetSkinPath());
	wsprintf(path, "%s%sgame\\SomeOneLeft.bmp", s, SkinFolder);

	int cx,cy;
	CGameImage	m_bt;
	m_bt.SetLoadInfo(path,true);
	m_bkimage.SetLoadInfo(path,CGameImageLink::m_bAutoLock);
	CGameImageHelper ImageHandle(&m_bkimage);
	HRGN hRgn=AFCBmpToRgn(ImageHandle,m_bkimage.GetPixel(0,0),RGB(1,1,1));
	if (hRgn!=NULL)
	{
		SetWindowRgn(hRgn,TRUE);
	}
	//cx=ImageHandle.GetWidth();
	//cy=ImageHandle.GetHeight();
	//SetWindowPos(NULL,0,0,cx,cy,SWP_NOMOVE|SWP_NOZORDER);
	//CenterWindow(m_pParentWnd);

	wsprintf(path, "%s%sgame\\ok_bt.bmp", s, SkinFolder);

	m_bt.SetLoadInfo(path,true);
	m_btOk.LoadButtonBitmap(path,false);
	//m_btOk.SetWindowPos(NULL,0,0,m_bt.GetWidth()/4,m_bt.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
	//m_btOk.MoveWindow( (m_bkimage.GetWidth() - m_bt.GetWidth()/4)/2,
		//m_bkimage.GetHeight()-50,
		//m_bt.GetWidth()/4,
		//m_bt.GetHeight()
		//);
}