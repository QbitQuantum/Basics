int CMovingLrcDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  在此添加您专用的创建代码
	MoveWindow(CRect(400,0,800,25));
	SetTimer(1,TIMER_INTERVAL,NULL);
	ipast=0.0f;
	m_Font.CreateFont(   
		12,    //nHeight   //_T("Tahoma")); 14
		0,                              //nWidth   
		0,    //nEscapement   
		0,    //nOrientation   
		FW_NORMAL,   //nWeight 
		//FW_MEDIUM,
		//FW_SEMIBOLD,
		FALSE,                          //bItalic   
		FALSE,                          //bUnderline   
		0,                              //cStrikeOut   
		//   ANSI_CHARSET,     
		DEFAULT_CHARSET,  //nCharSet   
		OUT_DEFAULT_PRECIS,             //nOutPrecision   
		CLIP_DEFAULT_PRECIS,            //nClipPrecision   
		DEFAULT_QUALITY,                //nQuality   
		DEFAULT_PITCH   |   FF_SWISS,   //nPitchAndFamily   
		_T("宋体"));
	SetWindowPos(&wndTopMost,400,0,0,0,SWP_NOSIZE);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,400,25,10,10);
	SetWindowRgn(rgn,TRUE);
	ShowWindow(SW_SHOW);
	UpdateWindow();
	return 0;
}