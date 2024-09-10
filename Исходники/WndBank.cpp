void CWndBank::OnInitialUpdate() 
{ 
	CWndNeuz::OnInitialUpdate(); 
#if __VER >= 11 // __SYS_POCKET
	if(GetWndBase( APP_BAG_EX )) GetWndBase( APP_BAG_EX )->Destroy();
#endif
	if( g_WndMng.m_pWndTrade || g_WndMng.m_pWndShop || g_WndMng.m_pWndGuildBank || g_WndMng.GetWndVendorBase() )
	{
		Destroy();
		return;
	}

	CWndTabCtrl* pTabCtrl = (CWndTabCtrl*) GetDlgItem( WIDC_BANK_0 );
	
	m_wndItemCtrl[0].Create( WLVS_ICON, CRect( 0, 0, 250, 250 ), pTabCtrl, 11 );
	m_wndItemCtrl[0].InitItem( &g_pPlayer->m_Bank[0], APP_COMMON_BANK );

	CWndTabCtrl* pTabCtrl1 = (CWndTabCtrl*) GetDlgItem( WIDC_BANK_1 );

	m_wndItemCtrl[1].Create( WLVS_ICON, CRect( 0, 0, 250, 250 ), pTabCtrl1, 11 );
	m_wndItemCtrl[1].InitItem( &g_pPlayer->m_Bank[1], APP_COMMON_BANK );

	CWndTabCtrl* pTabCtrl2 = (CWndTabCtrl*) GetDlgItem( WIDC_BANK_3 );
	
	m_wndItemCtrl[2].Create( WLVS_ICON, CRect( 0, 0, 250, 250 ), pTabCtrl2, 11 );
	m_wndItemCtrl[2].InitItem( &g_pPlayer->m_Bank[2], APP_COMMON_BANK );

	WTCITEM tabTabItem;
	
	tabTabItem.mask = WTCIF_TEXT | WTCIF_PARAM;
	tabTabItem.pszText = prj.GetText(TID_GAME_ITEM);//"아이템";
	tabTabItem.pWndBase = &m_wndItemCtrl[0];
	pTabCtrl->InsertItem( 0, &tabTabItem );

	tabTabItem.pWndBase = &m_wndItemCtrl[1];
	pTabCtrl1->InsertItem( 0, &tabTabItem );

	
	tabTabItem.pWndBase = &m_wndItemCtrl[2];
	pTabCtrl2->InsertItem( 0, &tabTabItem );
	

	LPWNDCTRL lpWndCtrl = GetWndCtrl( WIDC_BANKGO_0 );
	m_wndGold[0].Create( "g", WBS_NODRAWFRAME, lpWndCtrl->rect, this, WIDC_BANKGO_0 );
	m_wndGold[0].AddWndStyle( WBS_NODRAWFRAME );

	lpWndCtrl = GetWndCtrl( WIDC_BANKGO_1 );
	m_wndGold[1].Create( "g", WBS_NODRAWFRAME, lpWndCtrl->rect, this, WIDC_BANKGO_1 );
	m_wndGold[1].AddWndStyle( WBS_NODRAWFRAME );

	lpWndCtrl = GetWndCtrl( WIDC_BANKGO_2 );
	m_wndGold[2].Create( "g", WBS_NODRAWFRAME, lpWndCtrl->rect, this, WIDC_BANKGO_2 );
	m_wndGold[2].AddWndStyle( WBS_NODRAWFRAME );

	pCost[0] = (CWndStatic*) GetDlgItem( WIDC_BANKGOLD_0 );
	pCost[1] = (CWndStatic*) GetDlgItem( WIDC_BANKGOLD_1 );
	pCost[2] = (CWndStatic*) GetDlgItem( WIDC_BANKGOLD_2 );

	ReSetBank();
	
	RectItemCtrl[0] = pTabCtrl->m_rectClient + CRect( -3, 2, -18, -20 );
	RectItemCtrl[1] = pTabCtrl1->m_rectClient + CRect( -3, 2, -19, -20 );
	RectItemCtrl[2] = pTabCtrl2->m_rectClient + CRect( -3, 2, -20, -20 );

	CWndInventory* pWndInventory = (CWndInventory*)GetWndBase( APP_INVENTORY );
	CRect rectInventory = pWndInventory->GetWindowRect( TRUE );
	CPoint ptInventory = rectInventory.TopLeft();
	CPoint ptMove;

	if( ptInventory.x > m_pWndRoot->GetWndRect().Width() / 2 )
		ptMove = ptInventory - CPoint( (int)( rectInventory.Width() * 2.525 ), 0 );
	else
		ptMove = ptInventory + CPoint( rectInventory.Width(), 0 );
	Move( ptMove );

	m_pTexture = m_textureMng.AddTexture( m_pApp->m_pd3dDevice,  MakePath( DIR_THEME, "WndCommonBankNotUse.tga" ), 0xffff00ff );
} 