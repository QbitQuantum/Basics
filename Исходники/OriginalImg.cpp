void COriginalImg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here	
	
	CWnd *pWnd = GetDlgItem(IDC_ORGIMG);
	if (pWnd==NULL)
	{
		MessageBox("error!");
		return;
	}
	CRect rect;
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	pWnd->MoveWindow(rect.left, rect.top, m_width, m_height, true);	
	CPaintDC pdc(pWnd);	
	::SetStretchBltMode(pdc, COLORONCOLOR);
	//show  image
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(imgBuf + sizeof(BITMAPFILEHEADER));
	LPBITMAPINFO lpbmp = new BITMAPINFO;
	ZeroMemory(lpbmp, sizeof(BITMAPINFO));
	lpbmp->bmiHeader = *bmpinfo;
	StretchDIBits(pdc.GetSafeHdc(),  0,  0, m_width,  m_height,  0,  0,  m_width,  m_height, grayBuf,  lpbmp,  DIB_RGB_COLORS,  SRCCOPY);  
	// Do not call CDialog::OnPaint() for painting messages
}