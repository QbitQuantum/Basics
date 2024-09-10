void CXTPSkinObjectHeader::DrawItemEntry(CDC* pDC, int nIndex, CRect rcItem, int nState)
{
	CXTPSkinManagerClass* pClass = GetSkinClass();

	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)this;
	CImageList* pImageList = CImageList::FromHandle((HIMAGELIST)
		::SendMessage(pHeaderCtrl->m_hWnd, HDM_GETIMAGELIST, 0, 0L));

	// Set up the header item order array.
	HD_ITEM hdi;
	::ZeroMemory(&hdi, sizeof(HD_ITEM));

	hdi.fmt = HDF_STRING | HDF_IMAGE;
	hdi.mask = HDI_TEXT | HDI_FORMAT | HDI_IMAGE | HDI_LPARAM;

	// Get the header item text and format
	CString strCaption;
	LPTSTR pszText = strCaption.GetBuffer(256);
	pszText[0] = 0;
	hdi.pszText = pszText;
	hdi.cchTextMax = 255;

	BOOL bResult = pHeaderCtrl->GetItem(nIndex, &hdi);

	strCaption.ReleaseBuffer();

#ifdef _UNICODE
	if (!bResult)
	{
		char tText[256];
		tText[0] = 0;

		HD_ITEMA hdia;
		::ZeroMemory(&hdia, sizeof(HD_ITEMA));

		hdia.fmt = HDF_STRING | HDF_IMAGE;
		hdia.mask = HDI_TEXT | HDI_FORMAT | HDI_IMAGE | HDI_LPARAM;

		// Get the header item text and format
		hdia.pszText = tText;
		hdia.cchTextMax = 255;

		::SendMessage(pHeaderCtrl->m_hWnd, HDM_GETITEMA, nIndex, (LPARAM)&hdia);

		strCaption = tText;
		hdi.fmt = hdia.fmt;
		hdi.iImage = hdia.iImage;
		hdi.lParam = hdia.lParam;
	}
#else
	bResult;
#endif

	if (hdi.fmt & HDF_OWNERDRAW)
	{
		DRAWITEMSTRUCT dis;

		dis.CtlType = ODT_HEADER;
		dis.CtlID = (UINT)GetDlgCtrlID();
		dis.itemID = nIndex;
		dis.itemAction = ODA_DRAWENTIRE;
		dis.itemState = (nState == HIS_PRESSED) ? ODS_SELECTED : 0;
		dis.hwndItem = m_hWnd;
		dis.hDC = pDC->GetSafeHdc();
		dis.rcItem = rcItem;
		dis.itemData = hdi.lParam;

		// Now send it off to my parent...
		if (GetParent()->SendMessage(WM_DRAWITEM, dis.CtlID,
			(LPARAM)(DRAWITEMSTRUCT*)&dis))
		{
			return;
		}
	}

	CRect rcText(rcItem);

	if (pImageList && (hdi.fmt & HDF_IMAGE) && hdi.iImage >= 0 && hdi.iImage < pImageList->GetImageCount())
	{
		int iBitmapMargin = (int)SendMessage(HDM_GETBITMAPMARGIN);
		if (iBitmapMargin == 0)
			iBitmapMargin = GetMetrics()->m_cxEdge * 3;
		int cxBitmap = 16, cyBitmap = 16;
		ImageList_GetIconSize(pImageList->GetSafeHandle(), &cxBitmap, &cyBitmap);

		CPoint pt(rcItem.left + iBitmapMargin, (rcItem.bottom + rcItem.top - cyBitmap) / 2);

		if (hdi.fmt & HDF_BITMAP_ON_RIGHT)
		{
			CSize sz = pDC->GetTextExtent(strCaption);

			pt.x += sz.cx + iBitmapMargin + 9;
			if (pt.x + cxBitmap > rcItem.right - 3)
				pt.x = max(rcItem.left + 6, rcItem.right - 3 - cxBitmap);
			if (nState == HIS_PRESSED)
				pt.x ++;

			pImageList->Draw(pDC, hdi.iImage, pt, ILD_TRANSPARENT);
			rcText.right = pt.x + 6;
		}
		else
		{
			if (nState == HIS_PRESSED)
				pt.x ++;
			pImageList->Draw(pDC, hdi.iImage, pt, ILD_TRANSPARENT);

			rcText.left += cxBitmap + iBitmapMargin;
		}
	}

	if (((hdi.fmt & HDF_IMAGE) == 0) && ((hdi.fmt & HDF_SORTUP) || (hdi.fmt & HDF_SORTDOWN)))
	{
		int iBitmapMargin = GetMetrics()->m_cxEdge * 3;
		CSize sz = pDC->GetTextExtent(strCaption);

		CPoint pt(rcItem.left + iBitmapMargin, (rcItem.bottom + rcItem.top - 2) / 2);

		pt.x += sz.cx + iBitmapMargin + 9;
		if (pt.x + 9 > rcItem.right - 3)
			pt.x = max(rcItem.left + 6, rcItem.right - 3 - 9);

		if (hdi.fmt & HDF_SORTUP)
		{
			XTPDrawHelpers()->Triangle(pDC, CPoint(pt.x - 4, pt.y + 2),
				CPoint(pt.x, pt.y - 2), CPoint(pt.x + 4, pt.y + 2), GetColor(COLOR_3DSHADOW));
		}
		else
		{
			XTPDrawHelpers()->Triangle(pDC, CPoint(pt.x - 4, pt.y - 2),
				CPoint(pt.x, pt.y + 2), CPoint(pt.x + 4, pt.y - 2), GetColor(COLOR_3DSHADOW));
		}
		rcText.right = pt.x;
	}

	UINT nFormat = DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX;

	// determine justification for text.
	switch (hdi.fmt & HDF_JUSTIFYMASK)
	{
	case HDF_LEFT:
		nFormat |= DT_LEFT;
		rcText.DeflateRect(9, 0, 6, 0);
		break;

	case HDF_CENTER:
		nFormat |= DT_CENTER;
		rcText.DeflateRect(6, 0, 6, 0);
		break;

	case HDF_RIGHT:
		nFormat |= DT_RIGHT;
		rcText.DeflateRect(6, 0, 9, 0);
		break;
	}

	if (rcText.Width() > 0)
	{
		if (nState == HIS_PRESSED)
			rcText.OffsetRect(1, 1);

		// draw text.
		pDC->SetTextColor(GetColor(COLOR_BTNTEXT));
		pClass->DrawThemeText(pDC, HP_HEADERITEM, nState, strCaption, nFormat, &rcText);
	}
}