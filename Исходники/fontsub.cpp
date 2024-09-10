BOOL LV_Init(HWND hwnd)
{
    ListView_SetExtendedListViewStyle(hwnd,
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    HIMAGELIST hImageList;
    hImageList = ImageList_Create(12, 12, ILC_COLOR8 | ILC_MASK, 2, 2);

    HBITMAP hbm;
    hbm = (HBITMAP)LoadImage(g_hInstance, MAKEINTRESOURCE(2), IMAGE_BITMAP,
                             12, 12, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
    assert(hbm);
    ImageList_AddMasked(hImageList, hbm, RGB(192, 192, 192));
    DeleteObject(hbm);

    hbm = (HBITMAP)LoadImage(g_hInstance, MAKEINTRESOURCE(3), IMAGE_BITMAP,
                             12, 12, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
    assert(hbm);
    ImageList_AddMasked(hImageList, hbm, RGB(192, 192, 192));
    DeleteObject(hbm);

    hbm = (HBITMAP)LoadImage(g_hInstance, MAKEINTRESOURCE(4), IMAGE_BITMAP,
                             12, 12, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
    assert(hbm);
    ImageList_AddMasked(hImageList, hbm, RGB(192, 192, 192));
    DeleteObject(hbm);

    ListView_SetImageList(hwnd, hImageList, LVSIL_SMALL);

    LV_COLUMNW Column;
    ZeroMemory(&Column, sizeof(Column));
    Column.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_IMAGE;
    Column.fmt = LVCFMT_LEFT;

    Column.cx = NAME_COLUMN_WIDTH;
    Column.pszText = g_szNameHead;
    Column.iSubItem = 0;
    Column.iImage = 0;
    ListView_InsertColumn(hwnd, 0, &Column);

    Column.cx = SUB_COLUMN_WIDTH;
    Column.pszText = g_szSubstituteHead;
    Column.iSubItem = 1;
    Column.iImage = 2;
    ListView_InsertColumn(hwnd, 1, &Column);

    UINT State = LVIS_SELECTED | LVIS_FOCUSED;
    ListView_SetItemState(hwnd, 0, State, State);

    return TRUE;
}