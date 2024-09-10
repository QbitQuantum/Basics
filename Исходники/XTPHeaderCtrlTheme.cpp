void CXTPHeaderCtrlTheme::OnDrawItemBitmap(LPDRAWITEMSTRUCT lpDIS, CRect& rcText, CXTPHeaderCtrl* pHeaderCtrl)
{
	ASSERT_VALID(pHeaderCtrl);

	HDITEM hdi;
	hdi.mask = HDI_BITMAP | HDI_FORMAT | HDI_IMAGE;
	pHeaderCtrl->GetItem(lpDIS->itemID, &hdi);

	HIMAGELIST hImageList = 0;
	int nIndex = -1;

	if (hdi.fmt & HDF_BITMAP && hdi.hbm != NULL)
	{
		hImageList = (HIMAGELIST)hdi.hbm;
		nIndex = 0;
	}
	else if (hdi.fmt & HDF_IMAGE)
	{
		hImageList = (HIMAGELIST)pHeaderCtrl->SendMessage(HDM_GETIMAGELIST);
		nIndex = hdi.iImage;
	}

	if (nIndex != -1 && (hdi.fmt & HDF_IMAGE) && pHeaderCtrl->GetImageManager())
	{
		CXTPImageManagerIcon* pIcon = pHeaderCtrl->GetImageManager()->GetImage(nIndex, 0);

		if (pIcon)
		{
			CRect rcItem(lpDIS->rcItem);
			CPoint point(rcText.left,  (rcItem.Height() - pIcon->GetHeight()) / 2);

			rcText.left += pIcon->GetWidth() + m_sizePadding.cx;

			XTPImageState imageState = (lpDIS->itemState & ODS_SELECTED) ? xtpImageChecked :
				(lpDIS->itemState & ODS_HOTLIGHT) ? xtpImageHot : xtpImageNormal;

			if (lpDIS->itemState == ODS_SELECTED)
				point.Offset(1, 1);

			if (point.x + pIcon->GetWidth() > lpDIS->rcItem.right)
				return;

			// draw image transparently.
			pIcon->Draw(CDC::FromHandle(lpDIS->hDC), point, pIcon->GetIcon(imageState));

			return;
		}
	}

	if (hImageList)
	{
		int cx, cy;
		if (::ImageList_GetIconSize(hImageList, &cx, &cy) && (nIndex < ImageList_GetImageCount(hImageList)))
		{
			CRect rcItem(lpDIS->rcItem);
			CPoint point(rcText.left,  (rcItem.Height() - cy) / 2);

			rcText.left += cx + m_sizePadding.cx;

			if (lpDIS->itemState == ODS_SELECTED)
				point.Offset(1, 1);

			if (point.x + cx > lpDIS->rcItem.right)
				return;

			// draw image transparently.
			::ImageList_Draw(hImageList, nIndex, lpDIS->hDC, point.x, point.y, ILD_TRANSPARENT);
		}
	}
}