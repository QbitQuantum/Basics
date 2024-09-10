void CWndRepairItem::OnInitialUpdate() 
{ 
	CWndNeuz::OnInitialUpdate(); 
	// 여기에 코딩하세요

	memset( m_adwIdRepair, 0xff, sizeof(m_adwIdRepair) );
	m_dwCost = 0;

//	CWndTabCtrl* pTabCtrl = (CWndTabCtrl*) GetDlgItem( WIDC_INVENTORY );

	CWndEdit* pWndEdit = (CWndEdit*) GetDlgItem( WIDC_EDIT1 );
	pWndEdit->EnableWindow( FALSE );

	pWndStaticCost = (CWndStatic*) GetDlgItem( WIDC_STATIC3 );

	m_wndItemCtrl.Create( WLVS_ICON | WBS_NODRAWFRAME, CRect( 6, 24, 174, 192 ), this, 11 );
	m_wndItemCtrl.InitItem( m_adwIdRepair );

//	pRepairItem.SetItemContainer( ITYPE_ITEM, MAX_REPAIR );
//	m_wndItemCtrl.InitItem( &pRepairItem, APP_REPAIR );
//	WTCITEM tabTabItem;
//	tabTabItem.mask = WTCIF_TEXT | WTCIF_PARAM;
//	tabTabItem.pszText = "아이템";
//	tabTabItem.pWndBase = &m_wndItemCtrl;
//	pTabCtrl->InsertItem( 0, &tabTabItem );

	CWndInventory* pWndInventory = (CWndInventory*)g_WndMng.CreateApplet( APP_INVENTORY );
	CRect rectInventory = pWndInventory->GetWindowRect( TRUE );
	CPoint ptInventory = rectInventory.TopLeft();
	CPoint ptMove;
	
	if( ptInventory.x > m_pWndRoot->GetWndRect().Width() / 2 )
		ptMove = ptInventory - CPoint( rectInventory.Width(), 0 );
	else
		ptMove = ptInventory + CPoint( rectInventory.Width(), 0 );
	Move( ptMove );
/*		CRect rectRoot = m_pWndRoot->GetLayoutRect();
		CRect rectWindow = GetWindowRect();
		CPoint point( rectRoot.right - rectWindow.Width(), 110 );
		Move( point );
		MoveParentCenter();
*/
} 