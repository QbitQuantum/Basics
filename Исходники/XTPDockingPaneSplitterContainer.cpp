BOOL CXTPDockingPaneSplitterWnd::GetAvailableRect(CRect& rcAvail, CRect& rcUnion)
{
	CXTPDockingPaneManager* pManager = GetDockingPaneManager();
	if (!pManager)
		return FALSE;

	int nSplitterSize = pManager->GetPaintManager()->m_nSplitterSize;

	BOOL bHoriz = m_pContainer->m_bHoriz;
	ASSERT(m_pFirst && m_pSecond);
	if (!m_pFirst || !m_pSecond)
		return FALSE;

	CRect rcFirst = m_pFirst->GetPaneWindowRect();
	CRect rcSecond = m_pSecond->GetPaneWindowRect();

	MINMAXINFO mmiFirst, mmiSecond;
	m_pFirst->GetMinMaxInfo(&mmiFirst);
	m_pSecond->GetMinMaxInfo(&mmiSecond);

	rcAvail.UnionRect(rcFirst, rcSecond);
	rcUnion = rcAvail;

	int nGap = pManager->m_nSplitterGap;
	if (bHoriz)
	{
		rcAvail.DeflateRect(max(mmiFirst.ptMinTrackSize.x, nGap), 0,
			max(mmiSecond.ptMinTrackSize.x + nSplitterSize, nGap), 0);

		if (rcUnion.Width() > mmiFirst.ptMaxTrackSize.x)
			rcAvail.right = min(rcAvail.right, rcUnion.left + mmiFirst.ptMaxTrackSize.x);

		if (rcUnion.Width() > mmiSecond.ptMaxTrackSize.x)
			rcAvail.left = max(rcAvail.left, rcUnion.right - mmiSecond.ptMaxTrackSize.x - nSplitterSize);

		if (rcAvail.left >= rcAvail.right)
			return FALSE;
	}
	else
	{
		rcAvail.DeflateRect(0, max(mmiFirst.ptMinTrackSize.y, nGap),
			0, max(mmiSecond.ptMinTrackSize.y + nSplitterSize, nGap));

		if (rcUnion.Height() > mmiFirst.ptMaxTrackSize.y)
			rcAvail.bottom = min(rcAvail.bottom, rcUnion.top + mmiFirst.ptMaxTrackSize.y);

		if (rcUnion.Height() > mmiSecond.ptMaxTrackSize.y)
			rcAvail.top = max(rcAvail.top, rcUnion.bottom - mmiSecond.ptMaxTrackSize.y - nSplitterSize);

		if (rcAvail.top >= rcAvail.bottom)
			return FALSE;
	}
	return TRUE;
}