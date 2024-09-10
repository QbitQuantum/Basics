static VOID 
sInitKeyList (PSPLITKEYSTRUCT psks) 
{

	LV_COLUMN	lvC; 
	CHAR		sz[256];
	HBITMAP		hBmp;
	HDC			hDC;
	INT			iNumBits;

	// create image list
	hDC = GetDC (NULL);		// DC for desktop
	iNumBits = GetDeviceCaps (hDC, BITSPIXEL) * GetDeviceCaps (hDC, PLANES);
	ReleaseDC (NULL, hDC);

	if (iNumBits <= 8) {
		psks->hIml = ImageList_Create (16, 16, ILC_COLOR|ILC_MASK, 
										NUM_BITMAPS, 0); 
		hBmp = LoadBitmap (g_hInst, MAKEINTRESOURCE (IDB_IMAGES4BIT));
		ImageList_AddMasked (psks->hIml, hBmp, RGB(255, 0, 255));
		DeleteObject (hBmp);
	}
	else {
		psks->hIml = ImageList_Create (16, 16, ILC_COLOR24|ILC_MASK, 
										NUM_BITMAPS, 0); 
		hBmp = LoadBitmap (g_hInst, MAKEINTRESOURCE (IDB_IMAGES24BIT));
		ImageList_AddMasked (psks->hIml, hBmp, RGB(255, 0, 255));
		DeleteObject (hBmp);
	}

	ListView_SetImageList (psks->hwndList, psks->hIml, LVSIL_SMALL);

	lvC.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT; 
	lvC.pszText = sz;

	LoadString (g_hInst, IDS_USERID, sz, sizeof(sz));
	lvC.cx = INITIAL_SHAREKEY_COLUMNWIDTH;   
	lvC.iSubItem = 0;
	if (ListView_InsertColumn (psks->hwndList, 0, &lvC) == -1) return;

	LoadString (g_hInst, IDS_SHARES, sz, sizeof(sz));
	lvC.cx = 50;   
	lvC.iSubItem = 1;
	if (ListView_InsertColumn (psks->hwndList, 1, &lvC) == -1) return;
}