bool CEtsEodManagerApp::_IsFirstInstance()
{
	CWnd* pWndPrev = CWnd::FindWindow(g_cszMainFrameClassName, NULL);

	if(pWndPrev)
	{
		CWnd* pWndChild = pWndPrev->GetLastActivePopup();

		if(pWndPrev->IsIconic())
			pWndPrev->ShowWindow(SW_RESTORE);
		else if(!pWndPrev->IsWindowVisible())
			pWndPrev->ShowWindow(SW_SHOW);

		pWndChild->SetForegroundWindow();
		return false;
	}

	return true;
}