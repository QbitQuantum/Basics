void CUserMeetingDlg::OnMyGroup()
{
	CMenu pMenu;
	pMenu.CreatePopupMenu();
	
	if ( m_pXML ) CreateMenuGroup( m_pXML, pMenu );
	
	HMENU hMenu = CreatePopupMenu();
	AppendMenu( pMenu, MF_STRING, MIN_GROUP - 1, _T("我的所有成员") );
	
	CRect rcButton;
	m_wndMember.GetWindowRect( &rcButton );
	
	DWORD nFlags = TPM_LEFTALIGN | TPM_VERTICAL | TPM_RIGHTBUTTON;
	
	if ( UINT nMenuID = pMenu.TrackPopupMenu(nFlags | TPM_RETURNCMD, rcButton.left, rcButton.bottom, this) )
	{
		if ( nMenuID == MIN_GROUP - 1 )
		{
			CString strText;
			m_wndGroup.GetWindowText( strText );
			
			CString str;
			str.Format( "是否发布\"%s\"内的所有成员?", strText );
			
			if (AfxMessageBox(str, MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2) == IDOK)
			{
				CMenu* pSubMenu = pMenu.GetSubMenu( pMenu.GetMenuItemCount() - 2 );
				if ( pSubMenu ) PutIntoPhone( pSubMenu->GetSafeHmenu(), 0, pSubMenu->GetMenuItemCount() );
			}
		}
		else
		{
			PutIntoPhone( pMenu, nMenuID );
		}
	}
}