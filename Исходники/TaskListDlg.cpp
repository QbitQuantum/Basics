void TaskListDlg::drawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	RECT rect = lpDrawItemStruct->rcItem;
	HDC hDC = lpDrawItemStruct->hDC;
	int nItem = lpDrawItemStruct->itemID;
	const TCHAR *label = _taskListInfo._tlfsLst[nItem]._fn.c_str();
	int iImage = _taskListInfo._tlfsLst[nItem]._status;

	COLORREF textColor = darkGrey;
	int imgStyle = ILD_SELECTED;

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		imgStyle = ILD_TRANSPARENT;
		textColor = black;
		::SelectObject(hDC, _taskList.GetFontSelected());
	}

	//
	// DRAW IMAGE
	//
	HIMAGELIST hImgLst = _taskList.getImgLst();

	IMAGEINFO info;
	ImageList_GetImageInfo(hImgLst, iImage, &info);

	RECT & imageRect = info.rcImage;
	//int yPos = (rect.top + (rect.bottom - rect.top)/2 + (isSelected?0:2)) - (imageRect.bottom - imageRect.top)/2;

	SIZE charPixel;
	::GetTextExtentPoint(hDC, TEXT(" "), 1, &charPixel);
	int spaceUnit = charPixel.cx;
	int marge = spaceUnit;

	rect.left += marge;
	ImageList_Draw(hImgLst, iImage, hDC, rect.left, rect.top, imgStyle);
	rect.left += imageRect.right - imageRect.left + spaceUnit * 2;

	//
	// DRAW TEXT
	//
	::SetTextColor(hDC, textColor);
	rect.top -= ::GetSystemMetrics(SM_CYEDGE);

	::DrawText(hDC, label, lstrlen(label), &rect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
}