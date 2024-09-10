void CGuiBarOffice::UpdateChilds()
{
	CRect rc;
	GetClientRect(rc);
	CWnd* pWnd = GetWindow(GW_CHILD);
	while (pWnd != NULL)
    {
        if (pWnd->IsWindowVisible())
		{
			pWnd->MoveWindow(rc);
			break;
		}
            pWnd=pWnd->GetWindow(GW_HWNDNEXT);
	}
}