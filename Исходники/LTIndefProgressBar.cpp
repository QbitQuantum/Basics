void LTIndefProgressBar::VerifyBuffers( CDC* pDC )
{
	CRect rClientEx;
	GetClientRect(rClientEx);
	if (!p_BarBack)
	{

		p_BarBack = LTBitmapBuffer::Create(pDC, rClientEx.Width(),rClientEx.Height());
		DrawThemeBackground(h_ThemeBar, p_BarBack->GetDC()->m_hDC, PP_BAR, 0, rClientEx, rClientEx);
	}

	if (!p_BarSlot)
	{
		CRect rSlot = rClientEx;
		rSlot.right = rSlot.left + SLOT_WIDTH;

		p_BarSlot = LTBitmapBuffer::Create(pDC, rSlot.Width(), rClientEx.Height());
		DrawThemeBackground(h_ThemeBar, p_BarSlot->GetDC()->m_hDC, PP_FILL, PBFS_PARTIAL, rSlot, rSlot);
	}
}