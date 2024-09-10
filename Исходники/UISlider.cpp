void CUISlider::OnLButtonDown(POINT point)
{
	screenToClient(point);
	if(PtInRect(&m_rcButton, point))
	{
		// Pressed while inside the control
		SetPressed(true);

		//m_nDragX = pt.x;
		m_ptDragOffset.x = m_rcButton.right - point.x;
		m_ptDragOffset.y = m_rcButton.bottom - point.y;
		SetFocus();
		return;
	}
	if(m_rcRelativeBox.ptInRect(point))
	{
		m_ptDragOffset.x=0;
		m_ptDragOffset.y=0;
		//SetPressed(true);
		SetFocus();
		if(m_bH)
		{
			if(point.x > m_rcButton.left)
			{
				SetValueInternal(m_nValue + __max(m_nPageSize-1,1));
				return;
			}
			if(point.x < m_rcButton.right)
			{
				SetValueInternal(m_nValue - __max(m_nPageSize-1,1));
				return;
			}
		}
		else
		{
			if(point.y > m_rcButton.top)
			{
				SetValueInternal(m_nValue + m_nPageSize - 1);
				return;
			}
			if(point.y < m_rcButton.bottom)
			{
				SetValueInternal(m_nValue - m_nPageSize + 1);
				return;
			}
		}
	}
}