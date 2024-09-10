void CIPFindDlg::GetCurSelIPMask(char *ip, char *mask)
{
	USES_CONVERSION;

	CString strMsg = MSG_CUR_ADAPTER;
	strMsg += "IP:";
	strMsg += A2T(ip);
	strMsg += " Mask:";
	strMsg += A2T(mask);

	SetDlgItemText(IDC_STATIC_ADAPTER_MSG, strMsg);

	m_strFindIP = ip;
	m_strFindMask = mask;
}