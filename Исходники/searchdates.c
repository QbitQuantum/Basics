static void PrepareResultsList(HWND hwnd){
	LVCOLUMNW	lvc;
	HBITMAP		hBmp;
	HMODULE		hIcons;

	hIcons = LoadLibraryExW(g_NotePaths.IconsPath, NULL, LOAD_LIBRARY_AS_DATAFILE);
	if(hIcons){
		//prepare and set list view image lists
		hBmp = LoadBitmapW(hIcons, MAKEINTRESOURCEW(IDB_CTRL_SMALL));
		m_hImlSearch = ImageList_Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 1);
		ImageList_AddMasked(m_hImlSearch, hBmp, CLR_MASK);
		DeleteBitmap(hBmp);
		DeleteObject((void *)CLR_MASK);
		//prepare image list for check image
		hBmp = LoadBitmapW(hIcons, MAKEINTRESOURCEW(IDB_CHECKS));
		m_hImlDefCheck = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
		ImageList_AddMasked(m_hImlDefCheck, hBmp, CLR_MASK);
		DeleteBitmap(hBmp);
		DeleteObject((void *)CLR_MASK);
		FreeLibrary(hIcons);
	}
	ListView_SetImageList(m_hListResults, m_hImlSearch, LVSIL_SMALL);
	SendMessageW(m_hListResults, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES, LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
	ZeroMemory(&lvc, sizeof(lvc));
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
	for(int i = 0; i < NELEMS(m_cols); i++){
		if(i > 0){
			lvc.cx = 240;
		}
		else{
			lvc.cx = 180;
		}
		lvc.iSubItem = i;
		lvc.pszText = m_cols[i];
		SendMessageW(m_hListResults, LVM_INSERTCOLUMNW, i, (LPARAM)&lvc);
	}

	//add checks
	CTreeView_Subclass(GetDlgItem(hwnd, IDC_TVW_SEARCH_DATES));
	TreeView_SetImageList(GetDlgItem(hwnd, IDC_TVW_SEARCH_DATES), m_hImlDefCheck, TVSIL_NORMAL);
	PrepareChecksList(GetDlgItem(hwnd, IDC_TVW_SEARCH_DATES));
}