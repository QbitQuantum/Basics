int CTaskbarNotifier::Create(CWnd *pWndParent)
{
	m_pWndParent=pWndParent;
	CString strWndClass=AfxRegisterWndClass(0,AfxGetApp()->LoadStandardCursor(IDC_ARROW),GetSysColorBrush(COLOR_WINDOW),NULL);
	return CreateEx(0,strWndClass,NULL,WS_POPUP,0,0,0,0,pWndParent->m_hWnd,NULL);
}