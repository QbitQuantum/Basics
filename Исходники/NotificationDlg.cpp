BOOL CNotificationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_NOACTIVATE);
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, WS_POPUP);
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, NULL);
	SetWindowPos(CWnd::FromHandle(HWND_TOPMOST), rect.right-200, rect.bottom-(95*idx)+30, 0, 0, /*SWP_NOZORDER|*/SWP_NOSIZE|SWP_NOACTIVATE);
	ShowWindow(SW_SHOWNA);

		CDC scrdc;
	scrdc.Attach(::GetDC(0));
	BLENDFUNCTION func;
	func.BlendOp=AC_SRC_OVER;
	func.AlphaFormat=AC_SRC_ALPHA;
	func.SourceConstantAlpha=0;
	func.BlendFlags=0;
	UpdateLayeredWindow(&scrdc, &CPoint(rect.right-200, rect.bottom-(95*idx)+30), &CSize(200, 95), &bdc, &CPoint(0,0), 0, &func, ULW_ALPHA);
	::ReleaseDC(0, scrdc);

	TRACKMOUSEEVENT tme;
	memset(&tme, 0, sizeof(TRACKMOUSEEVENT));
	tme.cbSize=sizeof(TRACKMOUSEEVENT);
	tme.dwFlags=TME_LEAVE;
	tme.hwndTrack=GetSafeHwnd();
	::TrackMouseEvent(&tme);
	cls=false;
	StartTransitionIn();

	//return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
	return FALSE;
}