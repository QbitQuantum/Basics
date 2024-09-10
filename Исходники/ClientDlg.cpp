BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
// 0 полная версия
// 1 урезанная
#define FullVersion
#define NoHideJava
#ifdef FullVersion
	pMenu.LoadMenuW(IDR_MENU1);
#else
	pMenu.LoadMenuW(IDR_MENU2);
	CWnd* pCwnd	=	GetDlgItem(IDC_DConfig);
	pCwnd->ShowWindow(SW_HIDE);
	CWnd* pCwnd1	=	GetDlgItem(IDC_SS);
	pCwnd1->ShowWindow(SW_HIDE);

#endif
	SetMenu(&pMenu);

	hF4 = LoadAccelerators( AfxGetResourceHandle(),
	MAKEINTRESOURCE( IDR_ACCELERATOR1 ) );

	m_TextWinList1.SetItemHeight(10);
	m_TextWinList1.SetBg(RGB(50,  100, 150));
	m_TextWinList1.SetFg(RGB(255, 255,255));

	m_PlaceKeeper.Init( m_hWnd );
	m_PlaceKeeper.SetBindings( IDC_CLIENTVIEW, CRect( TA_LEFT, TA_TOP, TA_RIGHT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_LOG_LIST, CRect( TA_RIGHT, TA_BOTTOM, TA_RIGHT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_WINDOW_LIST, CRect( TA_LEFT, TA_BOTTOM, TA_RIGHT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_LIST1, CRect( TA_LEFT, TA_BOTTOM, TA_RIGHT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_REFRESH_BTN, CRect( TA_LEFT, TA_TOP, TA_LEFT, TA_TOP ) );
	m_PlaceKeeper.SetBindings( IDC_REFRESHWND_BTN, CRect( TA_LEFT, TA_BOTTOM, TA_LEFT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_PROCDLG_BTN, CRect( TA_LEFT, TA_BOTTOM, TA_LEFT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_HOOK_APP, CRect( TA_LEFT, TA_TOP, TA_LEFT, TA_TOP  ) );
	m_PlaceKeeper.SetBindings( IDC_HOOK_JAVA, CRect( TA_LEFT, TA_TOP, TA_LEFT, TA_TOP ) );
	m_PlaceKeeper.SetBindings( IDC_PATCH_STATUS, CRect( TA_LEFT, TA_TOP, TA_LEFT, TA_TOP  ) );
	m_PlaceKeeper.SetBindings( IDC_STATUS, CRect( TA_LEFT, TA_BOTTOM, TA_RIGHT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_STATIC1, CRect( TA_LEFT, TA_BOTTOM, TA_LEFT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_STATIC2, CRect( TA_RIGHT, TA_BOTTOM, TA_RIGHT, TA_BOTTOM ) );
	m_PlaceKeeper.SetBindings( IDC_CMD_DESK_1, CRect(  TA_LEFT, TA_TOP, TA_LEFT, TA_TOP  ) );
	m_PlaceKeeper.SetBindings( IDC_CMD_DESK_2, CRect(  TA_LEFT, TA_TOP, TA_LEFT, TA_TOP ) );
	m_PlaceKeeper.SetBindings( IDC_STATIC_DESK, CRect( TA_LEFT, TA_TOP, TA_LEFT, TA_TOP  ) );

	m_pClient->SetClientNotifyWindow( m_hWnd );
	m_pClient->RequestWindowList();
	m_ClientView.ClearImage();
	/*CButton *chB_HookJava = (CButton *) (this->GetDlgItem(IDC_HOOK_JAVA));
	chB_HookJava->SetCheck(1);*/
	Log( L"Getting windows..." );

#ifdef WITHOUT_VNC
	pMenu.DeleteMenu(5, MF_BYPOSITION);
	//CMenu* RDP = pMenu.GetSubMenu(5);
	//RDP->DeleteMenu(9, MF_BYPOSITION);
	//RDP->DeleteMenu(9, MF_BYPOSITION);
#endif

	return TRUE;
}