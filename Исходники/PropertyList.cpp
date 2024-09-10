void CPropertyList::DrawItem(LPDRAWITEMSTRUCT lpDIS) {
	CDC dc;
	dc.Attach(lpDIS->hDC);
	CRect rectFull = lpDIS->rcItem;
	CRect rect = rectFull;
	if (m_nDivider==0) {
		m_nDivider = rect.Width() / 2;
	}
	rect.left = m_nDivider;
	CRect rect2 = rectFull;
	rect2.right = rect.left - 1;
	UINT nIndex = lpDIS->itemID;

	if (nIndex != (UINT) -1) {
		//get the CPropertyItem for the current row
		CPropertyItem* pItem = (CPropertyItem*) GetItemDataPtr(nIndex);
		//draw two rectangles, one for each row column
		if (pItem->m_nItemType == PIT_VAR) {
			dc.FillSolidRect(rect2,RGB(220,220,220));
		} else {
			dc.FillSolidRect(rect2,RGB(192,192,192));
		}
		dc.DrawEdge(rect2,EDGE_SUNKEN,BF_BOTTOMRIGHT);
		dc.DrawEdge(rect,EDGE_SUNKEN,BF_BOTTOM);
		
		if (lpDIS->itemState == ODS_SELECTED) {
			dc.DrawFocusRect(rect2);
		}

		//write the property name in the first rectangle
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(pItem->m_propName,CRect(rect2.left+3,rect2.top+3,
											rect2.right-3,rect2.bottom+3),
					DT_LEFT | DT_SINGLELINE);

		//write the initial property value in the second rectangle
		dc.DrawText(pItem->m_curValue,CRect(rect.left+3,rect.top+3, rect.right+3,rect.bottom+3), DT_LEFT | (pItem->m_nItemType == PIT_VAR) ? DT_WORDBREAK : DT_SINGLELINE);
	}
	dc.Detach();
}