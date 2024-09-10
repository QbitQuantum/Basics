static HWND CreateToolbar(HWND hwndParent, int nButtons, int nBtnWidth, int nBtnHeight, HBITMAP hbm)
{
	HWND hTBWnd;			// Handle of toolbar window
	HIMAGELIST imageList;

	// Cria a toolbar

	hTBWnd = CreateWindowEx(0,
      TOOLBARCLASSNAME, "",
	  WS_CHILD | WS_VISIBLE | CCS_TOP | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT,
	  0, 0, 0, 0,
      hwndParent, NULL, hAppInstance, NULL
    );

	if(!hTBWnd)
		return NULL;

	SetToolBarHandle(hTBWnd);

	// Create an ImageList with transparent bitmaps

	if(hbm && IsBitmap(hbm)) {

		nButtons = MAX(1, MIN(nButtons, MIN(nBtnWidth, MAX_IMAGELIST_IMAGES)));

		imageList = ImageList_Create(nBtnWidth, nBtnHeight, ILC_COLORDDB | ILC_MASK, nButtons, 0);
		ImageList_AddMasked(imageList, hbm, RGB(0, 255, 0));
		DeleteObject(hbm);
		SendMessage(hTBWnd, TB_SETIMAGELIST, 0, (LPARAM)imageList);
	}

	return hTBWnd;
}