HWND FindPeraDeskClientLonginWindow( void )
{
	CWnd * pDeskTopWnd = CWnd::GetDesktopWindow();
	CWnd *pFind = pDeskTopWnd->GetWindow(GW_CHILD);
	while (pFind && pFind->m_hWnd)
	{
		if (::GetProp(pFind->m_hWnd,"PeraDeskClient_LoginWnd"))
			return pFind->m_hWnd;

		pFind = pFind->GetWindow(GW_HWNDNEXT);
	}
	return NULL;
}