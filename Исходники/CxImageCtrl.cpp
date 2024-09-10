void CCxImageCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nDelta;
	int nMaxPos = m_dwWidth - m_nCurWidth;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (m_nHScrollPos >= nMaxPos)
			return;
		nDelta = min(nMaxPos/20,nMaxPos-m_nHScrollPos);
		break;
		
	case SB_LINEUP:
		if (m_nHScrollPos <= 0)
			return;
		nDelta = -min(nMaxPos/20,m_nHScrollPos);
		break;
		
	case SB_PAGEDOWN:
		if (m_nHScrollPos >= nMaxPos)
			return;
		nDelta = min(nMaxPos/2,nMaxPos-m_nHScrollPos);
		break;
		
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nHScrollPos;
		break;
		
	case SB_PAGEUP:
		if (m_nHScrollPos <= 0)
			return;
		nDelta = -min(nMaxPos/20,m_nHScrollPos);
		break;
		
	default:
		return;
	}
	m_nHScrollPos += nDelta;
	SetScrollPos(SB_HORZ,m_nHScrollPos,TRUE);
	//ScrollWindow(-nDelta,0);
	
	Invalidate(FALSE);
	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}