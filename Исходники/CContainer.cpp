BOOL CContainer::OnPaint(HDC hDC) 
{
	CRect rcClient;
	CPaintDC dc(GetSafeHwnd()); // device context for painting
	CBrush cbr;
	CRect m_rectDraw;
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	GetClientRect(rcClient);
	CGDI		MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,rcClient.Width(),rcClient.Height());	
	
	CBitmap *m_bitmapOld=new CBitmap(MemDC.SelectObject(&m_BitmapMemDC));
	MemDC.FillRect(&rcClient,&cbr);
		
	m_rectTab=m_rectCliente;
	m_rectDraw=m_rectCliente;
	if (m_alnTab==ALN_BOTTOM)
	{
		if (m_Numtabs > 1)
		m_rectDraw.bottom=rcClient.bottom-(m_sizeImag.cy+SPACE_TAB+2);	
	}
	else
		m_rectDraw.top=rcClient.top+(m_sizeImag.cy+SPACE_TAB+2);
	
	if (m_style != S3D) //si son carpetas estilo excel o tabbed como devstudio 7
	{
		if (m_alnTab==ALN_BOTTOM)
		{
			m_rectCliente.bottom=rcClient.bottom-(DEFAULT_FLAT);
			m_rectTab.top=rcClient.bottom+2;
		}
		else
		{
			m_rectTab.bottom=rcClient.top+(DEFAULT_FLAT)+3;
		}
	}

	int nVal=0;
	
	if (m_alnTab!=ALN_TOP)
	{
		
		MemDC.FillRect(m_rectTab,&cbr);
		CRect mrc=m_rectDraw;
		
	}
	else
	{
		CRect rc=m_rectDraw;
		for (int i=0; i< 2; i++)
		{
			MemDC.Draw3dRect(rc,CDrawLayer::GetRGBColorFace(),CDrawLayer::GetRGBColorFace());
			rc.DeflateRect(1,1);
		}
		
		rc.InflateRect(3,3);
		if (m_bDrawFrame)
			MemDC.Draw3dRect(rc,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));
		else
		{
			CRect mrc=m_rectDraw;
			mrc.top+=nVal;
			MemDC.Draw3dRect(mrc,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));

		}
		rc=m_rectDraw;
		rc.bottom=rc.top+3;
		MemDC.FillRect(rc,&cbr);
		
	}
	
	
	
	Drawtabs(&MemDC);

	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	cbr.DeleteObject();
	m_bitmapOld->DeleteObject();
	dc.DeleteDC();
	delete m_bitmapOld;
	return TRUE;
}