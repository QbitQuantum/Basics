void CPushCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pdc;
	int bmpId;
	CBitmap bitmap;
	BITMAP  bmp;
	CPictureHolder picHolder;
	CRect rcSrcBounds;

	CPen* pOldPen;
	RECT    rect;
	SHORT   inflate;

	pdc = CDC::FromHandle(lpDrawItemStruct->hDC);

	switch (lpDrawItemStruct->itemAction)
	{
		case ODA_DRAWENTIRE:
		case ODA_SELECT:
			// Load "up" or "down" bitmap depending on selection state
			bmpId = (lpDrawItemStruct->itemState & ODS_SELECTED) ? IDB_DOWNBITMAP
				: IDB_UPBITMAP;
			bitmap.LoadBitmap(bmpId);
			bitmap.GetObject(sizeof(BITMAP), &bmp);
			rcSrcBounds.right = bmp.bmWidth;
			rcSrcBounds.bottom = bmp.bmHeight;

			// Create picture and render
			picHolder.CreateFromBitmap((HBITMAP)bitmap.m_hObject, NULL, FALSE);
			picHolder.Render(pdc, lpDrawItemStruct->rcItem, rcSrcBounds);

			break;

		case ODA_FOCUS:
			// Just draw focus rect
			pOldPen = (CPen*)pdc->SelectStockObject(BLACK_PEN);
			if (lpDrawItemStruct->itemState & ODS_FOCUS)
			{
				CopyRect((LPRECT)&rect, (LPRECT)&lpDrawItemStruct->rcItem);
				inflate = (SHORT)min(3,min(rect.right  - rect.left + 1,
					rect.bottom - rect.top  + 1) / 5);
				InflateRect(&rect, -inflate, -inflate);
				pdc->DrawFocusRect(&rect);
			}
			pdc->SelectObject(pOldPen);
			break;
	}
}