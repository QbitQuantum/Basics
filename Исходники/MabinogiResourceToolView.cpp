void CMabinogiResourceToolView::OnInitialUpdate()
{
	int nIndex = 0;
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件名"), LVCFMT_LEFT, 120);
	GetListCtrl().InsertColumn(nIndex++, TEXT("版本"), LVCFMT_LEFT, 60);
	GetListCtrl().InsertColumn(nIndex++, TEXT("类型说明"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(nIndex++, TEXT("大小"), LVCFMT_LEFT, 80);
	GetListCtrl().InsertColumn(nIndex++, TEXT("压缩后大小"), LVCFMT_LEFT, 80);
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件时间1"), LVCFMT_LEFT, 140);
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件时间2"), LVCFMT_LEFT, 140);
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件时间3"), LVCFMT_LEFT, 140);

	HIMAGELIST hImgList;// = (HIMAGELIST)SHGetFileInfo(TEXT(""), 0, &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_LARGEICON);
	SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void**) &hImgList);
	GetListCtrl().SetImageList(CImageList::FromHandle(hImgList), TVSIL_NORMAL);

	SHGetImageList(SHIL_SMALL, IID_IImageList, (void**) &hImgList);
	GetListCtrl().SetImageList(CImageList::FromHandle(hImgList), LVSIL_SMALL);


	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP);

	LVTILEVIEWINFO lvtvi = { sizeof(LVTILEVIEWINFO), LVTVIM_COLUMNS };

	lvtvi.cLines = 2;
	lvtvi.dwFlags = LVTVIF_AUTOSIZE;
	GetListCtrl().SetTileViewInfo ( &lvtvi );

	CListView::OnInitialUpdate();


}