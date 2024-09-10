bool CClient::Cmd_SecureTrade( CChar *pChar, CItem *pItem )
{
	ADDTOCALLSTACK("CClient::Cmd_SecureTrade");
	// Begin secure trading with a char. (Make the initial offer)
	if ( !pChar || pChar == m_pChar )
		return false;

	// Make sure both clients can see each other, because trade window is an container
	// and containers can be opened only after the object is already loaded on screen
	if ( !m_pChar->CanSee(pChar) || !pChar->CanSee(m_pChar) )
		return false;

	if ( pItem && (IsTrigUsed(TRIGGER_DROPON_CHAR) || IsTrigUsed(TRIGGER_ITEMDROPON_CHAR)) )
	{
		CScriptTriggerArgs Args(pChar);
		if ( pItem->OnTrigger(ITRIG_DROPON_CHAR, m_pChar, &Args) == TRIGRET_RET_TRUE )
			return false;
	}

	if ( pChar->m_pNPC )		// NPC's can't use trade windows
		return pItem ? pChar->NPC_OnItemGive(m_pChar, pItem) : false;
	if ( !pChar->m_pClient )	// and also offline players
		return false;

	if ( pChar->GetDefNum("REFUSETRADES") )
	{
		SysMessagef(g_Cfg.GetDefaultMsg(DEFMSG_MSG_TRADE_REFUSE), pChar->GetName());
		return false;
	}

	// Check if the trade window is already open
	for ( CItem *pItemCont = m_pChar->GetContentHead(); pItemCont != NULL; pItemCont = pItemCont->GetNext() )
	{
		if ( !pItemCont->IsType(IT_EQ_TRADE_WINDOW) )
			continue;

		CItem *pItemPartner = pItemCont->m_uidLink.ItemFind();
		if ( !pItemPartner )
			continue;

		CChar *pCharPartner = dynamic_cast<CChar *>(pItemPartner->GetParent());
		if ( pCharPartner != pChar )
			continue;

		if ( pItem )
		{
			if ( IsTrigUsed(TRIGGER_DROPON_TRADE) )
			{
				CScriptTriggerArgs Args1(pChar);
				if ( pItem->OnTrigger(ITRIG_DROPON_TRADE, this, &Args1) == TRIGRET_RET_TRUE )
					return false;
			}
			CItemContainer *pCont = dynamic_cast<CItemContainer *>(pItemCont);
			if ( pCont )
				pCont->ContentAdd(pItem);
		}
		return true;
	}

	// Open new trade window
	if ( IsTrigUsed(TRIGGER_TRADECREATE) )
	{
		CScriptTriggerArgs Args(pItem);
		if ( (m_pChar->OnTrigger(CTRIG_TradeCreate, pChar, &Args) == TRIGRET_RET_TRUE) || (pChar->OnTrigger(CTRIG_TradeCreate, m_pChar, &Args) == TRIGRET_RET_TRUE) )
			return false;
	}

	if ( IsTrigUsed(TRIGGER_DROPON_TRADE) && pItem )
	{
		CScriptTriggerArgs Args1(pChar);
		if ( pItem->OnTrigger(ITRIG_DROPON_TRADE, this, &Args1) == TRIGRET_RET_TRUE )
			return false;
	}

	CItem *pItem1 = CItem::CreateBase(ITEMID_Bulletin1);
	if ( !pItem1 )
		return false;

	CItemContainer *pCont1 = static_cast<CItemContainer *>(pItem1);
	if ( !pCont1 )
	{
		DEBUG_ERR(("Item 0%x must be a container type to enable player trading.\n", ITEMID_Bulletin1));
		pItem1->Delete();
		return false;
	}

	CItemContainer *pCont2 = static_cast<CItemContainer *>(CItem::CreateBase(ITEMID_Bulletin1));
	ASSERT(pCont2);

	pCont1->SetName("Trade Window");
	pCont1->SetType(IT_EQ_TRADE_WINDOW);
	pCont1->m_itEqTradeWindow.m_iWaitTime = 0;
	pCont1->m_itEqTradeWindow.m_bCheck = 0;
	pCont1->m_uidLink = pCont2->GetUID();
	m_pChar->LayerAdd(pCont1, LAYER_SPECIAL);

	pCont2->SetName("Trade Window");
	pCont2->SetType(IT_EQ_TRADE_WINDOW);
	pCont2->m_itEqTradeWindow.m_iWaitTime = 0;
	pCont2->m_itEqTradeWindow.m_bCheck = 0;
	pCont2->m_uidLink = pCont1->GetUID();
	pChar->LayerAdd(pCont2, LAYER_SPECIAL);

	PacketTradeAction cmd(SECURE_TRADE_OPEN);
	cmd.prepareContainerOpen(pChar, pCont1, pCont2);
	cmd.send(this);
	cmd.prepareContainerOpen(m_pChar, pCont2, pCont1);
	cmd.send(pChar->m_pClient);

	if ( g_Cfg.m_iFeatureTOL & FEATURE_TOL_VIRTUALGOLD )
	{
		PacketTradeAction cmd2(SECURE_TRADE_UPDATELEDGER);
		if ( m_NetState->isClientVersion(MINCLIVER_TOL) )
		{
			cmd2.prepareUpdateLedger(pCont1, static_cast<DWORD>(m_pChar->m_virtualGold % 1000000000), static_cast<DWORD>(m_pChar->m_virtualGold / 1000000000));
			cmd2.send(this);
		}
		if ( pChar->m_pClient->m_NetState->isClientVersion(MINCLIVER_TOL) )
		{
			cmd2.prepareUpdateLedger(pCont2, static_cast<DWORD>(pChar->m_virtualGold % 1000000000), static_cast<DWORD>(pChar->m_virtualGold / 1000000000));
			cmd2.send(pChar->m_pClient);
		}
	}

	LogOpenedContainer(pCont2);
	pChar->m_pClient->LogOpenedContainer(pCont1);

	if ( pItem )
	{
		if ( IsTrigUsed(TRIGGER_DROPON_TRADE) )
		{
			CScriptTriggerArgs Args1(pChar);
			if ( pItem->OnTrigger(ITRIG_DROPON_TRADE, this, &Args1) == TRIGRET_RET_TRUE )
			{
				pCont1->Delete();
				pCont2->Delete();
				return false;
			}
		}
		pCont1->ContentAdd(pItem, pCont1->GetTopPoint());
	}
	return true;
}