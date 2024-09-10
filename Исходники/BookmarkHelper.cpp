CBookmarkTreeView::CBookmarkTreeView(HWND hTreeView,CBookmarkFolder *pAllBookmarks,
	const GUID &guidSelected,const NBookmarkHelper::setExpansion_t &setExpansion) :
	m_hTreeView(hTreeView),
	m_pAllBookmarks(pAllBookmarks),
	m_uIDCounter(0)
{
	SetWindowSubclass(hTreeView,BookmarkTreeViewProcStub,0,reinterpret_cast<DWORD_PTR>(this));

	SetWindowTheme(hTreeView,L"Explorer",NULL);

	m_himl = ImageList_Create(16,16,ILC_COLOR32|ILC_MASK,0,48);
	HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_SHELLIMAGES));
	ImageList_Add(m_himl,hBitmap,NULL);
	TreeView_SetImageList(hTreeView,m_himl,TVSIL_NORMAL);
	DeleteObject(hBitmap);

	SetupTreeView(guidSelected,setExpansion);
}