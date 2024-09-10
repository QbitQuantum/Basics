void CHexEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	if(!m_pData)
		return;

	if(nFlags & MK_SHIFT)
	{
		m_selStart = m_currentAddress;
	}
	CPoint pt = CalcPos(point.x, point.y);
	if(pt.x > -1)
	{
		m_editPos = pt;
		pt.x *= m_nullWidth;
		pt.y *= m_lineHeight;
		
		if(pt.x == 0 && m_bShowAddress)
			CreateAddressCaret();
		else
			CreateEditCaret();

		SetCaretPos(pt);
		if(nFlags & MK_SHIFT)
		{
			m_selEnd = m_currentAddress;
			if(m_currentMode == EDIT_HIGH || m_currentMode == EDIT_LOW)
				m_selEnd++;
			RedrawWindow();
		}
	}
	if(!(nFlags & MK_SHIFT))
	{
#ifdef _VS6_USED
		if(DragDetect(this->m_hWnd, point))
#else
		if(DragDetect(point))
#endif
		{
			m_selStart = m_currentAddress;
			m_selEnd   = m_selStart;
			SetCapture();
		}
		else
		{
			BOOL bsel = m_selStart != 0xffffffff;

			m_selStart = 0xffffffff;
			m_selEnd   = 0xffffffff;
			if(bsel)
				RedrawWindow();
		}
	}
	if(!IsSelected())
	{
		ShowCaret();
	}
}