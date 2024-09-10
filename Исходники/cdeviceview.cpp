void CDeviceView::CalcDimensions()
{
	// go through all texts and controls to find the max y coord
	int max = g_sizeImage.cy - g_iListHeaderHeight;
	int i = 0;
	for (; i < GetNumTexts(); i++)
	{
		CDeviceViewText *pText = GetText(i);
		if (!pText)
			continue;
		int ty = pText->GetMaxY();
		if (ty > max)
			max = ty;
	}
	for (i = 0; i < GetNumControls(); i++)
	{
		CDeviceControl *pControl = GetControl(i);
		if (!pControl)
			continue;
		int cy = pControl->GetMaxY();
		if (cy > max)
			max = cy;
	}

	// set
	m_nViewHeight = max;
	m_nScrollOffset = 0;

	// enable scrollbar if view height more than window size
	if (m_nViewHeight > g_sizeImage.cy - g_iListHeaderHeight)
		EnableScrollBar();
}