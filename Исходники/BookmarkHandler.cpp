void CContainer::InsertBookmarkToolbarButtons(void)
{
	Bookmark_t		RootBookmark;
	HIMAGELIST		himl;
	HBITMAP			hb;

	himl = ImageList_Create(16,16,ILC_COLOR32 | ILC_MASK,0,1);
	hb = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_SHELLIMAGES));
	ImageList_Add(himl,hb,NULL);
	DeleteObject(hb);

	/* Add the custom buttons to the toolbars image list. */
	SendMessage(m_hBookmarksToolbar,TB_SETIMAGELIST,0,(LPARAM)himl);

	m_Bookmark.GetRoot(&RootBookmark);

	InsertToolbarButtonsInternal(&RootBookmark);
}