void CNumberLimitEdit::ReportErrorMsg()
{
	CString strMsg, strTitle;
	strMsg.Format(m_nErrMsgID, m_nMin, m_nMax);	

	UINT nType = MB_OK;

	DWORD dwLayout = 0;
	GetProcessDefaultLayout(&dwLayout);
	if (dwLayout == LAYOUT_RTL) {
		nType |= MB_RTLREADING | MB_RIGHT;
	}
	
	MessageBox(strMsg, m_strTitle, nType);
}