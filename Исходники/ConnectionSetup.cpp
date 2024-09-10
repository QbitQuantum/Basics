void CConnectionSetup::Write_Config()
{

    CString Connect_Type;
    Connect_Type.Format(_T("%d"),m_combox_connection_type.GetCurSel());
    CString COM_Port;
    m_combox_comport.GetWindowText(COM_Port);
    CString Num_com_port=COM_Port.Mid(3);

    CString bradrate;
    m_combox_bradrate.GetWindowText(bradrate);

    CString ipaddress;
    m_combox_ipaddress.GetWindowText(ipaddress);

    CString ipport;
    m_edit_port.GetWindowText(ipport);

    CString BT;
    m_edit_between_time.GetWindowText(BT);

    CString RT;
    m_edit_response_timeout.GetWindowText(RT);

    CString CT;
    m_edit_connect_timeout.GetWindowText(CT);

    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),Connect_Type,g_configfile_path);

    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM Port"),COM_Port,g_configfile_path);

    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM_Port"),Num_com_port,g_configfile_path);

    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Baudrate"),bradrate,g_configfile_path);


    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),ipaddress,g_configfile_path);
    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),ipport,g_configfile_path);

    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),BT,g_configfile_path);
    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),RT,g_configfile_path);
    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T(" Connect Timeout"),CT,g_configfile_path);


    m_bradrate=_wtoi(bradrate);
    m_Commication_Type=_wtoi(Connect_Type);
    m_comport=COM_Port;
    m_ipaddress=ipaddress;
    m_ipport=_wtoi(ipport);
    m_connect_timeout=_wtoi(CT);
    m_response_timeout = _wtoi (RT);
    m_between_time = _wtoi (BT);




}