int MakeControlToolBar ( int iControlID, int iStyle, int iExtendedStyle, DWORD pFilename, int iNumberOfToolImages )
{
	// Assign the style
	DWORD dwExtendedStyle = GetExtendedStyle ( iExtendedStyle );
	DWORD dwSelectStyle = CCS_TOP;
	switch ( iStyle )
	{
		case 1 : dwSelectStyle |= 0;							break;
	}

	// Create control
	MaintainGlobalHWND();
	if ( !CreateControl ( iControlID, g_pGlob->hWnd, TOOLBARCLASSNAME, dwExtendedStyle, dwSelectStyle, "", 0, 0, 0, 0 ) )
		return 0;

	// Create image list
	g_pControls [ iControlID ].himlImageList = ImageList_Create(16, 16, ILC_COLOR24, 0, 65535); 

	// Assign the image lists to the list view control. 
	HWND hwndTB = g_pControls [ iControlID ].hWnd;

 	// Sets the size of the TBBUTTON structure.
	SendMessage(hwndTB, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);

	// Set the maximum number of text rows and bitmap size.
	SendMessage(hwndTB, TB_SETBITMAPSIZE,  0, (LPARAM)MAKELONG(16, 16));

	// Load bitmap for all buttons
	for ( int iI=0; iI<iNumberOfToolImages; iI++ )
	{
		char pFile[256];
		wsprintf ( pFile, "%s%d.bmp", pFilename, iI );
		HBITMAP hbmp = (HBITMAP)LoadImage(NULL, pFile,IMAGE_BITMAP,16,16,LR_LOADFROMFILE);
		ImageList_Add(g_pControls [ iControlID ].himlImageList,hbmp,NULL);
	}
	SendMessage(hwndTB, TB_SETIMAGELIST, 0, (LPARAM)g_pControls [ iControlID ].himlImageList);
	SendMessage(hwndTB, TB_SETHOTIMAGELIST, 0, (LPARAM)g_pControls [ iControlID ].himlImageList);

	// Subclass to get access to all control messages directly
	g_pControls [ iControlID ].lOriginalWinProc = SetWindowLong ( hwndTB, GWL_WNDPROC, (LONG)SubClassControlWinProc );

	// Update safe rects after new addition
	UpdateSafeRectsArray();

	// Success
	return 1;
}