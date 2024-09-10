void CDuiListCtrl::SetControlRect(CRect rc)
{
	m_rc = rc;
	CRect rcTemp;
	for (size_t i = 0; i < m_vecControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecControl.at(i);
		if (pControlBase)
		{
			UINT uControlID = pControlBase->GetControlID();
			if(SCROLL_V == uControlID)
			{
				rcTemp = m_rc;
				rcTemp.left = rcTemp.right - m_nScrollWidth;
			}else
			if(LISTBK_AREA == uControlID)
			{
				rcTemp = m_rc;
				rcTemp.right -= m_nScrollWidth;
			}else
			{
				continue;
			}
			pControlBase->SetRect(rcTemp);			
		}
	}

	// 重新计算所有行的位置
	int nXPos = 0;
	int nYPos = 0;
	for(size_t i = 0; i < m_vecRowInfo.size(); i++)
	{
		ListRowInfo &rowInfoTemp = m_vecRowInfo.at(i);
		int nItemWidth = m_rc.Width() - m_nScrollWidth;
		rowInfoTemp.rcRow.SetRect(nXPos, nYPos, nXPos + nItemWidth, nYPos + m_nRowHeight);

		nYPos += m_nRowHeight;
	}

	// 需要的总高度大于显示区高度才会显示滚动条
	m_pControScrollV->SetVisible(((int)m_vecRowInfo.size() * m_nRowHeight) > m_rc.Height());
	((CScrollV*)m_pControScrollV)->SetScrollMaxRange((int)m_vecRowInfo.size() * m_nRowHeight);
}