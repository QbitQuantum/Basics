//-----------------------------------------------------------------------------
BOOL CMRCSizeToolBar::Create(CWnd * pParent, DWORD dwStyle, UINT nID, LPRECT pRect)
//-----------------------------------------------------------------------------
{
	m_ToolCtrlButtonSize.cx = 16;
	m_ToolCtrlButtonSize.cy = 15;
	
	// if no rectangle supplied, then what is hopefully as sensible default.
	// ie a single row of buttons
	CRect rect;
	if (pRect != NULL)
		rect.CopyRect(pRect);
	else
	{
		pParent->GetClientRect(&rect);
		rect.left = 0;
		rect.top = 0;
		rect.bottom = m_ToolCtrlButtonSize.cy + 18;
		rect.right -= 8;
	}
		
	BOOL status = CMRCSizeControlBar::Create(pParent, NULL, nID, dwStyle, rect); 
	if (status == TRUE)
	{
	}
	return status;
}