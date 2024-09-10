void CXTPPopupControl::UpdateBitmapRegion()
{
	if (!GetSafeHwnd())
		return;

	m_bLayered = FALSE;

	if (m_nBackgroundBitmap <= 0)
	{
		SetWindowRgn(NULL, FALSE);
		return;
	}

	CXTPImageManagerIcon* pImage = m_pImageManager->GetImage(m_nBackgroundBitmap, 0);
	if (!pImage)
	{
		SetWindowRgn(NULL, FALSE);
		return;
	}

	if (pImage->IsAlpha())
	{
		SetWindowRgn(NULL, FALSE);

		SetRegionAlphaLayer(pImage);
	}
	else
	{
		HRGN hRgn = BitmapToRegion(pImage);
		if (!hRgn)
			return;

		SetWindowRgn(hRgn, FALSE);
	}
}