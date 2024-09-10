HWND CreateEmptyToolbar(HWND hwndParent, int nBitmapIdx, int nBitmapWidth, int nCtrlId, DWORD dwExtraStyle)
{
	HWND	   hwndTB;
	HIMAGELIST hImgList;
	
	hwndTB = CreateToolbarEx (hwndParent,
			TOOLBAR_STYLE|dwExtraStyle,
			nCtrlId, 0,
			0,
			0,
			NULL,
			0,
			0, 0, 0, 0,
			sizeof(TBBUTTON) );

	//hImgList = ImageList_LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(nBitmapIdx), 
	//								nBitmapWidth, 16, RGB(255,0,255));
	hImgList = ImageList_LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(nBitmapIdx), 
									nBitmapWidth, 16, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);

	SendMessage(hwndTB, TB_SETIMAGELIST, 0, (LPARAM)hImgList);

	return hwndTB;

	return CreateWindowEx(0, TOOLBARCLASSNAME,0,WS_VISIBLE|WS_CHILD|TBSTYLE_FLAT|
		TBSTYLE_TRANSPARENT |CCS_NORESIZE|CCS_NODIVIDER,
		0,0,0,0,hwndParent,0,0,0);

  //SendMessage(hToolBar, TB_SETSTYLE, 0, SendMessage(hToolBar, TB_GETSTYLE, 0,0 )
//& ~ TBSTYLE_TRANSPARENT);
}