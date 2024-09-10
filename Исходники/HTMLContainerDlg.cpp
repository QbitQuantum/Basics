void CHTMLContainerDlg::_OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel)
{
	CString targetURL(V_BSTR(URL));

	__time64_t now;
	_time64(&now);
	if (max(now, m_backspaceTime) - min(now, m_backspaceTime) <= 1) *Cancel = TRUE;
// 	if (m_lastURL.CompareNoCase(targetURL) == 0)
// 	{
// 		*Cancel = TRUE;
// 	}
// 	else
// 	{
// 		m_lastURL = m_curURL;
// 		m_curURL = targetURL;
// 	}
	
	OnBeforeNavigate(pDisp, targetURL);
}