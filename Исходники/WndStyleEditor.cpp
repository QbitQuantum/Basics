void CWndStyleEditor::OnEnChangeEditBottom()
{
	CString Str;
	m_rectBottom.GetWindowText(Str);
	m_Rect.bottom = (float)_wtof( Str.GetBuffer() );
	m_StyleRender.SetDrawRect(m_Rect);
	if(m_pBlock)
		((*m_pBlock)[m_BlockIndex]) = m_Rect;
}