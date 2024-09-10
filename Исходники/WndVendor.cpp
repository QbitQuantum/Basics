void CWndVendor::OnInitialUpdate()
{
	CWndNeuz::OnInitialUpdate(); 

#if __VER >= 8 // __S8_VENDOR_REVISION
	SetTitle( prj.GetText( TID_GAME_VENDOR_TITLE ) );
	m_wndctrlVendor.Create( WLVS_ICON | WBS_NODRAWFRAME, CRect( 5, 60, 440, 460 ), this, 100 );
#else // __VER >= 8 // __S8_VENDOR_REVISION
	m_wndctrlVendor.Create( WLVS_ICON | WBS_NODRAWFRAME, CRect( 18, 80, 220, 250 ), this, 100 );
#endif // __VER >= 8 // __S8_VENDOR_REVISION
	
	SetVendor( g_pPlayer );
	if( g_pPlayer )
	{
		if( g_pPlayer->IsMode( COMMUNITY_MODE ) )
		{
			Destroy();
		}
	}
#if __VER >= 11 // __SYS_POCKET
	if(GetWndBase( APP_BAG_EX )) GetWndBase( APP_BAG_EX )->Destroy();
#endif
	if( g_WndMng.m_pWndTrade || g_WndMng.m_pWndShop || g_WndMng.m_pWndBank || g_WndMng.m_pWndGuildBank)
	{
		Destroy();
		return;
	}
	
#ifdef __S_SERVER_UNIFY
	if( g_WndMng.m_bAllAction == FALSE )
	{
		Destroy();
		return;
	}
#endif // __S_SERVER_UNIFY
	
#if __VER >= 8 // __S8_PK
	if( g_pPlayer->IsChaotic() )
	{
		CHAO_PROPENSITY Propensity = prj.GetPropensityPenalty( g_pPlayer->GetPKPropensity() );
		if( !Propensity.nVendor )
		{
			g_WndMng.PutString( prj.GetText( TID_GAME_CHAOTIC_NOT_VENDOR ) );
			Destroy();
			return;
		}
	}
#endif // __VER >= 8 // __S8_PK

	if( !m_pVendor->IsActiveMover() )
	{
		CWndButton* pButton	= (CWndButton*)GetDlgItem( WIDC_OK );
		pButton->SetVisible( FALSE );
		pButton	= (CWndButton*)GetDlgItem( WIDC_CANCEL );
		pButton->SetVisible( FALSE );
	}

	ReloadItemList();

	CWndInventory* pWndInventory	= (CWndInventory*)g_WndMng.CreateApplet( APP_INVENTORY );
	CRect rcInventory	= pWndInventory->GetWindowRect( TRUE );
	CRect rcVendor = GetWindowRect( TRUE );
	CPoint ptInventory	= rcInventory.TopLeft();
	CPoint point;
	if( ptInventory.x > m_pWndRoot->GetWndRect().Width() / 2 )
		point	= ptInventory - CPoint( rcVendor.Width(), 0 );
	else
		point	= ptInventory + CPoint( rcInventory.Width(), 0 );
	Move( point ); 
} 