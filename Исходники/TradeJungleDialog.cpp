/////////////////////////////////////////////////////////////////////////////
// setup
/////////////////////////////////////////////////////////////////////////////
BOOL CTradeJungleDialog::OnInitDialog() 
{
	int i;
	int nRes = 0;
	int nChoice = 0;
	BOOL bSingles;
	CDC *dc;
	CString str;
	CHoverStatic *pStatic;
	CButtonST *pButton;
	HDC hDC;

	CHelpDialog::OnInitDialog();

	//get the device context
	dc = GetDC();
	hDC = dc->GetSafeHdc();

	//set up all the statics and bitmaps
	for(i = 0; i < 9; i++)
	{
		//get the res
		switch(i / 3)
		{
		case 0: nRes = RES_WHEAT; break;
		case 1: nRes = RES_SHEEP; break;
		case 2: nRes = RES_ORE; break;
		}

		//bitmaps
		pButton = &m_W2Button + i;

		//set the bitmaps
		pButton->SetBitmaps(VIEW->getResImage(nRes, hDC), COLOR_TRANSP, VIEW->getResImage(nRes, hDC), COLOR_TRANSP);
		pButton->EnableWindow(FALSE);

		//statics
		pStatic = &m_W2Static + i;

		//set the properties
		pStatic->SetFont(Tahoma12);
		pStatic->SetCenter();

		//set the text
		pStatic->SetText(VIEW->getResName(nRes));
	}
	
	//release the device context
	ReleaseDC(dc);

	//determine if we show single cards or not
	bSingles = (1 == (m_nJungles - m_nNeeded));

	//set top text
	str.Format("Which card%s would you like to keep?", bSingles ? "" : "s");
	SetWindowText(str);

	//show or hide the single options
	showSingles(bSingles);

	//if we've got singles and 2 jungles, it means we have to hide the one card
	//choice they don't have
	if((TRUE == bSingles) && (2 == m_nJungles))
	{
		//look at the player's res count for each
		if(0 == GAME->m_players[m_nPlayer].m_iRes[RES_WHEAT])
		{
			m_WButton.ShowWindow(SW_HIDE);
			m_WStatic.ShowWindow(SW_HIDE);
			m_1Radio.ShowWindow(SW_HIDE);
			nChoice = 1;
		}
		else if(0 == GAME->m_players[m_nPlayer].m_iRes[RES_ORE])
		{
			m_OButton.ShowWindow(SW_HIDE);
			m_OStatic.ShowWindow(SW_HIDE);
			m_2Radio.ShowWindow(SW_HIDE);
		}
		else
		{
			m_SButton.ShowWindow(SW_HIDE);
			m_SStatic.ShowWindow(SW_HIDE);
			m_3Radio.ShowWindow(SW_HIDE);
		}
	}

	//initial set radio selection
	switch(nChoice)
	{
	case 0:	m_1Radio.SetCheck(TRUE); break;
	case 1: m_2Radio.SetCheck(TRUE); break;
	case 2: m_3Radio.SetCheck(TRUE); break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}