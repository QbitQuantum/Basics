/////////////////////////////////////////////////////////////////////////////
// show everything
/////////////////////////////////////////////////////////////////////////////
void CTradeOfferDialog::OnCounterButton() 
{
	int i;
	int iRes;
	int iPlayer;
	int iCount = 4;
	int nQty;
	CRect rect;
	CString str;
	CButtonST *pButton;
	CHoverStatic *pText;
	CHoverStatic *pQty;

	//kill the timer
	stopTimer();

	//send the reply
	VIEW->clientReplyOffer(m_uiTradeID, TRADE_COUNTER);

	//set new texts
	str.Format("Ask %s for these cards...", GAME->m_players[VIEW->getPlayer()].m_player.getName());
	m_PlayerStatic.SetWindowText(str);

	//set our text
	m_OPlayerStatic.SetWindowText("in exchange for these cards");

	//get who we are
	iPlayer = GAME->m_iIndex;

	//go through what the trader wants from us and weed out anything that
	//we don't have
	for(i = 0; i < 4; i++)
	{	
		//enable all other player trade windows
		pButton = &m_Trade1Button + i;
		pButton->EnableWindow();

		//disable this side, if necessary
		if(-1 != m_iTradePlace[i])
		{
			iRes = m_iTradePlace[i];

			pButton = &m_OHand1Button + iRes;
			pButton->EnableWindow(FALSE);

			pText = &m_OHand1Text + iRes;
			pText->EnableWindow(FALSE);

			pQty = &m_Inhand1Qty + iRes;
			pQty->EnableWindow(FALSE);
		}

		//skip ones that aren't there
		if(-1 == m_iOTradePlace[i])
		{
			iCount--;
			continue;
		}

		//get the res
		iRes = m_iOTradePlace[i];

		//get button
		pButton = &m_OTrade1Button + i;

		//enable window for trading
		pButton->EnableWindow();

		//determine if we have enough to match what they want
		if(GAME->m_players[iPlayer].m_iRes[iRes] < m_iOTrade[iRes])
		{
			//reset counter spot
			m_iOTradePlace[i] = -1;
			m_iOTrade[iRes] = 0;

			pText = &m_OTrade1Text + i;
			pQty = &m_OTrade1Qty + i;

			//hide all
			pText->ShowWindow(SW_HIDE);
			pQty->ShowWindow(SW_HIDE);
			pButton->ShowWindow(SW_HIDE);

			//we've changed the trade already
			m_bChanged = TRUE;

			//decrement counter
			iCount--;
		}
		else
		{
			//disable opposing side
			pButton = &m_InHand1Button + iRes;
			pButton->EnableWindow(FALSE);

			pText = &m_Inhand1Text + iRes;
			pText->EnableWindow(FALSE);

			//now correctly set how many cards should appear below

			//get the onhand quantity
			nQty = GAME->m_players[iPlayer].m_iRes[iRes] - m_iOTrade[iRes];

			//get quantity pointer
			pQty = &m_Inhand1Qty + iRes;

			//if it's zero, remove this card
			if(nQty == 0)
			{
				//get the other pointers
				pButton = &m_OHand1Button + iRes;
				pText = &m_OHand1Text + iRes;

				//remove the texts
				pText->ShowWindow(SW_HIDE);
				pButton->ShowWindow(SW_HIDE);
				pQty->ShowWindow(SW_HIDE);
			}
			else
			{
				//set the new text
				str.Format("%d", nQty);
				pQty->SetText(str);
			}
		}
	}

	//get screen rect
	GetWindowRect(&rect);

	//disable this button
	m_CounterButton.EnableWindow(FALSE);

	//disable the accept button so they dont' accidently press it
	m_OKButton.EnableWindow(FALSE);

	//show all
	SetWindowPos(&wndTop, 0, 0, rect.Width(), 260, SWP_NOMOVE | SWP_NOZORDER);

	//set the trade flag
	m_iNumOTrade = iCount;

	//enable/disable the offer button
	enableTrade();

	//set the focus to the view
	VIEW->SetFocus();
}