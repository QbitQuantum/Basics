BOOL CWndShopCtrl::OnDropIcon( LPSHORTCUT pShortcut, CPoint point )
{
	CWndBase* pWndFrame =  pShortcut->m_pFromWnd->GetFrameWnd();
	if( pWndFrame->GetWndId() != APP_SHOP_ )
		return FALSE;

	if( pShortcut->m_dwShortcut == SHORTCUT_ITEM )
	{
		CItemElem* pItemElem = (CItemElem*)pShortcut->m_dwData;
		DWORD nTempCost = 0;
		if( m_nTabType == 0)
		{
			nTempCost += pItemElem->GetCost();
			nTempCost = static_cast< int >( static_cast< float >( nTempCost ) * prj.m_fShopBuyRate );

			if(CTax::GetInstance()->IsApplyTaxRate( g_pPlayer, pItemElem ))
				nTempCost += ( static_cast<DWORD>(nTempCost * CTax::GetInstance()->GetPurchaseTaxRate( g_pPlayer )) );
		}
		else if( m_nTabType == 1 || m_nTabType == 2 )
			nTempCost += pItemElem->GetChipCost();

		nTempCost = (int)((float)nTempCost * prj.m_fShopCost );
		
		if( pItemElem && pItemElem->m_dwItemId == II_SYS_SYS_SCR_PERIN )
			nTempCost = PERIN_VALUE;

		if( nTempCost > INT_MAX )
			return FALSE;

		for( int i = 0; i < MAX_CART; i++ )
		{
			int x = i % 6;
			int y = i / 6;			
			CRect rectHittest = CRect( x * 35, y * 35 + 3, x * 35 + 35, y * 35 + 35 + 3);
			if( rectHittest.PtInRect( point ) )
			{
				m_nLastPoint = i;
				break;
			}
		}
		CWndBase* pParent = (CWndBase*)GetParentWnd();
		pParent->OnChildNotify( WIN_ITEMDROP, m_nIdWnd, (LRESULT*)pShortcut ); 
		return TRUE;
	}

	return FALSE;
}