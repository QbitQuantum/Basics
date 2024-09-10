void CDlgShowControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hRgn);		

	if (PtInRegion( hRgn, point.x, point.y ))
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MY_HAND));
	
		if (!m_bMouseIn)
		{
			m_bMouseIn = TRUE;
			Invalidate();
			UpdateWindow();
			SetCapture();
		}
	}
	else
	{
		if (m_bMouseIn)
		{
			m_bMouseIn = FALSE;
			
			Invalidate();
			UpdateWindow();
			
			if (!m_bDown )
				ReleaseCapture();
		}
	}
	DeleteObject(hRgn);

	CDialog::OnMouseMove(nFlags, point);
}