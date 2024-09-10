void CWndGuildBank::OnInitialUpdate() 
{ 
	CWndNeuz::OnInitialUpdate(); 
	// 여기에 코딩하세요
#if __VER >= 11 // __SYS_POCKET
	if(GetWndBase( APP_BAG_EX )) GetWndBase( APP_BAG_EX )->Destroy();
#endif
	if( g_WndMng.m_pWndTrade || g_WndMng.m_pWndShop || g_WndMng.m_pWndBank || g_WndMng.GetWndVendorBase() )
	{
		Destroy();
		return;
	}

	
	CWndStatic* pCost = (CWndStatic*) GetDlgItem( WIDC_GUILDBANK_NUM );
	pCost->AddWndStyle(WSS_MONEY);

	CWndTabCtrl* pTabCtrl = reinterpret_cast<CWndTabCtrl*>(GetDlgItem(WIDC_TABCTRL1));
	
	m_wndItemCtrl.Create( WLVS_ICON, CRect( 0, 0, 250, 250 ), pTabCtrl, 11 );
	m_wndItemCtrl.InitItem( &g_pPlayer->GetGuild()->m_GuildBank, APP_GUILD_BANK );

	WTCITEM tabTabItem;
	
	tabTabItem.mask = WTCIF_TEXT | WTCIF_PARAM;
	tabTabItem.pszText = prj.GetText(TID_GAME_ITEM);//"아이템";
	tabTabItem.pWndBase = &m_wndItemCtrl;
	pTabCtrl->InsertItem( 0, &tabTabItem );
	
	LPWNDCTRL lpWndCtrl = GetWndCtrl( WIDC_CUSTOM1 );
	m_wndGold.Create( "g", WBS_NODRAWFRAME, lpWndCtrl->rect, this, WIDC_CUSTOM1 );
	m_wndGold.AddWndStyle( WBS_NODRAWFRAME );

	CGuild *pGuild = g_pPlayer->GetGuild();
	if( pGuild )
	{
		if(	pGuild->IsMaster( g_pPlayer->m_idPlayer ) == FALSE )	// 길마가 아니면 
		{
			CWndButton* pWndButt = (CWndButton*)GetDlgItem(WIDC_BUTTON2);	// 망토제작 버튼을 disable 시킨다.
			pWndButt->EnableWindow( FALSE );
		}
	}


#ifdef __GLDISABLE
	CWndButton* pWndButt = (CWndButton*)GetDlgItem(WIDC_BUTTON1);
	pWndButt->EnableWindow( FALSE );
#endif	

	CWndInventory* pWndInventory = (CWndInventory*)GetWndBase( APP_INVENTORY );
	CRect rectInventory = pWndInventory->GetWindowRect( TRUE );
	CPoint ptInventory = rectInventory.TopLeft();
	CPoint ptMove;
	
	CRect rect = GetWindowRect( TRUE );
	
	if( ptInventory.x > rect.Width() / 2 )
		ptMove = ptInventory - CPoint( rect.Width(), 0 );
	else
		ptMove = ptInventory + CPoint( rectInventory.Width(), 0 );
	
	Move( ptMove );

	if( pGuild )
	{
		CWndButton* pWndButt = (CWndButton*)GetDlgItem(WIDC_BUTTON3);

#if __VER >= 8 // __GUILDCOMBAT_85
		pWndButt->EnableWindow(FALSE);
		pWndButt->SetVisible(FALSE);
#else // __VER >= 8
		if( g_GuildCombatMng.m_uWinGuildId == pGuild->GetGuildId()  )
			pWndButt->EnableWindow(TRUE);
		else
			pWndButt->EnableWindow(FALSE);
#endif // __VER >= 8
	}

#if __VER >= 11 // __GUILD_BANK_LOG
	CWndButton* pWndButtLog = (CWndButton*)GetDlgItem(WIDC_LOG);
	pWndButtLog->EnableWindow(TRUE);
	pWndButtLog->SetVisible(TRUE);
#else //__GUILD_BANK_LOG
	//CWndButton* pWndButtLog = (CWndButton*)GetDlgItem(WIDC_LOG);
	//pWndButtLog->EnableWindow(FALSE);
	//pWndButtLog->SetVisible(FALSE);
#endif //__GUILD_BANK_LOG
} 