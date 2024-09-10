BOOL FW_HtmlCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;
	if (!wndStatic.SubclassDlgItem(nID, pParent))
		return FALSE;
	
	CRect rc;
	wndStatic.GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	wndStatic.ShowWindow(SW_HIDE);
	
	return Create(NULL,
		NULL,
		(WS_CHILD | WS_VISIBLE ),
		rc,
		pParent,
		nID,
		NULL);
}