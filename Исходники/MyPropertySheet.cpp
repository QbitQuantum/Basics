BOOL CMyPropertySheet::OnHelpInfo(HELPINFO* pHelpInfo)
{
	BOOL ret = FALSE;
	bool handled = false;

	if (GetStyle() & WS_CHILD)
	{
		// were an embedded property sheet, need to pass up 
		// the chain to get this message processed correctly
		CWnd * pWnd = GetParent();
		while (pWnd != NULL && pWnd->GetStyle() & WS_CHILD)
		{
			// move up the window heirarchy while 
			// finding child windows
			pWnd = pWnd->GetParent();
		}
		if (pWnd != NULL)
		{
			ret = GetParent()->GetParent()->SendMessage(WM_HELP, 
				0, (LPARAM)(pHelpInfo));
			handled = true;
		}
		// the sheet does not have a non child parent, 
		// some kind of problem!
		ASSERT(handled);    
	}
	if (!handled)
	{
		ret = CPropertySheet::OnHelpInfo(pHelpInfo);
	}
	return ret;
}