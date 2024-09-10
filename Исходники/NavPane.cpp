void CNavPaneWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);

	CWnd* pParent = GetParent();
	if (pParent == NULL || pParent != NULL && pParent->IsWindowVisible())
		SendMessageToVisibleDescendants(m_hWnd, WM_SHOWPARENT, bShow, nStatus);
}