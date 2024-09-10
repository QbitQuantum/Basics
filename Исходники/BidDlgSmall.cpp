void CBidDialogSmall::EnableControls()
{
	// enable all controls
	for(int i=IDC_BID_LEVEL_1;i<=IDC_BID_LEVEL_7;i++)
	{
		CButton* pButton = (CButton*) GetDlgItem(i);
		pButton->EnableWindow(TRUE);
		pButton->SetState(FALSE);
	}

	for(i=IDC_SUIT_CLUBS;i<=IDC_SUIT_NOTRUMP;i++)
	{
		CButton* pButton = (CButton*) GetDlgItem(i);
		pButton->EnableWindow(TRUE);
		pButton->SetState(FALSE);
	}
/*
	// enable the level & suit buttons
	int nLastBid = pDOC->GetLastValidBid();
	if (nLastBid == BID_PASS)
	{
	}
	//	
	int nLevel = BID_LEVEL(nLastBid);
	int nSuit = BID_SUIT(nLastBid);

	// enable all suits higher than the one bid
	for(int i=0;i<nSuit;i++)
		GetDlgItem(IDC_SUIT_CLUBS+i)->EnableWindow(TRUE);
*/
}