void COXImageListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	if(m_imageList.GetImageCount()==0)
		return;
	
	int nImageIndex=(int)lpDrawItemStruct->itemData;
	if(nImageIndex<0 || nImageIndex>=GetCount())
		return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect(lpDrawItemStruct->rcItem);
	CRect rectIcon=rect;
	rectIcon.DeflateRect(rect.Width()/10,rect.Height()/10);

	if((lpDrawItemStruct->itemAction & (ODA_SELECT|ODA_DRAWENTIRE)))
	{
		// item has been selected - hilite frame
		CBrush brush(lpDrawItemStruct->itemState & ODS_SELECTED ?
			m_clrHighlight : m_clrBackground);
		pDC->FillRect(&rect,&brush);
	}
	else if((lpDrawItemStruct->itemAction & (ODA_FOCUS|ODA_DRAWENTIRE)) &&
		!(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		CBrush brush((lpDrawItemStruct->itemState & ODS_SELECTED) ?
			m_clrHighlight : m_clrBackground);
		pDC->FrameRect(rect,&brush);
	}

	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		// Item has been unselected - remove frame
		pDC->IntersectClipRect(rect);
		SendMessage(WM_ERASEBKGND,(WPARAM)lpDrawItemStruct->hDC);
	}

	if(lpDrawItemStruct->itemAction&(ODA_SELECT|ODA_DRAWENTIRE))
	{
		UINT nStyle=ILD_TRANSPARENT;
		m_imageList.Draw(pDC,nImageIndex,rectIcon.TopLeft(),nStyle);
	}

}