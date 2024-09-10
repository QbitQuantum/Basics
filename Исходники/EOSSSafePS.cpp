BOOL CEOSSPropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	CRect WindowRect;
	CRect FinalRect;
	GetWindowRect(&WindowRect);
	WindowRect.bottom += 60;
	MoveWindow(&WindowRect);
	int Interspace = 6;

	int ButtonWidth = (WindowRect.right - WindowRect.left)/5 - 6*Interspace;
	if (ButtonWidth < 100) 
		ButtonWidth = 116;
	else
		ButtonWidth = 157;

	FinalRect = WindowRect;
	ScreenToClient(FinalRect);
	int Y1 = FinalRect.bottom - 60;
	int Y2 = FinalRect.bottom - 10;

	DWORD dwStyle = WS_CHILD | WS_TABSTOP | WS_VISIBLE |
		  BS_PUSHBUTTON | BS_MULTILINE | BS_CENTER;

	m_pCloseButton->Create( "Close", dwStyle,
		  CRect(Interspace, Y1,
				Interspace + ButtonWidth,Y2),
		  this,
		  ID_CLOSE_BUTTON);

	m_pPauseButton->Create(COLLECTINGBEGIN, dwStyle,
		  CRect(2*Interspace + ButtonWidth,Y1,
				2*Interspace + 2*ButtonWidth,Y2),
		  this,
		  ID_PAUSE_BUTTON);

	m_pAckFlagsButton->Create("Acknowledge Flags",dwStyle,
		  CRect(3*Interspace + 2*ButtonWidth,Y1,
				3*Interspace + 3*ButtonWidth,Y2),
		  this,
		  ID_ACKFL_BUTTON);

	m_pPrintButton->Create("Snapshot Status\nTo File",dwStyle,
		  CRect(4*Interspace + 3*ButtonWidth,Y1,
				4*Interspace + 4*ButtonWidth,Y2),
		  this,
		  ID_PRINT_BUTTON);

	char temp[32];
	int minutes = (m_pParent->m_iDlgCloseMilliseconds/1000-m_dToClose)/60;
	int seconds   = (m_pParent->m_iDlgCloseMilliseconds/1000-m_dToClose) % 60;
	sprintf(temp,"Extend Auto\nClose: %d:%02d",minutes,seconds);

	m_pToClose->Create(temp,dwStyle,
		  CRect(5*Interspace + 4*ButtonWidth,Y1,
				5*Interspace + 5*ButtonWidth,Y2),
		this,
		ID_TOCLOSE);

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	if (pSysMenu != NULL)
	{
		pSysMenu->DeleteMenu( SC_SIZE, MF_BYCOMMAND);
		pSysMenu->DeleteMenu( SC_MAXIMIZE, MF_BYCOMMAND);
	}
	
	GetTabControl( )->SetImageList(m_pImageList);
	GetTabControl( )->ModifyStyle(TCS_MULTILINE,TCS_SINGLELINE);
	TC_ITEM pTabCtrlItem;
	pTabCtrlItem.mask = TCIF_IMAGE;
	pTabCtrlItem.iImage = 1;
	GetTabControl()->SetItem(1,&pTabCtrlItem);

	return bResult;
}