void CGuiControlBar::OnSize(UINT nType, int cx, int cy)
{
//	CControlBar::OnSize(nType, cx, cy);
	CWnd* pWnd = GetWindow(GW_CHILD);
	if (!m_bSupportMultiView)
	{
        if (pWnd != NULL)
        {
            pWnd->MoveWindow(0, 0, cx, cy);
            ASSERT(pWnd->GetWindow(GW_HWNDNEXT) == NULL);
		}
	}
	else
	{
		while (pWnd != NULL)
        {
            if (pWnd->IsWindowVisible())
			{
				pWnd->MoveWindow(0, 0, cx, cy);
				break;
			}
            pWnd=pWnd->GetWindow(GW_HWNDNEXT);
		}
	}
	//m_pDockSite->RecalcLayout();
	// TODO: Add your message handler code here
}