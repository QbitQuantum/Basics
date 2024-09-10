void CTestMFCDlg::OnPaint() 
{
	/*
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	*/
	CPaintDC dc(this);
	CRect rect;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP3);
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);
	CDC cdc;
	cdc.CreateCompatibleDC(&dc);
	cdc.SelectObject(bmp);
	CBrush brush;
	brush.CreatePatternBrush(&bmp);

	//GetClientRect(rect);
	GetClientRect(rect);
	dc.StretchBlt(0,0,rect.right,rect.bottom,&cdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,SRCCOPY);
	//dc.FillRect(CRect(0,0,rect.right/2,rect.bottom/2),&brush);
	//dc.FillSolidRect(0,0,rect.right/2,rect.bottom/2,RGB(0,0,255));
	//dc.FillSolidRect(CRect(0,0,rect.right/2,rect.bottom/2),RGB(0,0,255));
	//CDialog::OnPaint();
	/*
	CDialog::OnInitDialog(); 
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP1); 
	CBrush brush;
	brush.CreatePatternBrush(&bmp); 
	bmp.DeleteObject(); 
	*/
}