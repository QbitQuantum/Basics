void CWndGuildVote::OnInitialUpdate() 
{ 
	CWndNeuz::OnInitialUpdate(); 
	// 여기에 코딩하세요

	CWndEdit* pEdit;
	
	pEdit = (CWndEdit*) GetDlgItem( WIDC_EDIT1 );
	pEdit->EnableWindow(FALSE);
	pEdit = (CWndEdit*) GetDlgItem( WIDC_EDIT4 );
	pEdit->EnableWindow(FALSE);
	pEdit = (CWndEdit*) GetDlgItem( WIDC_EDIT2 );
	pEdit->EnableWindow(FALSE);
	pEdit = (CWndEdit*) GetDlgItem( WIDC_EDIT5 );
	pEdit->EnableWindow(FALSE);
	pEdit = (CWndEdit*) GetDlgItem( WIDC_EDIT3 );
	pEdit->EnableWindow(FALSE);

	CGuild* pGuild = g_pPlayer->GetGuild();
	if( !pGuild )
	{
		g_WndMng.PutString( "소속된 길드가 없어서 길드투표창을 열 수 없습니다." );
		Destroy();
		return;
	}
	else
	if( !(pGuild->m_nLevel > 7) )
	{
		g_WndMng.PutString( prj.GetText(TID_GAME_GUILDNOTLEVEL) );
		Destroy();
		return;
	}

	CWndComboBox* pCombo = (CWndComboBox*)GetDlgItem(WIDC_COMBOBOX1);

	pCombo->ResetContent();
	
	list <CGuildVote*>::iterator it = pGuild->m_votes.begin();
	
	for ( ; it != pGuild->m_votes.end() ; ++it )
	{
		int nIndex;
		nIndex = pCombo->AddString( (*it)->GetTitle() );
		pCombo->SetItemData( nIndex, (*it)->GetID() );
	}
		
	CWndButton* pWndButton[4];

	pWndButton[ 0 ] = (CWndButton*)GetDlgItem( WIDC_RADIO1 );
	pWndButton[ 1 ] = (CWndButton*)GetDlgItem( WIDC_RADIO2 );
	pWndButton[ 2 ] = (CWndButton*)GetDlgItem( WIDC_RADIO3 );
	pWndButton[ 3 ] = (CWndButton*)GetDlgItem( WIDC_RADIO4 );
	pWndButton[ 0 ]->SetGroup( TRUE );

	// 윈도를 중앙으로 옮기는 부분.
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CPoint point( rectRoot.right - rectWindow.Width(), 110 );
	Move( point );
	MoveParentCenter();
} 