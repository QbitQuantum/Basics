void CBCGPMSOffice2007DemoView::OnENRequesteResize(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	REQRESIZE *pReqResize = reinterpret_cast<REQRESIZE *>(pNMHDR);
	ASSERT (pReqResize != NULL);

	CScrollBar* pScrollBar = ((CMainFrame*) GetTopLevelFrame ())->GetScrollBar ();
	if (pScrollBar->GetSafeHwnd () == NULL)
	{
		return;
	}

	ASSERT_VALID (pScrollBar);

	CRect rectClient;
	GetClientRect (rectClient);

	const int nViewHeight = rectClient.Height ();
	const int nTotalHeight = (pReqResize->rc.bottom - pReqResize->rc.top);

	if (nTotalHeight <= nViewHeight)
	{
		pScrollBar->EnableScrollBar (ESB_DISABLE_BOTH);
	}
	else
	{
		pScrollBar->EnableScrollBar (ESB_ENABLE_BOTH);

		SCROLLINFO scrollInfo;
		memset (&scrollInfo, 0, sizeof (scrollInfo));

		scrollInfo.cbSize = sizeof (SCROLLINFO);
		scrollInfo.fMask = SIF_RANGE | SIF_PAGE;
		scrollInfo.nMin = 0;
		scrollInfo.nMax = nTotalHeight;
		scrollInfo.nPage = nViewHeight;

		if (!pScrollBar->SetScrollInfo (&scrollInfo))
		{
			pScrollBar->SetScrollRange (0, nTotalHeight, TRUE);
		}
	}
}