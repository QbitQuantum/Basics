/***************************************************
OnPaint
	The framework calls this member function when Windows
	or an application makes a request to repaint a portion
	of an application’s window.
	The CUGHint uses this event to draw the tool tip
	window.
Params:
	<none>
Returns:
	<none>
*****************************************************/
void CUGHint::OnPaint() 
{
	if ( m_ctrl->m_GI->m_paintMode == FALSE )
		return;

	CDC* dc = GetDC();

	if(m_hFont != NULL)
		dc->SelectObject(m_hFont);
	
	CRect rect;
	GetClientRect(rect);

	dc->SetTextColor(m_textColor);
	dc->SetBkColor(m_backColor);

	dc->SetBkMode(OPAQUE);
	dc->DrawText(m_text,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	ReleaseDC(dc);
	ValidateRect(NULL);
}