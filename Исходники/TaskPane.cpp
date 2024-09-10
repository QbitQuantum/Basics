/*************************************************
Function:       // ShowUserInfo
Description:    //
Calls:          //
Table Accessed: //
Table Updated:  //
Input:          //
                //
Output:         //
Return:         //
Others:         //
*************************************************/
void CIBATaskPane::ShowUserInfo(CActiveMember & ActiveMember)
{
	CString strContent;
	
	CString strUseTime = ActiveMember.GetCheckInTimeAsString();
	if (!strUseTime.IsEmpty())
	{
		strUseTime.AppendFormat(_T("(%s)"), ActiveMember.GetPayTypeAsString());
	}

		/*L"姓名:%s\r\n"
		L"账号:%s\r\n"
		L"用户级别:%s\r\n"
		L"证件号码:%s\r\n"
		L"\r\n"
		L"\r\n"
		L"电脑名称:%s\r\n"
		L"机器区域:%s\r\n"

		L"使用时间:%s\r\n"
		L"使用时长:%s\r\n"
		L"\r\n"
		L"\r\n"
		L"可用金额:%s\r\n"
		L"消费金额:%s\r\n",*/

	strContent.Format(LOAD_STRING(IDS_TASK_INFO),
		ActiveMember.GetUserName(),
		ActiveMember.GetNetId(),
		ActiveMember.GetUserClassName(),
		ActiveMember.GetPersonalID(),
		ActiveMember.GetTerminalID(),
		ActiveMember.GetPCClass(),
		strUseTime,
		ActiveMember.GetUseTimeAsString(),
		ActiveMember.GetAvailavleBalanceAsString(),
		ActiveMember.GetAmountAsString());

	m_ActiveMember = ActiveMember;

	ShowUserInfo(strContent);

	// GXX 2013-5-6 15:20:36 这段代码可能有用，不要删除
	/*if (CNetBarConfig::GetInstance()->GetEnableID2Reader())
	{
		if (m_dlgUserPhoto.m_hWnd == NULL)
		{
			CString strTmp = _T("证件照");
			int nPage1Gr4 = AddGroup(1, strTmp);
			m_dlgUserPhoto.Create(IDD_DLG_USER_PHOTO, this);
			AddWindow(nPage1Gr4, m_dlgUserPhoto, 150);
		}
		CString strPath = theApp.GetWorkPath();
		CString strImgPath = strPath + _T("\\IDImages\\");
		CString strPicPath = strImgPath;
		strPicPath.Append(ActiveMember.GetPersonalID());
		strPicPath.Append(_T(".jpg"));
		if (IsWindow(m_dlgUserPhoto.m_hWnd))
		{
			m_dlgUserPhoto.m_staticPhoto.ShowPic(strPicPath);
		}
	}*/
	if (1 == CNetBarConfig::GetInstance()->GetIsShowRzxPhoto())
	{
		if (m_dlgUserPhoto.m_hWnd == NULL)
		{
			CString strTmp = _T("证件照");
			int nPage1Gr4 = AddGroup(1, strTmp);
			m_dlgUserPhoto.Create(IDD_DLG_USER_PHOTO, this);
			AddWindow(nPage1Gr4, m_dlgUserPhoto, 150);
		}
		CString strPath = theApp.GetWorkPath();
		CString strImgPath = strPath + _T("\\UserImages\\");
		CString strPicPath = strImgPath;
		CString strID = CIBAHelpper::FormatNetId(ActiveMember.GetNetId());
		strPicPath.Append(strID);
		strPicPath.Append(_T(".jpg"));
		if (IsWindow(m_dlgUserPhoto.m_hWnd))
		{
			IBA_LOG(_T("实名照片路径：%s"), strPicPath);
			m_dlgUserPhoto.m_staticPhoto.ShowPic(strPicPath);
		}
	}
}