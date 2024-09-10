void CWndChat::OnInitialUpdate()
{
	CWndNeuz::OnInitialUpdate();

#ifdef __CHAT_V19
	CWndButton* pWndLock = (CWndButton*)GetDlgItem( WIDC_CHECK1 );
	CWndButton* pWndLog = (CWndButton*)GetDlgItem( WIDC_CHECK3 );
	CWndButton* pWndMoveLock = (CWndButton*)GetDlgItem( WIDC_MOVELOCK );
	CWndButton* pWndHelp = (CWndButton*)GetDlgItem( WIDC_HELP );
	CWndButton* pWndCheck = (CWndButton*)GetDlgItem( WIDC_RADIO6 );
	pWndLock->SetVisible( false );
	pWndLog->SetVisible( true );
	pWndMoveLock->SetVisible( false );
	pWndHelp->SetVisible( false );
	pWndCheck->SetVisible(false);
#endif //__CHAT_V19

	//AddWndStyle( WBS_THICKFRAME );

	m_timerDobe.Set( SEC( 5 ) );

	LPWNDCTRL lpWndCtrl = GetWndCtrl( WIDC_MACRO_CHAT );
	LPWNDCTRL lpWndText = GetWndCtrl( WIDC_CUSTOM1 );
	m_wndMacroChat.Create( "g", WBS_NODRAWFRAME, lpWndCtrl->rect, this, WIDC_MACRO_CHAT );
	m_wndMacroChat.AddWndStyle( WBS_NODRAWFRAME );

	lpWndCtrl = GetWndCtrl( WIDC_EDIT );
	m_wndEdit.Create( g_Neuz.GetSafeHwnd(), WBS_NODRAWFRAME, lpWndCtrl->rect, this, WIDC_EDIT );
	m_wndText.Create( WBS_NOFRAME | WBS_NODRAWFRAME | WBS_VSCROLL, lpWndText->rect, this, WIDC_TEXT );
	CWndText* pWndText = (CWndText*)GetDlgItem( WIDC_TEXT );
	CWndEdit* pWndHead = (CWndEdit*)GetDlgItem( WIDC_HEAD );
	CWndEdit* pWndEdit = (CWndEdit*)GetDlgItem( WIDC_EDIT );

	if( g_pPlayer->IsAuthHigher( AUTH_GAMEMASTER ) )
	{
		pWndText->m_bEnableClipboard = TRUE;
		pWndHead->m_bEnableClipboard = TRUE;
		pWndEdit->m_bEnableClipboard = TRUE;
	}
	pWndEdit->SetNativeMode();

#if __VER >= 11 // __CSC_VER11_1
	CRect rectEdit = m_wndEdit.GetWndRect();
	rectEdit.left = rectEdit.left - 90;
	m_wndEdit.SetWndRect( rectEdit );

	CRect customRect = lpWndCtrl->rect;
	CWndCustom* pCustom = (CWndCustom*)GetDlgItem(WIDC_MACRO_CHAT);
	if(pCustom)
#ifdef __CHAT_V19
		pCustom->Move(customRect.TopLeft().x - 112, customRect.TopLeft().y - 2);
#else
		pCustom->Move(customRect.TopLeft().x - 119, customRect.TopLeft().y);
		pWndEdit->Move(customRect.TopLeft().x + 105, customRect.bottom + 30);
#endif //__CHAT_V19
	if(pWndHead)
	{
		pWndHead->EnableWindow(FALSE);
		pWndHead->SetVisible(FALSE);
	}
#endif //__CSC_VER11_1
	if( g_Option.m_nInstantHelp )
	{
		CScript	s;
		s.Load( MakePath( DIR_CLIENT, "InstantHelp.inc" ) );
		s.GetToken();
		while( s.tok != FINISHED )
		{
			m_strArray.Add( s.Token );
			s.GetToken();
		}
	}
	//m_strArray.

/*
	CRect rect = GetClientRect();
	rect.top = rect.bottom - 20;
	rect.right = 70;
	rect.left += 5;
	rect.DeflateRect( 1, 1 );
	m_wndBeginning.Create( g_Neuz.GetSafeHwnd(), WBS_NODRAWFRAME, rect, this, 1000);

	rect = GetClientRect();
	rect.top = rect.bottom - 20;
	rect.left = 75;
	rect.right -= 134;
	rect.DeflateRect( 1, 1 );
	//rect.left = rect.Width() * 20 / 100;
	//m_wndEdit.AddWndStyle( WBS_NODRAWFRAME );
	m_wndEdit.Create( g_Neuz.GetSafeHwnd(), WBS_NODRAWFRAME, rect, this, 1001 );
*/
//	m_texEdit.LoadTexture( m_pApp->m_pd3dDevice, MakePath( DIR_THEME, "WndChat2.bmp" ), 0xffff00ff, TRUE );
/*
	rect = GetClientRect();
	rect.top = rect.bottom - 20;
	rect.left = rect.right - 134;
	rect.right = r mnnnnft + 15;
	rect.DeflateRect( 1, 1 );
	m_wndShout.Create( " ", 0, rect, this, 1010 );

	rect = GetClientRect();
	rect.top = rect.bottom - 20;
	rect.left = rect.right - 117;
	rect.right = rect.left + 15;
	rect.DeflateRect( 1, 1 );
	m_wndParty.Create( " ", 0, rect, this, 1011 );
*/

/*
	m_wndText.AddWndStyle( WBS_VSCROLL );
	m_wndText.AddWndStyle( WBS_NOFRAME );
	m_wndText.AddWndStyle( WBS_NODRAWFRAME );
	m_wndText.Create( 0, rect, this, 1003 ); 
	m_wndText.SetFont( g_Neuz.m_Theme.m_pFontChat );
	m_wndText.m_string.Reset( m_pFont, &rect);
*/
/*
	rect = GetClientRect();
	rect.left = rect.right - 100;
	//rect.bottom -= 80;
	rect.DeflateRect( 1, 1 );
	m_wndReceiver.AddWndStyle( WBS_VSCROLL );
	m_wndReceiver.AddWndStyle( WBS_NOFRAME );
	m_wndReceiver.Create( EBS_AUTOVSCROLL, rect, this, 1002 );
	m_wndReceiver.AddString( "Vampyre\n" );
	m_wndReceiver.AddString( "Xuzhu\n" );
	m_wndReceiver.AddString( "Zodiacus\n" );
	m_wndReceiver.AddString( "Jeff\n" );
	m_wndReceiver.m_string.Reset( m_pFont, &rect);
*/

	//CWndText* pWndText = (CWndText*)GetDlgItem( WIDC_TEXT );
	SetChannel();
	CWndButton* pWndRadio1 = (CWndButton*)GetDlgItem( WIDC_RADIO1 );
	CWndButton* pWndRadio2 = (CWndButton*)GetDlgItem( WIDC_RADIO2 );
	CWndButton* pWndRadio3 = (CWndButton*)GetDlgItem( WIDC_RADIO3 );
	CWndButton* pWndRadio4 = (CWndButton*)GetDlgItem( WIDC_RADIO4 );
	CWndButton* pWndRadio5 = (CWndButton*)GetDlgItem( WIDC_RADIO5 );
	if( m_nChatChannel == CHATSTY_GENERAL ) pWndRadio1->SetCheck( TRUE );	else
	if( m_nChatChannel == CHATSTY_WHISPER ) pWndRadio2->SetCheck( TRUE );	else
	if( m_nChatChannel == CHATSTY_SHOUT   ) pWndRadio3->SetCheck( TRUE );	else
	if( m_nChatChannel == CHATSTY_PARTY   ) pWndRadio4->SetCheck( TRUE );	else
	if( m_nChatChannel == CHATSTY_GUILD   ) pWndRadio5->SetCheck( TRUE );
	//pWndText->m_string.Init(
	//pWndText->m_string = g_WndMng.m_ChatString;
	pWndText->m_nLineSpace = 2;
	//pWndText->m_string.Reset( m_pFont, &pWndText->GetClientRect() );
	
	//pWndText->
	/*
	CRect rect = GetClientRect();
	rect.bottom -= 20;
	rect.right -= 0;//100;
	rect.DeflateRect( 1, 1);
	m_wndText.SetWndRect( rect );
*/
	//LPBYTE m_wndChatEdit[3];
	//CSize sizeWndChatEdit[3];
#if __VER >= 11 // __CSC_VER11_1
	LoadTGA( MakePath( DIR_THEME, "WndChatEdit00_1.tga" ), &m_wndChatEdit[0] );
#else //__CSC_VER11_1
	LoadTGA( MakePath( DIR_THEME, "WndChatEdit00.tga" ), &m_wndChatEdit[0] );
#endif //__CSC_VER11_1
	LoadTGA( MakePath( DIR_THEME, "WndChatEdit01.tga" ), &m_wndChatEdit[1] );
#ifdef __LANG_IME_0327
	LoadTGA( MakePath( DIR_THEME,  ::GetLanguage(), "WndChatEdit02.tga" ), &m_wndChatEdit[2] );
#else	// __LANG_IME_0327
	LoadTGA( MakePath( DIR_THEME, "WndChatEdit02.tga" ), &m_wndChatEdit[2] );
#endif	// __LANG_IME_0327

	if( m_wndChatEdit[2].lpData == NULL )
	{
		Error( "CWndChat::OnInitialUpdate() m_wndChatEdit[2].lpData = NULL" );
		return;
	}
/*
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CPoint point( 154, rectRoot.bottom - rectWindow.Height() );
	Move( point );
*/
#ifndef __CHAT_V19
	CWndButton* pWndLock = (CWndButton*)GetDlgItem( WIDC_CHECK1 );
	pWndLock->SetCheck( m_bChatLock );
	CWndButton* pWndMoveLock = (CWndButton*)GetDlgItem( WIDC_MOVELOCK );
	pWndMoveLock->SetCheck( m_bMoveLock );
#endif //__CHAT_V19
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rect = GetWindowRect();
	int nWidth  = rect.Width(); 
	int nHeight = rect.Height(); 
	int x = 0;//rectRoot.left + (rectRoot.Width()  / 2) - (nWidth  / 2);
	int y = rectRoot.bottom - nHeight;	
	CPoint point( x, y );
	Move( point );

	m_timerInputTimeOut.Set( SEC( 300 ) );

#if __VER >= 8 //__Y_CHAT_SYSTEM_8
	if( g_WndMng.m_pWndChatLog == NULL )
	{
		g_WndMng.m_pWndChatLog = new CWndChatLog;
		
		if( g_WndMng.m_pWndChatLog )
		{
			g_WndMng.m_pWndChatLog->Initialize( NULL, APP_CHAT_LOG );
			
			CRect rectRoot = m_pWndRoot->GetLayoutRect();
			CRect rect = GetWindowRect(TRUE);
			CRect rect2 = g_WndMng.m_pWndChatLog->GetClientRect(TRUE);
			
			int x = 0;
			int y = rect.top;
			
			if( (rect.right+rect2.Width()) < rectRoot.right )
				x = rect.right;
			else
				x = (rect.left - rect2.Width() );
			
			CPoint point( x, y );
			g_WndMng.m_pWndChatLog->Move( point );

			g_WndMng.m_pWndChatLog->SetVisible(FALSE);
		}
	}

	if( g_WndMng.m_pWndChatLog )
	{
		CWndButton* pWndCheck3  = (CWndButton*)GetDlgItem( WIDC_CHECK3 );
		if( pWndCheck3 )
			pWndCheck3->SetCheck(g_WndMng.m_pWndChatLog->m_bVisible);
	}
#endif //__Y_CHAT_SYSTEM_8
}