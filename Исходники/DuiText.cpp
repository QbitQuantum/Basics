void CDuiText::SetControlRect(CRect rc)
{
	m_rc = rc;

	CRect rcTemp;
	for (size_t i = 0; i < m_vecControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecControl.at(i);
		if (pControlBase)
		{
			UINT uControlID = pControlBase->GetControlID();
			if((SCROLL_V == uControlID) && m_bScrollV)
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
}