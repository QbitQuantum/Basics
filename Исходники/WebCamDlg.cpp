void CWebCamDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	DrawDibDraw
		(
		m_hDD, 
		m_hDC,
		0, 0,
		rect.right, rect.bottom,
		&m_bmih,
		m_lpScreenDIB,
		0, 0,
		m_bmih.biWidth, m_bmih.biHeight,
		DDF_SAME_HDC
		);
	// Do not call CDialog::OnPaint() for painting messages
}