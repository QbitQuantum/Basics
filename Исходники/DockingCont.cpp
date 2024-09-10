void DockingCont::drawTabItem(DRAWITEMSTRUCT *pDrawItemStruct)
{
	TCITEM	tcItem		= {0};
	RECT	rc			= pDrawItemStruct->rcItem;
	
	int		nTab		= pDrawItemStruct->itemID;
	bool	isSelected	= (nTab == getActiveTb());

	// get current selected item
	tcItem.mask = TCIF_PARAM;
	::SendMessage(_hContTab, TCM_GETITEM, nTab, (LPARAM)&tcItem);
	if (!tcItem.lParam)
		return;

	TCHAR*	text	= ((tTbData*)tcItem.lParam)->pszName;
	int		length	= lstrlen(((tTbData*)tcItem.lParam)->pszName);


	// get drawing context
	HDC hDc = pDrawItemStruct->hDC;

	int nSavedDC = ::SaveDC(hDc);

	// For some bizarre reason the rcItem you get extends above the actual
	// drawing area. We have to workaround this "feature".
	rc.top += ::GetSystemMetrics(SM_CYEDGE);

	::SetBkMode(hDc, TRANSPARENT);
	HBRUSH hBrush = ::CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	::FillRect(hDc, &rc, hBrush);
	::DeleteObject((HGDIOBJ)hBrush);

	// draw orange bar
	if ((_bDrawOgLine == TRUE) && (isSelected))
	{
		RECT barRect  = rc;
		barRect.top  += rc.bottom - 4;

		hBrush = ::CreateSolidBrush(RGB(250, 170, 60));
		::FillRect(hDc, &barRect, hBrush);
		::DeleteObject((HGDIOBJ)hBrush);

	}

	// draw icon if enabled
	if (((tTbData*)tcItem.lParam)->uMask & DWS_ICONTAB)
	{
		HIMAGELIST	hImageList	= (HIMAGELIST)::SendMessage(_hParent, DMM_GETIMAGELIST, 0, 0);
		int			iPosImage	= ::SendMessage(_hParent, DMM_GETICONPOS, 0, (LPARAM)((tTbData*)tcItem.lParam)->hClient);

		if ((hImageList != NULL) && (iPosImage >= 0))
		{
			// Get height of image so we
			IMAGEINFO	info		= {0};
			RECT &		imageRect	= info.rcImage;
			
			ImageList_GetImageInfo(hImageList, iPosImage, &info);
			ImageList_Draw(hImageList, iPosImage, hDc, rc.left + 3, 2, ILD_NORMAL);

			if (isSelected == true)
			{
				rc.left += imageRect.right - imageRect.left + 5;
			}
		}
	}

	if (isSelected == true)
	{
		COLORREF _unselectedColor = RGB(0, 0, 0);
		::SetTextColor(hDc, _unselectedColor);

		// draw text
		rc.top -= ::GetSystemMetrics(SM_CYEDGE);
		::SelectObject(hDc, _hFont);
		::DrawText(hDc, text, length, &rc, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
	}

	::RestoreDC(hDc, nSavedDC);
}