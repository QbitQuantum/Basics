/*!
 @brief ユーザ情報の表示
*/
void CUserInfoDlg::ExecUserInfo()
{
	TCHAR szUserName[UNLEN + 1];
	DWORD nUserNameSize = sizeof(szUserName) / sizeof(TCHAR);
	GetUserName(szUserName, &nUserNameSize);
	m_strUserName = szUserName;

	TCHAR szDomainName[DNLEN + 1];
	DWORD nDomainNameSize = sizeof(szDomainName) / sizeof(TCHAR);
	GetComputerNameEx(ComputerNameDnsDomain, szDomainName, & nDomainNameSize);
	m_strDomainName = szDomainName;

	TCHAR szFullUserName[UNLEN + 1];
	ZeroMemory(szFullUserName, sizeof(szFullUserName));
	GetFullName(szUserName, szDomainName, szFullUserName);
	m_strFullUserName = szFullUserName;

	m_bAdminUser = IsUserAnAdmin();

	TCHAR szGroupName[(GNLEN + 1) * 5];
	ZeroMemory(szGroupName, sizeof(szGroupName));
	GetGroupName(szUserName, szGroupName);
	m_strGroupName = szGroupName;	
	m_strGroupName.TrimLeft(_T(','));

	UpdateData(FALSE);
}