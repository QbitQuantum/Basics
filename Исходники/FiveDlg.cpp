BOOL CFiveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    m_pDlg = NULL;
    CRect rect(0, 0, 200, 200);
    m_Table.CreateEx( WS_EX_CLIENTEDGE, _T("ChessTable"), NULL, WS_VISIBLE | WS_BORDER | WS_CHILD,
        CRect( 0, 0, 401, 478 ), this, IDC_TABLE );
    // 设置双方姓名
    SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    SetDlgItemText( IDC_ST_ENEMY, _T("无玩家加入") );
    // 禁用“再玩”和“离开”
    CMenu *pMenu = GetMenu();
    pMenu->EnableMenuItem( ID_MENU_PLAYAGAIN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );
    pMenu->EnableMenuItem( ID_MENU_LEAVE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );
    // 捕获聊天输入框句柄，供处理回车使用
    m_hChat = FindWindowEx( GetDlgItem( IDC_CMB_CHAT )->GetSafeHwnd(), NULL, _T("Edit"), NULL );
    ::SendMessage( m_hChat, EM_LIMITTEXT, (WPARAM)128, 0);
    m_Table.Clear( TRUE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_HQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );

    GetDlgItem( IDC_TABLE )->SetFocus();
	return FALSE;  // return TRUE  unless you set the focus to a control
}