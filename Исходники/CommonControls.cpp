void CToolTipCtrl::UpdateTipText(LPCWSTR lpszText,HWND hWnd,UINT nIDTool)
{
	TOOLINFOW ti;
	WCHAR szText[256];
	ti.cbSize=TTTOOLINFOW_V1_SIZE;
	ti.uFlags=TTF_SUBCLASS;
	ti.hwnd=hWnd;
	ti.uId=nIDTool;
	ti.lpszText=szText;
	StringCbCopyW(szText,256*2,lpszText);
	::SendMessage(m_hWnd,TTM_UPDATETIPTEXTW,0,(LPARAM)&ti);
}