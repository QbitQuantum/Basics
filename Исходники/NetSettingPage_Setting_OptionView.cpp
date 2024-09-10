void CNetSettingPage_Setting_OptionView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	BOOL bNotificationState = TRUE;

	HCURSOR hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

	RETAILMSG(1, (TEXT("[NETUI] CNetSettingPage_Setting_OptionView::OnInitialUpdate() \r\n") ));

	// Apply MenuBar
	memset(&m_mbi, 0, sizeof(SHMENUBARINFO));
	m_mbi.cbSize = sizeof( SHMENUBARINFO );
	m_mbi.hwndParent = m_hWnd;
	m_mbi.dwFlags = SHCMBF_HMENU;
	m_mbi.nToolBarId = IDR_MENU_APPLY_DEFAULT;
	m_mbi.hInstRes = AfxGetInstanceHandle();
	SHCreateMenuBar( &m_mbi );

	
	// Scan Option
	m_comboScanThreshold.AddString(L"All");
	m_comboScanThreshold.AddString(L">=Very Low");
	m_comboScanThreshold.AddString(L">=Low");
	m_comboScanThreshold.AddString(L">=Good");
	m_comboScanThreshold.AddString(L">=Very Good");

	m_comboNettoAccess.AddString(L"Only ADHOC");
	m_comboNettoAccess.AddString(L"Only Access Points");
	m_comboNettoAccess.AddString(L"All Available");


	GetScanOpt(&m_sScanOption);
	

	RETAILMSG(1, (TEXT("[NETUI] GetScanOpt \r\n") ));
	RETAILMSG(1, (TEXT("[NETUI] bTurnOnAvailNetNoti : %d \r\n"), m_sScanOption.bTurnOnAvailNetNoti ));
	RETAILMSG(1, (TEXT("[NETUI] dwScanThreShold : %d \r\n"), m_sScanOption.dwScanThreShold ));
	RETAILMSG(1, (TEXT("[NETUI] tszLockSSID : %s \r\n"), m_sScanOption.tszLockSSID ));
	RETAILMSG(1, (TEXT("[NETUI] dwNetToAccess : %d \r\n"), m_sScanOption.dwNetToAccess ));


	// XML에 해당값이 초기화 되지 않아 -1이 리턴되면 기본 Default 값으로 다시 세팅해준다.
	if(m_sScanOption.dwScanThreShold == -1)
	{
		m_sScanOption.dwScanThreShold = DEFAULT_SCANOPT_SCANTHRESHOLD_VALUE;
	}
	
	if(m_sScanOption.dwNetToAccess == -1)
	{
		m_hwndSink = ::FindWindow( TEXT("SinkWirelessNetUI"), NULL );

		if(m_hwndSink != NULL)
		{
			DWORD dwFlags = (DWORD)::SendMessage(m_hwndSink, SHWZCM_GETSTATE, 0, 0);

			// Success
			dwFlags--;

			m_sScanOption.dwNetToAccess = dwFlags;
		}
		else
		{
			m_sScanOption.dwNetToAccess = DEFAULT_SCANOPT_NETTOACCESS_VALUE;
		}
	}

	
	// xml에서 읽어온 값보다, 현재 동작중인 상태값을 읽어와서 상태가 다를경우 다시 xml 값을 변경해준다.
	
	SHWZCGetNotificationState(&bNotificationState);
	if(bNotificationState != m_sScanOption.bTurnOnAvailNetNoti)
	{
		m_sScanOption.bTurnOnAvailNetNoti = bNotificationState;
	}
	

	SetScanOpt(m_sScanOption);

	m_chkbtnTurnOnAvaNetNofi.SetCheck(m_sScanOption.bTurnOnAvailNetNoti);
	m_comboScanThreshold.SetCurSel(m_sScanOption.dwScanThreShold);
	m_comboNettoAccess.SetCurSel(m_sScanOption.dwNetToAccess);
	SetDlgItemText(IDC_EDIT_LOCK_SSID, m_sScanOption.tszLockSSID);



	// Power Option
	int nAllowValue = -1;
	GetPowerOpt(&nAllowValue);


	// 값 없는 상태에서는 초기값 지정
	if( nAllowValue == -1 )
	{
		SetPowerOpt(TRUE);
		nAllowValue = TRUE;
	}

	if(nAllowValue)
	{
		CheckDlgButton(IDC_CHECK_ALLOW_SUSPEND, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_ALLOW_SUSPEND, BST_UNCHECKED);
	}




	// Initilize Force Restore form Invaild Ping Status
	GetBkgPingCheckOpt(&m_sBkgPingCheckOpt);

	RETAILMSG(1, (TEXT("[NETUI] GetBkgPingCheckOpt \r\n") ));
	RETAILMSG(1, (TEXT("[NETUI] bOperating : %d \r\n"), m_sBkgPingCheckOpt.bOperating ));
	RETAILMSG(1, (TEXT("[NETUI] dwBreakInterval : %d \r\n"), m_sBkgPingCheckOpt.dwBreakInterval ));
	RETAILMSG(1, (TEXT("[NETUI] dwPingInterval : %d \r\n"), m_sBkgPingCheckOpt.dwPingInterval ));
	RETAILMSG(1, (TEXT("[NETUI] dwMaxCheckCount : %d \r\n"), m_sBkgPingCheckOpt.dwMaxCheckCount ));
	RETAILMSG(1, (TEXT("[NETUI] tszCustomDestAddr : %s \r\n"), m_sBkgPingCheckOpt.tszCustomDestAddr ));

	if( GetPingCheckerStatus() )
	{
		CheckDlgButton(IDC_CHECK_FORCE_RESTORE_ENABLE, BST_CHECKED);
		m_sBkgPingCheckOpt.bOperating = TRUE;

		GetDlgItem(IDC_EDIT_SET_PING_BREAKITV)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_PING_PINGITV)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_PING_CHECKMAXCNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_PING_CHECK_DESTADDR)->EnableWindow(FALSE);
		
	}
	else
	{
		CheckDlgButton(IDC_CHECK_FORCE_RESTORE_ENABLE, BST_UNCHECKED);
		m_sBkgPingCheckOpt.bOperating = FALSE;
			
		SetDlgItemInt(IDC_EDIT_SET_PING_BREAKITV, DEFAULT_CHECK_N_BREAK_INTERVAL);
		SetDlgItemInt(IDC_EDIT_SET_PING_PINGITV, DEFAULT_PING_INTERVAL);
		SetDlgItemInt(IDC_EDIT_SET_PING_CHECKMAXCNT, DEFAULT_MAX_CHECK_COUNT);
		SetDlgItemText(IDC_EDIT_SET_PING_CHECK_DESTADDR, _T("")); // Custom 주소가 지정되어있지 않으면 매 체크시마다 DefaultGateWay 검사해서 보낸다.

		GetDlgItem(IDC_EDIT_SET_PING_BREAKITV)->EnableWindow();
		GetDlgItem(IDC_EDIT_SET_PING_PINGITV)->EnableWindow();
		GetDlgItem(IDC_EDIT_SET_PING_CHECKMAXCNT)->EnableWindow();
		GetDlgItem(IDC_EDIT_SET_PING_CHECK_DESTADDR)->EnableWindow();
	}

	// 모두 0일경우(잘못된 값일경우) Default로 세팅
	if( (m_sBkgPingCheckOpt.dwBreakInterval == 0) && (m_sBkgPingCheckOpt.dwPingInterval == 0) && (m_sBkgPingCheckOpt.dwMaxCheckCount == 0) )
	{
		m_sBkgPingCheckOpt.dwBreakInterval = DEFAULT_CHECK_N_BREAK_INTERVAL;
		m_sBkgPingCheckOpt.dwPingInterval = DEFAULT_PING_INTERVAL;
		m_sBkgPingCheckOpt.dwMaxCheckCount = DEFAULT_MAX_CHECK_COUNT;
		memset(m_sBkgPingCheckOpt.tszCustomDestAddr, 0, sizeof(m_sBkgPingCheckOpt.tszCustomDestAddr));

		SetBkgPingCheckOpt(m_sBkgPingCheckOpt);

	}

	SetDlgItemInt(IDC_EDIT_SET_PING_BREAKITV, m_sBkgPingCheckOpt.dwBreakInterval);
	SetDlgItemInt(IDC_EDIT_SET_PING_PINGITV, m_sBkgPingCheckOpt.dwPingInterval);
	SetDlgItemInt(IDC_EDIT_SET_PING_CHECKMAXCNT, m_sBkgPingCheckOpt.dwMaxCheckCount);
	SetDlgItemText(IDC_EDIT_SET_PING_CHECK_DESTADDR, m_sBkgPingCheckOpt.tszCustomDestAddr);

	


	// Get WZC Context Timer Value
	if( QueryWzcContext(&m_wzcContext) == TRUE)
	{
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTP, m_wzcContext.tmTp, FALSE);
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTF, m_wzcContext.tmTf, FALSE);
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTR, m_wzcContext.tmTr, FALSE);
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTC, m_wzcContext.tmTc, FALSE);
	}
	else
	{
		// ERROR
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTP, 0, FALSE);
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTF, 0, FALSE);
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTR, 0, FALSE);
		SetDlgItemInt(IDC_EDIT_CONTEXT_TMTC, 0, FALSE);
	}






	SetCursor(hOldCursor);

}