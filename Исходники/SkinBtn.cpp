BOOL CSkinBtn::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bRePain == FALSE)
	{
		if(!m_bDCStored)
		{
    		CRect  rect;
			GetClientRect(&rect);

			m_memDC.CreateCompatibleDC (pDC);
			CBitmap	btScreen;
			btScreen.CreateCompatibleBitmap (pDC,rect.Width(),rect.Height());
			m_memDC.SelectObject (&btScreen);

			m_memDC.BitBlt (0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);

			m_bDCStored=true;

			CRgn rgn;
			rgn.CreateRectRgn (0, 0, rect.Width(), rect.Height());
			SetWindowRgn (rgn, TRUE);

			btScreen.DeleteObject();
		}
	}
	return TRUE;// CButton::OnEraseBkgnd(pDC);//
}