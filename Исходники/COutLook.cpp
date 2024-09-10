BOOL COutLook::OnPaint(HDC hDC) 
{
	CPaintDC dc(GetSafeHwnd());
	CRect rect,rcClient;
	GetClientRect(&rect);
	CRect rcMsg;
	int iy=0;
	int m_iNumBotton= m_ArrayButtons.GetSize();
	int iMitad= rect.Width()/2;
	iMitad-=(m_sizeImage.cx/2);
	iMitad--;
	int nMode; 
	rcClient=rect;
	CBrush cbr;
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	
	CGDI			MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,
				  rect.Width(),rect.Height());	
	CBitmap m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);

	MemDC.FillRect(&rect,&cbr);
	nMode  =MemDC.SetBkMode(TRANSPARENT);
	CFont cfont(MemDC.SelectObject((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	for( int iCont=0; iCont< m_iNumBotton;iCont++)
	{
		CItems* cit=(CItems*)m_ArrayButtons[iCont];
		CRect rcWin;
		cit->m_bt.GetWindowRect(rcWin);
		ScreenToClient(rcWin);
		rcMsg=rcWin;
		rcMsg.top=rcWin.bottom+2;
		rcMsg.bottom=rcMsg.top+16;
		rcMsg.left=rect.left;
		rcMsg.right=rect.right;
		if (m_TypeOutLook)
			MemDC.DrawText(cit->m_szMessage,rcMsg,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}	
	MemDC.SetBkMode(nMode);
	MemDC.SelectObject(cfont.GetFont());
	if (m_iDrawFrameUp==TRUE)
	{
		m_rectArrowUp.top=5;
		m_rectArrowUp.bottom=m_rectArrowUp.top+16;
		m_rectArrowUp.right=rect.right-5;
		m_rectArrowUp.left=m_rectArrowUp.right-16;
		MemDC.DrawFrameControl(m_rectArrowUp,DFC_SCROLL,DFCS_SCROLLUP);
	}
	if (m_iDrawFrameDown==TRUE)
	{
		m_rectArrowDown.bottom=rect.bottom-5;
		m_rectArrowDown.top=m_rectArrowDown.bottom-16;
		m_rectArrowDown.right=rect.right-5;
		m_rectArrowDown.left=m_rectArrowDown.right-16;
		MemDC.DrawFrameControl(m_rectArrowDown,DFC_SCROLL,DFCS_SCROLLDOWN);
	}
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(&m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	return TRUE;	
}