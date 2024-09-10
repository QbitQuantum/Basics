BOOL CNdbTreeView::CreateTreeView(HINSTANCE hInst, HWND hParent, DWORD dwId) {


    m_hInstance		= hInst ;
    m_hParent			= hParent ;
    m_dwId				= dwId ;
    HIMAGELIST		himl ;
    HBITMAP				hbmp ;
    DWORD dwCount	= 0 ;

    m_hControl = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, WC_TREEVIEW, "Tree View",
                                WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES |
                                TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SINGLEEXPAND,
                                0, 0, 0, 0, m_hParent, (HMENU)m_dwId, m_hInstance, NULL) ;

    if(!m_hControl)
        return FALSE ;

    if((himl = ImageList_Create(nX, nY, ILC_MASK | ILC_COLOR8, 4, 0)) == NULL)
        return FALSE ;

    hbmp = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDI_OPEN));
    hbmp = (HBITMAP)LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_OPEN), IMAGE_BITMAP, nX, 0, LR_DEFAULTSIZE);
    m_nOpen = ImageList_AddMasked(himl, hbmp, clr);
    DeleteObject(hbmp);
    hbmp = (HBITMAP)LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_CLOSED), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    m_nClosed = ImageList_AddMasked(himl, hbmp, clr);
    DeleteObject(hbmp);
    hbmp = (HBITMAP)LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_COMPUTER),IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    m_nComputer = ImageList_AddMasked(himl, hbmp, clr);
    DeleteObject(hbmp);
    hbmp = (HBITMAP)LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_DATABASE), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
    m_nDatabase = ImageList_AddMasked(himl, hbmp, clr);
    DeleteObject(hbmp);

    if(ImageList_GetImageCount(himl) < 4)
        return FALSE ;

    TreeView_SetImageList(m_hControl, himl, TVSIL_NORMAL);

    ShowWindow(m_hControl, SW_SHOW) ;

    return TRUE ;

}