void CModbusPollView::OnSetupUseasdefault()
{

	CString StrTemp;
	StrTemp.Format(_T("%d"),m_Slave_ID);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("SLAVE_ID"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_Function);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("FUNCTION"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_address);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("ADDRESS"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_Quantity);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("QUANTITY"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_Scan_Rate);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("SCANRATE"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_Rows);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("ROWS"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_Display);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("DATA_TYPE"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_Hide_Alias_Columns);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("HIDEALIAS"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_Address_Cell);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("ADDRESSINCELL"),StrTemp,g_configfile_path);
	StrTemp.Format(_T("%d"),m_PLC_Addresses);
	WritePrivateProfileStringW(_T("MBPOLL_VIEW_SETTING"),_T("PLCBASE1"),StrTemp,g_configfile_path);
}