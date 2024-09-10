int  CSHeaderCtrl::DrawSortImage(CDC* pDC, const CRect& rect, LPHDITEM lphdi)
{
	int iWidth = 0;
	
	if (rect.Width() > 0)
	{
		UINT nSortIndex = SHC_STATE_TO_INDEX_SORT(lphdi->iImage);
		CImageList* pImageList = GetImageList();
		if(nSortIndex != SHC_NONE_SORT && pImageList != NULL)
		{
			POINT point;
			point.y = rect.CenterPoint().y - ((m_sizeImage.cy+1) >> 1);
			point.x = rect.left;
			
			SIZE size;
			size.cx = rect.Width() < m_sizeImage.cx ? rect.Width() : m_sizeImage.cx;
			size.cy = m_sizeImage.cy;
			
			// save image list background color
			COLORREF rgb = pImageList->GetBkColor();
			
			// set image list background color to same as header control
			pImageList->DrawIndirect(pDC, GetIndexOfImageList(nSortIndex), point, size, CPoint(0, 0));
			
			iWidth = size.cx;
		}