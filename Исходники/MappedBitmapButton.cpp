void CMappedBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);
	ASSERT(m_image.GetImageCount() == 4);

	// images are:
	// 0 = up
	// 1 = down
	// 2 = focused
	// 3 = disabled
	int image = 0;
	UINT state = lpDrawItemStruct->itemState;
	if (state & ODS_SELECTED)
		image = 1;
	else if (state & ODS_FOCUS)
		image = 2;   // third image for focused
	else if (state & ODS_DISABLED)
		image = 3;   // last image for disabled

	// draw the whole button
	CRect rect;
	rect.CopyRect(&lpDrawItemStruct->rcItem);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	VERIFY( m_image.Draw( pDC, image, rect.TopLeft(), ILD_NORMAL ) );
}