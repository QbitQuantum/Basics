void CBidDialog::UpdateBidDisplay(int nPos, int nBid, BOOL bPrompt, BOOL bTentative)
{
	int nTextID = IDC_BID_SOUTH + nPos;
	int nIconID = IDCI_BID_SOUTH + nPos;

	// see if we're using text for bids
	if (!UsingSuitSymbols() || !ISBID(nBid) || bTentative)
	{
		// show bid text
		GetDlgItem(nIconID)->ShowWindow(FALSE);
		GetDlgItem(nTextID)->ShowWindow(TRUE);
		CString strTemp;

		// show text
		if ((nPos == SOUTH) && (bPrompt))
		{
			SetDlgItemText(nTextID, "??");
		} 
		else if (nBid == -2)
		{
			SetDlgItemText(nTextID, "?");
		} 
		else if (nBid == -1) 
		{
			SetDlgItemText(nTextID, "");
		} 
		else if (bTentative)
		{
			strTemp = BidToShortString(nBid) + _T('?');
			SetDlgItemText(nTextID, (LPCTSTR)strTemp);
		}
		else 
		{
			// real bid
			strTemp = BidToShortString(nBid);
			SetDlgItemText(nTextID, (LPCTSTR)strTemp);
		}
		GetDlgItem(nTextID)->UpdateWindow();
	}
	else
	{
		// show bid icon
		GetDlgItem(nTextID)->ShowWindow(FALSE);
		GetDlgItem(nIconID)->ShowWindow(TRUE);
		CStatic* pStatic = (CStatic*) GetDlgItem(nIconID);
		if (ISBID(nBid))
		{
			int nSuit = (nBid-1) % 5;
			int nLevel = (nBid-1) / 5;
			pStatic->SetIcon(m_buttonIcons[nSuit][nLevel]);
		}
		else
		{
			pStatic->SetIcon(NULL);
		}
		//
		pStatic->UpdateWindow();
	}
/*
	CString strTemp;

	// show text
	if ((nPos == SOUTH) && (bPrompt))
	{
		SetDlgItemText(IDC_BID_SOUTH, "??");
	} 
	else if (nBid == -2)
	{
		SetDlgItemText(IDC_BID_SOUTH+nPos, "?");
	} 
	else if (nBid == -1) 
	{
		SetDlgItemText(IDC_BID_SOUTH+nPos, "");
	} 
	else if (bTentative)
	{
		strTemp = BidToShortString(nBid) + _T('?');
		SetDlgItemText(IDC_BID_SOUTH+nPos, (LPCTSTR)strTemp);
	}
	else 
	{
		// real bid
		strTemp = BidToShortString(nBid);

		// play sound if appropriate
		if (m_bSpeechEnabled)
		{
			CString strDir = theApp.GetValueString(tszProgramDirectory);
//			CString strPath = strDir +  _T("\\Sounds\\") + PositionToString(nPos) + strTemp + _T(".wav");
			CString strPath = strDir +  _T("\\Sounds\\") + strTemp + _T(".wav");
			CFile file;
			if (file.Open(strPath, CFile::modeRead))
			{
				file.Close();
				PlaySound(strPath, NULL, SND_SYNC | SND_NOSTOP | SND_NOWAIT);
			}
		}

		// show bid
		SetDlgItemText(IDC_BID_SOUTH+nPos, (LPCTSTR)strTemp);
	}
*/
}