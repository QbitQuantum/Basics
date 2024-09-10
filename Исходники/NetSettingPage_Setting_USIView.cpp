void CNetSettingPage_Setting_USIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	// 컨트롤 초기화
	// RoamDelta 값은 0, 1, 2만 사용 (use driver default for 1(moderate), convert 0(aggressive) and 2(conservative) )
	m_spinRoamDelta.SetRange(0, 2);

	// PowerSaveMode 값은 0, 1, 2만 사용 ( 0: CAM (constantly awake) / 1: PS  (power-save) / 2: FAST PS mode )
	m_spinPowerSaveMode.SetRange(0, 2);


	// RoamTrigger
	m_comboRoamTrigger.AddString(L"-50");
	m_comboRoamTrigger.AddString(L"-55");
	m_comboRoamTrigger.AddString(L"-60");
	m_comboRoamTrigger.AddString(L"-65");
	m_comboRoamTrigger.AddString(L"-70");
	m_comboRoamTrigger.AddString(L"-71");
	m_comboRoamTrigger.AddString(L"-72");
	m_comboRoamTrigger.AddString(L"-73");
	m_comboRoamTrigger.AddString(L"-74");
	m_comboRoamTrigger.AddString(L"-75");
	m_comboRoamTrigger.AddString(L"-76");
	m_comboRoamTrigger.AddString(L"-77");
	m_comboRoamTrigger.AddString(L"-78");
	m_comboRoamTrigger.AddString(L"-79");
	m_comboRoamTrigger.AddString(L"-80");
	m_comboRoamTrigger.AddString(L"-81");
	m_comboRoamTrigger.AddString(L"-82");
	m_comboRoamTrigger.AddString(L"-83");
	m_comboRoamTrigger.AddString(L"-84");
	m_comboRoamTrigger.AddString(L"-85");
	m_comboRoamTrigger.AddString(L"-86");
	m_comboRoamTrigger.AddString(L"-87");
	m_comboRoamTrigger.AddString(L"-88");
	m_comboRoamTrigger.AddString(L"-89");
	m_comboRoamTrigger.AddString(L"-90");




	HKEY hKey = NULL;
	DWORD dwDisposition = 0;


	// 초기값 레지스트리에서 얻어와서 갱신시켜줌
	// wl 커맨드를 이용하여 USI 드라이버에서 직접 Set/Get을 할 수 있지만, 추가 라이브러리 구현이 필요함
	// 일정상 일단 레지스트리를 이용한 읽어오기 / 적용후 리셋을 이용한 방법 사용하도록 함
	if( RegCreateKeyEx(HKEY_LOCAL_MACHINE, DEFAULT_USI_PARAMS_REG_PATH, 0, NULL, REG_OPTION_NON_VOLATILE, 0, NULL, &hKey, &dwDisposition) == ERROR_SUCCESS )
	{

		DWORD dwType = 0;
		DWORD dwDataSize = 0;
		DWORD dwData = 0;
		TCHAR tszData[128] = {L'\0',};
		LONG lRet = 0;

#if 0 // 현 버전의 USI 드라이버에는 Roam Enable 보는 레지스트리가 잘못 되어있음 (항상 RoamEnable 임)

		//
		// Roam Enable
		//
		dwType = REG_DWORD;
		dwDataSize = sizeof(DWORD);
		lRet = RegQueryValueEx(hKey, L"roam_off", NULL, &dwType, (LPBYTE)&dwData, &dwDataSize);
		if( (lRet != ERROR_SUCCESS) || (dwData<0) )
		{
			dwData = 0; // roam Enable
			
			m_bRoamEnable = TRUE;
			RegSetValueEx(hKey, L"roam_off", 0, REG_DWORD, (LPBYTE)&dwData, sizeof(dwData) );
		}
		else
		{
			if(dwData == 0)
			{
				m_bRoamEnable = TRUE;
			}
			else
			{
				m_bRoamEnable = FALSE;
			}

		}
#endif
		
		//
		// RoamTrigger
		//
		dwType = REG_SZ;
		dwDataSize = sizeof(tszData);
		lRet = RegQueryValueEx(hKey, L"RoamTrigger", NULL, &dwType, (LPBYTE)&tszData, &dwDataSize);
		if( (lRet != ERROR_SUCCESS) || ( _tcslen(tszData) <= 0 ) )
		{
			_tcscpy(tszData, m_strRoamTrigger.GetBuffer(0));
			RegSetValueEx(hKey, L"RoamTrigger", 0, REG_SZ, (LPBYTE)tszData, _tcslen(tszData) * sizeof(TCHAR) );
		}
		else
		{
			m_strRoamTrigger = tszData;
		}

		


		//
		// RoamDelta (use driver default for 1(moderate), convert 0(aggressive) and 2(conservative) )
		//
		dwType = REG_DWORD;
		dwDataSize = sizeof(DWORD);
		lRet = RegQueryValueEx(hKey, L"RoamDelta", NULL, &dwType, (LPBYTE)&dwData, &dwDataSize);
		if( (lRet != ERROR_SUCCESS) || (dwData<0) )
		{
			m_spinRoamDelta.SetPos(DEFAULT_VALUE_ROAMDELTA);
			dwData = m_spinRoamDelta.GetPos();
			RegSetValueEx(hKey, L"RoamDelta", 0, REG_DWORD, (LPBYTE)&dwData, sizeof(dwData) );
		}
		else
		{
			if(dwData != 0 && dwData != 1 && dwData != 2)
			{
				m_spinRoamDelta.SetPos(DEFAULT_VALUE_ROAMDELTA);
			}
			else
			{
				m_spinRoamDelta.SetPos(dwData);
			}
		}


		//
		// RoamScanPrd
		//
		dwType = REG_DWORD;
		dwDataSize = sizeof(DWORD);
		lRet = RegQueryValueEx(hKey, L"RoamScanPrd", NULL, &dwType, (LPBYTE)&dwData, &dwDataSize);
		if( (lRet != ERROR_SUCCESS) || (dwData<0) )
		{
			RegSetValueEx(hKey, L"RoamScanPrd", 0, REG_DWORD, (LPBYTE)&m_dwRoamScanPrd, sizeof(m_dwRoamScanPrd) );
		}
		else
		{
			m_dwRoamScanPrd = dwData;
		}


		//
		// RoamScanFreq
		//
		dwType = REG_DWORD;
		dwDataSize = sizeof(DWORD);
		lRet = RegQueryValueEx(hKey, L"RoamScanFreq", NULL, &dwType, (LPBYTE)&dwData, &dwDataSize);
		if( (lRet != ERROR_SUCCESS) || (dwData<0) )
		{
			RegSetValueEx(hKey, L"RoamScanFreq", 0, REG_DWORD, (LPBYTE)&m_dwRoamScanFreq, sizeof(m_dwRoamScanFreq) );
		}
		else
		{
			m_dwRoamScanFreq = dwData;
		}


		//
		// FullRoamScanInterval
		//
		dwType = REG_DWORD;
		dwDataSize = sizeof(DWORD);
		lRet = RegQueryValueEx(hKey, L"FullRoamScanInterval", NULL, &dwType, (LPBYTE)&dwData, &dwDataSize);
		if( (lRet != ERROR_SUCCESS) || (dwData<0) )
		{
			RegSetValueEx(hKey, L"FullRoamScanInterval", 0, REG_DWORD, (LPBYTE)&m_dwFullRoamScanInterval, sizeof(m_dwFullRoamScanInterval) );
		}
		else
		{
			m_dwFullRoamScanInterval = dwData;
		}








		//
		// PowerSaveMode
		//
		dwType = REG_DWORD;
		dwDataSize = sizeof(DWORD);
		lRet = RegQueryValueEx(hKey, L"PowerSaveMode", NULL, &dwType, (LPBYTE)&dwData, &dwDataSize);
		
		RETAILMSG(1, (TEXT("[NETUI] PowerSaveMode(%d) \r\n"),dwData ));

		if( (lRet != ERROR_SUCCESS) || (dwData<0) )
		{
			m_spinPowerSaveMode.SetPos(DEFAULT_VALUE_POWERSAVEMODE);
			dwData = m_spinPowerSaveMode.GetPos();
			RegSetValueEx(hKey, L"PowerSaveMode", 0, REG_DWORD, (LPBYTE)&dwData, sizeof(dwData) );
		}
		else
		{
			if(dwData != 0 && dwData != 1 && dwData != 2)
			{
				m_spinPowerSaveMode.SetPos(DEFAULT_VALUE_POWERSAVEMODE);
			}
			else
			{
				m_spinPowerSaveMode.SetPos(dwData);
			}
		}





		RegCloseKey(hKey);
	}


#if 0 // 현 버전의 USI 드라이버에는 Roam Enable 보는 레지스트리가 잘못 되어있음 (항상 RoamEnable 임)
	// Set Data to Controls
	if(m_bRoamEnable)
	{
		CheckDlgButton(IDC_CHECK_ROAM_ENABLE, BST_CHECKED);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_ROAM_ENABLE, BST_UNCHECKED);
	}
#else
	CheckDlgButton(IDC_CHECK_ROAM_ENABLE, BST_CHECKED);
	GetDlgItem(IDC_CHECK_ROAM_ENABLE)->EnableWindow(FALSE);
#endif


	// 콤보 박스 선택을 위한 비교
	for(int i = 0; i< m_comboRoamTrigger.GetCount(); i++)
	{
		TCHAR tszTemp[32] = L"";

		m_comboRoamTrigger.GetLBText(i, tszTemp);
		if( _tcscmp(tszTemp, m_strRoamTrigger.GetBuffer(0)) == 0)
		{
			m_comboRoamTrigger.SetCurSel(i);
			break;
		}
	}

	SetDlgItemInt(IDC_EDIT_ROAM_SCANFREQ, m_dwRoamScanFreq);
	SetDlgItemInt(IDC_EDIT_ROAM_SCANPRD, m_dwRoamScanPrd);
	SetDlgItemInt(IDC_EDIT_ROAM_FULLROAMSCNITV, m_dwFullRoamScanInterval);
	
}