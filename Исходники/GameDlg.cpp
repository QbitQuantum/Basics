void CGameDlg::InitBackground()
{
	CClientDC dc(this);
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_GAME_BG);
	m_back.CreateCompatibleDC(&dc);
	m_back.SelectObject(bmpMain);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpmen;
	bmpmen.CreateCompatibleBitmap(&dc,800,600);
	m_dcMem.SelectObject(bmpmen);

	m_dcMem.BitBlt(0,0,800,600,&m_back,0,0,SRCCOPY);
}