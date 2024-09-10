void CNGWizard::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (!m_bmpHeader.IsEmpty() )
	{
		CPalette* pPal = m_bmpHeader.GetPalette();
		if ( (NULL != pPal) &&
			(NULL != GetSafeHwnd()) &&
			(this != pFocusWnd) &&
			!IsChild(pFocusWnd) )
		{
			CClientDC dc(this);
			CPalette* pOldPalette = dc.SelectPalette(pPal, TRUE);
			UINT nChanged = dc.RealizePalette();
			dc.SelectPalette(pOldPalette, TRUE);

			if (0 != nChanged)
			{
				Invalidate();
			}
		}
	}
	else
	{
		CNGWizard_BASE::OnPaletteChanged(pFocusWnd);
	}
}