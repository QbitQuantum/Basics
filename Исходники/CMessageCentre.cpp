//						============================
BOOL 					CMessageCentre::OnInitDialog() 
//						============================
{
	CDialog::OnInitDialog();

	// Set icon on the dialog
	HICON icon = AfxGetApp()->LoadIcon(IDI_ICON2);
	// Make it a small icon
	SetIcon(icon,false);

	// Change the dialog background to yellow
	m_brush.CreateSolidBrush(RGB(255,204,0));

	// Calculate the difference in height for 'Less Detail' en 'More Detail'
	// states of this dialog
	WINDOWPLACEMENT wp;
	CRect Recto;
	CWnd* pMore;
	CWnd* pLess;
	int nCaptionHeight = ::GetSystemMetrics(SM_CYCAPTION);

	m_nHeightDifference = 0;
	pMore = GetDlgItem(IDC_MORE_DETAIL_SIZE);
	pLess = GetDlgItem(IDC_LESS_DETAIL_SIZE);

	if ((pMore != 0) && (pLess != 0))
	{
		//pMore->GetWindowPlacement(&wp);
		//m_nHeightDifference = wp.rcNormalPosition.bottom;
		GetClientRect(&Recto);
		m_nHeightDifference = Recto.bottom; // + nCaptionHeight;

		pLess->GetWindowPlacement(&wp);
		m_nHeightDifference = m_nHeightDifference - wp.rcNormalPosition.bottom;


	}

//	m_button_pauze.SubclassDlgItem(IDC_BTN_PAUSE,this);
//	m_button_stop.SubclassDlgItem(IDC_BTN_STOP,this);
//	m_button_detail.SubclassDlgItem(IDC_BTN_DETAIL,this);
//	m_Progress.SubclassDlgItem(IDC_PROGRESS,this);

	// Set the texts of all controls
	m_pDlg->SetControlTexts();

	// Set the range of the progress indicator (0 ... 1000)
	m_Progress.SetRange(0, 1000);

	// Return TRUE unless you set the focus to a control
	return TRUE;
}