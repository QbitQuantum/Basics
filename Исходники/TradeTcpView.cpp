void CTcpView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	CRect rcClient;
	GetClientRect(rcClient);
	int nHeight = rcClient.Height();
	int nWidth = rcClient.Width();
	CRect rect;
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_ENTRUST);
	if (pListCtrl
		&& pListCtrl->GetSafeHwnd()
		&& pListCtrl->IsWindowEnabled())
	{
		pListCtrl->GetClientRect(rect);
		int nLeftWidth = rect.Width();
		pListCtrl->MoveWindow(rect.left, rect.top, nLeftWidth, nHeight);
		if(((GetWindowStyle(pListCtrl->m_hWnd)) & WS_VSCROLL) == WS_VSCROLL)
		{
			//MessageBox("aa");
		}
		//pListCtrl->GetScrollBarCtrl()
		/*m_stSplitter.GetClientRect(rect);
		m_stSplitter.MoveWindow(rect.left + nLeftWidth, rect.top, rect.Width(), nHeight);*/
		nLeftWidth =+ rect.Width();
		m_trData.GetClientRect(rect);
		m_trData.MoveWindow(nLeftWidth, rect.top, nWidth - nLeftWidth, nHeight);
	}	
}