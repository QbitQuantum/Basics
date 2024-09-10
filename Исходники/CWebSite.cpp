HRESULT IE_IOleInSiteWindowless::InvalidateRect(LPCRECT pRect, BOOL fErase)
{
	//DEBUG("************IOleInPlaceSiteWindowless::InvalidateRect");
	// Clip the rectangle against the object's size and invalidate it
	RECT rcI = { 0, 0, 0, 0 };
	RECT posRect=m_fs->m_IEWindow->SetBounds();
	if (pRect == NULL)
	{
		rcI = posRect;
	}
	else
	{
		IntersectRect(&rcI, &posRect, pRect);
	}
	::InvalidateRect(m_fs->m_hWndParent, &rcI, fErase);
 
	return S_OK;
}