void WINCLASS::sizingMsg(WPARAM wParam, LPARAM lParam, BOOL keepRatio)
{
	RECT *rect = (RECT*)lParam;

	int _minWidth, _minHeight;

	int xborder, yborder;
	int ymenu, ymenunew;
	int ycaption;

	MENUBARINFO mbi;

	/* Get the size of the border */
	xborder = GetSystemMetrics(SM_CXSIZEFRAME);
	yborder = GetSystemMetrics(SM_CYSIZEFRAME);
	
	/* Get the size of the menu bar */
	ZeroMemory(&mbi, sizeof(mbi));
	mbi.cbSize = sizeof(mbi);
	GetMenuBarInfo(hwnd, OBJID_MENU, 0, &mbi);
	ymenu = (mbi.rcBar.bottom - mbi.rcBar.top + 1);

	/* Get the size of the caption bar */
	ycaption = GetSystemMetrics(SM_CYCAPTION);

	/* Calculate the minimum size in pixels */
	_minWidth = (xborder + minWidth + xborder);
	_minHeight = (ycaption + yborder + ymenu + minHeight + yborder);

	/* Clamp the size to the minimum size (256x384) */
	rect->right = (rect->left + std::max(_minWidth, (int)(rect->right - rect->left)));
	rect->bottom = (rect->top + std::max(_minHeight, (int)(rect->bottom - rect->top)));

	/* Apply the ratio stuff */
	if(keepRatio)
	{
		switch(wParam)
		{
		case WMSZ_LEFT:
		case WMSZ_RIGHT:
		case WMSZ_TOPLEFT:
		case WMSZ_TOPRIGHT:
		case WMSZ_BOTTOMLEFT:
		case WMSZ_BOTTOMRIGHT:
			{
				float ratio = ((rect->right - rect->left - xborder - xborder) / (float)minWidth);
				rect->bottom = (rect->top + ycaption + yborder + ymenu + (minHeight * ratio) + yborder);
			}
			break;
				
		case WMSZ_TOP:
		case WMSZ_BOTTOM:
			{
				float ratio = ((rect->bottom - rect->top - ycaption - yborder - ymenu - yborder) / (float)minHeight);
				rect->right = (rect->left + xborder + (minWidth * ratio) + xborder);
			}
			break;
		}
	}

	/* Check if the height of the menu has changed during the resize */
	ZeroMemory(&mbi, sizeof(mbi));
	mbi.cbSize = sizeof(mbi);
	GetMenuBarInfo(hwnd, OBJID_MENU, 0, &mbi);
	ymenunew = (mbi.rcBar.bottom - mbi.rcBar.top + 1);

	if(ymenunew != ymenu)
		rect->bottom += (ymenunew - ymenu);
}