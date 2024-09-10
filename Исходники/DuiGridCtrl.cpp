void CDuiGridCtrl::SetControlRect(CRect rc)
{
	int nTotalColumnWidth = GetTotalColumnWidth();

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
				rcTemp.top += m_nHeaderHeight;
				rcTemp.left = rcTemp.right - m_nScrollWidth;
			}else
			if((SCROLL_H == uControlID) && (nTotalColumnWidth > m_rc.Width()))
			{
				rcTemp = m_rc;
				rcTemp.top = rcTemp.bottom - m_nScrollWidth;
				rcTemp.right = rcTemp.right - m_nScrollWidth;
			}else
			if(LISTBK_AREA == uControlID)
			{
				rcTemp = m_rc;
				rcTemp.top += m_nHeaderHeight;
				rcTemp.right -= m_nScrollWidth;
			}else
			{
				continue;
			}
			pControlBase->SetRect(rcTemp);			
		}
	}

	// 计算横向滚动条
	CalcColumnsPos();
	// 重新计算所有行的位置
	CalcRowsPos();
}