BOOL COCTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//create shortcut toolbar for the dialog
	//step1.load toolbar to m_wndToolBar
	if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadToolBar(IDR_TOOLBAR))	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//step2. get the client rect of the dialog
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);

	CPoint ptOffset(rcClientNow.left - rcClientStart.left,
		rcClientNow.top - rcClientStart.top);

	CRect  rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)	{
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE);
		pwndChild = pwndChild->GetNextWindow();
	}

	//step3.caculate the space for placing the toolbar
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	m_iWidth=rcWindow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	m_iHeight=rcWindow.Height();

	//reset the size of the window
	::MoveWindow(this->m_hWnd,0,0,m_iWidth,m_iHeight,FALSE);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	
	CString strPathName=".\\DOCT.cfg";
	ifstream fin(strPathName);		
	fin>>CamGain>>IntTime>>ScanFreq>>m_ALineNum>>m_IterationNum
		>>ScanVMinX>>ScanVMaxX>>ScanVMinY>>ScanVMaxY>>bStepX>>bStepY
		>>FrameNum>>FrameThickness>>Dispersion>>AvgNum>>bScanBackward
		>>bReconstructImage;
	fin.close();
	RawDataSize=ALineNum* IterationNum * SPECTRUMWIDTH ;
	FrameSize=ALineNum*IterationNum*FFTNUM/2;

	m_SliderCamGain = CamGain/CAMGAINFACTOR;
	m_SliderIntTime = IntTime/INTTIMEFACTOR;
	UpdateData(FALSE);

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	return TRUE; 
}