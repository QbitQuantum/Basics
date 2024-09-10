void CTestPlayDialog::OnStart() 
{
	//
	GetDlgItem(ID_START)->EnableWindow(FALSE);
	GetDlgItem(ID_STOP)->EnableWindow(TRUE);
	m_bPlayActive = TRUE;

	// results array is 8 x 8
	//          Clubs  Diamonds  Hearts  Spades  NT  Doubled  Redoubled  Total
	// -----------------------------------------------------------------------
	// 1-level   xx/yy
	// 2-level
	// ...
	// 7-level
	// Totals
	//
	int numHands = 0;
	BOOL bBreak = FALSE;

	//
	// suppress updates
	//
	pDOC->SuppressBidHistoryUpdate(TRUE);
	pDOC->SuppressPlayHistoryUpdate(TRUE);
	pMAINFRAME->HideDialog(twBidDialog);
	pVIEW->ClearDisplay();
//NCR	pVIEW->SuppressRefresh();   // Dialog box "smears" with this code ???
	pDOC->ClearAllInfo();

	// save settings
	BOOL bOldClaimSetting = theApp.GetValue(tbComputerCanClaim);
	theApp.SetValue(tbComputerCanClaim, FALSE);
	BOOL bOldAnalysisSetting = theApp.GetValue(tbEnableAnalysisTracing);
#ifndef _TESTING
	theApp.SetValue(tbEnableAnalysisTracing, FALSE);
#endif

	// 
	theApp.SetValue(tbAutoTestMode, TRUE);
	m_strStatus = "Auto play in progress...";
	UpdateData(FALSE);

	//
	int nCode = 0;
	double lfTotalTime = 0;
	long lNumHands = 0;
	CString strAvgTime;
	// loop 
	do
	{
		// play continuously

		// deal a new hand
		m_strStatus = "Dealing...";
		UpdateData(FALSE);
		pDOC->DealHands();
		numHands++;

		// and get bids
		m_strStatus = "Bidding...";
		UpdateData(FALSE);
		do 
		{
			// get the computer's bids
			int nPos = pDOC->GetCurrentPlayerPosition();
			int nBid = pDOC->GetCurrentPlayer()->Bid();
			nCode = pDOC->EnterBid(nPos, nBid);
			if ((nCode == -99) || (nCode == 1))
			{
				// passed out, or 3 passes, and bidding is complete
				break;
			}
			else if (nCode == -1) 
			{
				AfxMessageBox("Error in Bidding Dialog!");
				bBreak = TRUE;
				break;
			}
		} while (!bBreak);

		// bidding is complete; see if we reached a contract
		if (nCode == -99)
			continue;	// passed out, so redeal

		// start timeing
		long lStartTime = timeGetTime();

		// now play out the hand -- play on full auto
		theApp.SetValue(tnCardPlayMode, CEasyBApp::PLAY_FULL_AUTO_EXPRESS);
		pDOC->SetValue(tbExpressPlayMode, TRUE);
		pDOC->InvokeNextPlayer();

		// pump the mesage loop while the hand is being played out
		m_strStatus = "Playing hand...";
		UpdateData(FALSE);
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) 
		{ 
			if (!AfxGetApp()->PumpMessage()) 
			{ 
				::PostQuitMessage(0); 
				return; 
			}
		} 

		
		// reset flags
		pDOC->SetValue(tbExpressPlayMode, FALSE);

		// end timer 
		lNumHands++;
		long lEndTime = timeGetTime();
		lfTotalTime += (lEndTime - lStartTime);
		strAvgTime.Format(_T("%.1f secs"), lfTotalTime / (lNumHands*1000));
		//
		CStatic* pText = (CStatic*) GetDlgItem(IDC_AVG_TIME);
		pText->SetWindowText(strAvgTime);
		pText->UpdateWindow();
		//
		CStatic* pLabel = (CStatic*) GetDlgItem(IDC_LABEL_AVGTIME);
		if (!pLabel->IsWindowVisible())
		{
			pLabel->ShowWindow(SW_SHOW);
			pLabel->UpdateWindow();
		}

		//
		if (m_bStopFlag)
			break;

		// save results and update the display
		Update();
	} while (!bBreak);


	//
	// done -- reset
	//
	pDOC->SuppressBidHistoryUpdate(FALSE);
	pDOC->SuppressPlayHistoryUpdate(FALSE);
	pVIEW->EnableRefresh();
	pVIEW->Refresh(TRUE);
	pDOC->ClearAllInfo();

	// restore settings
	theApp.SetValue(tbComputerCanClaim, bOldClaimSetting);
	theApp.SetValue(tbEnableAnalysisTracing, bOldAnalysisSetting);

	//
	theApp.SetValue(tbAutoTestMode, FALSE);
	GetDlgItem(ID_START)->EnableWindow(TRUE);
	GetDlgItem(ID_STOP)->EnableWindow(FALSE);
	m_bPlayActive = FALSE;
	m_bStopFlag = FALSE;
	
	//
	m_strStatus = "Ready.";
	UpdateData(FALSE);
}