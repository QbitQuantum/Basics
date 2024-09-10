void CWndPiercing::OnInitialUpdate()
{
	CWndNeuz::OnInitialUpdate(); 

	CWndInventory* pWndInventory = (CWndInventory*)g_WndMng.CreateApplet( APP_INVENTORY );
	
	CRect rcInventory	= pWndInventory->GetWindowRect( TRUE );
	CRect rcVendor = GetWindowRect( TRUE );
	CPoint ptInventory	= rcInventory.TopLeft();
	CPoint point;
	if( ptInventory.x > m_pWndRoot->GetWndRect().Width() / 2 )
		point	= ptInventory - CPoint( rcVendor.Width(), 0 );
	else
		point	= ptInventory + CPoint( rcInventory.Width(), 0 );

	Move( point );

	LPWNDCTRL pCustom = NULL;
	pCustom = GetWndCtrl( WIDC_STATIC5 );
	m_Rect[0] = pCustom->rect;
	pCustom = GetWndCtrl( WIDC_STATIC6 );
	m_Rect[1] = pCustom->rect;
	pCustom = GetWndCtrl( WIDC_STATIC7 );
	m_Rect[2] = pCustom->rect;

	CWndStatic* pGoldNum = (CWndStatic*) GetDlgItem( WIDC_STATIC9 );
	pGoldNum->AddWndStyle( WSS_MONEY );
	

	if( g_pPlayer )
		m_pSfx = CreateSfx( g_Neuz.m_pd3dDevice, XI_INT_INCHANT, g_pPlayer->GetPos(), g_pPlayer->GetId(), g_pPlayer->GetPos(), g_pPlayer->GetId(), -1 );
} 