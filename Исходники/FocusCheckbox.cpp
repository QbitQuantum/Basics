HBRUSH CFocusCheckbox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	CRect r;
	GetClientRect(r);
	r.InflateRect(3, 1, 1, 1);
	FrameRect(pDC->m_hDC, r, GetSysColorBrush(COLOR_3DFACE));
	if (GetFocus() == this)
		pDC->DrawFocusRect(r);
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}