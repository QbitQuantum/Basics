void KSceneCustomScrollBar::ReCalculateScrollScales()
{
	size_t uVecSize = m_vecWnd.size();
	if (uVecSize <= 0)
		return;
	DWORD dwStype = this->GetStyle();
	if (dwStype & SB_VERT/*WS_VSCROLL*/)
	{
		m_nBarType = SB_VERT;
	}
	else
	{
		m_nBarType = SB_HORZ;
	}
	_ASSERTE(uVecSize == m_vecScrollScale.size());
	SCROLLINFO SI;
	SI.cbSize = sizeof(SCROLLINFO);
	SI.fMask = SIF_ALL;
	this->GetScrollInfo(&SI,SIF_ALL);
	INT nThisRange = SI.nMax - SI.nMin - SI.nPage + 1;
	enum
	{
		MAX_SCROLL_UNIT = 10000,
	};	
	if (abs(SI.nMax) > MAX_SCROLL_UNIT || abs(SI.nMin) > MAX_SCROLL_UNIT || nThisRange < 0)
	{
		for (size_t i = 0; i < uVecSize; i++)
		{
			m_vecScrollScale[i] = 1;
		}
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	
	_ASSERTE(nThisRange >= 0);
	for (size_t i = 0; i < uVecSize; i++)
	{
		float fScale = 0;
		CWnd* pTargetWnd = m_vecWnd[i];
		if (pTargetWnd)
		{
			pTargetWnd->GetScrollInfo(m_nBarType, &SI);
			INT nThatRange = (SI.nMax - SI.nMin - SI.nPage + 1);
			_ASSERTE(nThatRange >= 0);
			if (nThisRange == nThatRange)
			{
				fScale = 1;
			}
			else
			{
				fScale = nThisRange != 0 ? ((float)nThatRange/(float)nThisRange) : (float)nThatRange;
			}				
		}
		m_vecScrollScale[i] = fScale;			
	}
	
}