void CNewMessageBox::setShowInfo(int nType, int nBtns, std::string strMsg)
{
	USES_CONVERSION;
	m_nShowType = nType;
	m_strMsgShow = A2T(strMsg.c_str());
	m_nBtn = nBtns;

	//++判断将显示的行数
// 	int nLines = 1;
// 	int nSingleCount = 0;
// 	LOGFONT	logfont;
//	if (m_fontStatus.GetSafeHandle())
// 	{
// 		CRect client_rect;
// 		if (GetDlgItem(IDC_STATIC_ShowMsg)->GetSafeHwnd())
// 			GetDlgItem(IDC_STATIC_ShowMsg)->GetClientRect(&client_rect);
// 		m_fontStatus.GetLogFont(&logfont);
// 		int nCharW = logfont.lfWidth;
// 		nSingleCount = client_rect.Width() / nCharW - 1;
// 		int nLen = m_strMsgShow.GetLength() * sizeof(TCHAR);
// 		nLines = nLen / nSingleCount + 1;
//	}
	//--

	InitUI();
}