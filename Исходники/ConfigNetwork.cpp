void CConfigNetwork::GetConfig()
{
	if (!m_pDev || m_bInited)
	{
		return;
	}
	
	while (m_ethernetsel.GetCount() > 0)
	{
		m_ethernetsel.DeleteString(0);
	}

	BOOL bRet = FALSE;
	DWORD retlen = 0;
	bRet = CLIENT_GetDevConfig(m_pDev->LoginID, DH_DEV_DEVICECFG, 0,
								&m_sysCFG, sizeof(DHDEV_SYSTEM_ATTR_CFG), &retlen, CONFIG_WAITTIME*4);
	if (!bRet || retlen != sizeof(DHDEV_SYSTEM_ATTR_CFG)) 
	{
		((CNetSDKDemoDlg*)AfxGetMainWnd())->LastError();
		return;
	}
	CString strEth;
	for (int i = 0; i < m_sysCFG.byNetIONum; i++)
	{
		strEth.Format(ConvertString("Ethernet %d"), i+1);
		m_ethernetsel.InsertString(i, strEth);
	}

	bRet = CLIENT_GetDevConfig(m_pDev->LoginID, DH_DEV_NETCFG, 0,
								&m_netCFG, sizeof(DHDEV_NET_CFG), &retlen, CONFIG_WAITTIME*4);
	if (!bRet || retlen != sizeof(DHDEV_NET_CFG))
	{
		((CNetSDKDemoDlg*)AfxGetMainWnd())->LastError();
		return;
	}
	else
	{
		m_bInited = TRUE;
	}

	//show config information
	SetDlgItemText(IDC_EDIT_DEVNAME, m_netCFG.sDevName);
	SetDlgItemInt(IDC_EDIT_MAXTCP, m_netCFG.wTcpMaxConnectNum);
	SetDlgItemInt(IDC_EDIT_TCPPORT, m_netCFG.wTcpPort);
	SetDlgItemInt(IDC_EDIT_UDPPORT, m_netCFG.wUdpPort);
	SetDlgItemInt(IDC_EDIT_HTTPPORT, m_netCFG.wHttpPort);
	SetDlgItemInt(IDC_EDIT_HTTPSPORT, m_netCFG.wHttpsPort);
	SetDlgItemInt(IDC_EDIT_SSLPORT, m_netCFG.wSslPort);
	SetDlgItemInt(IDC_EDIT_MAXTCP, m_netCFG.wTcpMaxConnectNum);
	SetDlgItemInt(IDC_EDIT_MAXTCP, m_netCFG.wTcpMaxConnectNum);
	
	//ethernet config
	if (m_ethernetsel.GetCount() > 0)
	{
		m_ethernetsel.SetCurSel(0);
		OnSelchangeComboEthernet();
	}

	//remote config
	if (m_remotehostsel.GetCount() > 0)
	{
		m_remotehostsel.SetCurSel(0);
		OnSelchangeComboRemotehost();
	}

	//mail config
	SetDlgItemText(IDC_EDIT_MAILUSERNAME, m_netCFG.struMail.sUserName);
	SetDlgItemText(IDC_EDIT_MAILUSERPSW, m_netCFG.struMail.sUserPsw);
	SetDlgItemText(IDC_EDIT_MAILIP, m_netCFG.struMail.sMailIPAddr);
	SetDlgItemInt(IDC_EDIT_MAILPORT, m_netCFG.struMail.wMailPort);
	SetDlgItemText(IDC_EDIT_MAILDESADDR, m_netCFG.struMail.sDestAddr);
	SetDlgItemText(IDC_EDIT_MAILCCADDR, m_netCFG.struMail.sCcAddr);
	SetDlgItemText(IDC_EDIT_MAILBCCADDR, m_netCFG.struMail.sBccAddr);
	SetDlgItemText(IDC_EDIT_MAILSUBJECT, m_netCFG.struMail.sSubject);
	
	//Begin: Add by li_deming(11517) 2008-1-30
	//DDNS config
	bRet = FALSE;
	bRet = CLIENT_GetDevConfig(m_pDev->LoginID, DH_DEV_MULTI_DDNS, 0,
								&m_ddnsCFG, sizeof(DHDEV_MULTI_DDNS_CFG), &retlen, CONFIG_WAITTIME*4);
	selIndexOld=-1;	
	if(bRet == TRUE)
	{
		CString strItem="";
		m_ctlDDNSIDList.Clear();
		for(int i=0; i<m_ddnsCFG.dwDdnsServerNum;i++)
		{
			strItem="";
			strItem.Format(ConvertString("DDNS %d"),i);
			m_ctlDDNSIDList.InsertString( i,  strItem);				
		}
		UpdateData(FALSE);
		m_ctlDDNSIDList.SetCurSel(0);
		OnSelchangeComboDdnsid();
	}
	else
	{
		AfxMessageBox(ConvertString("Get Dev Multi DDNS Info Fail!"));
	}
	
	//End:li_deming(11517)
}