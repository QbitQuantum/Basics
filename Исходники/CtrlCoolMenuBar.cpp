void CCoolMenuBarCtrl::SetMenu(HMENU hMenu)
{
	m_hMenu = hMenu;
	
	Clear();
	
	if ( ! m_hMenu ) return;
	
	CMenu pMenu;
	pMenu.Attach( m_hMenu );
	
	for ( UINT nItem = 0 ; nItem < pMenu.GetMenuItemCount() ; nItem++ )
	{
		CString strMenu;
		pMenu.GetMenuString( nItem, strMenu, MF_BYPOSITION );
		
		int nAmp = strMenu.Find( '&' );
		if ( nAmp >= 0 ) strMenu = strMenu.Left( nAmp ) + strMenu.Mid( nAmp + 1 );
		
		CCoolBarItem* pItem = new CCoolBarItem( this, nItem + 1 );
		pItem->SetText( _T(" ") + strMenu + _T(" ") );
		m_pItems.AddTail( pItem );
	}
	
	pMenu.Detach();
}