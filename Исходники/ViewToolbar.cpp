HWND CViewToolbar::Create()
{
    if ((m_hWnd = CreateWindow(TOOLBARCLASSNAME, NULL, WS_CHILD | WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NOPARENTALIGN | TBSTYLE_FLAT | TBSTYLE_LIST, 0, 0, 0, 0, m_hWndParent, NULL, g_hInstance, NULL)) == NULL)
        return NULL;

    HBITMAP hBitmap;
    if ((hBitmap = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_VIEW_TOOLBAR))) == NULL)
        return NULL;
    if ((m_hImageList = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, MAX_VIEW_TOOLBAR_ICONS, 0)) == NULL)
    {
        DeleteObject(hBitmap);
        return NULL;
    }
    if (ImageList_AddMasked(m_hImageList, hBitmap, RGB(0, 0, 0)) == -1)
    {
        DeleteObject(hBitmap);
        return NULL;
    }
    DeleteObject(hBitmap);
    SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)m_hImageList);

    TBBUTTON tbb[MAX_CATEGORIES];
    for (int i = 0; i < MAX_CATEGORIES; i++)
    {
        tbb[i].iBitmap = iIcons[i];
        tbb[i].idCommand = uCommands[i];
        tbb[i].fsState = TBSTATE_ENABLED;
        tbb[i].fsStyle = TBSTYLE_AUTOSIZE | TBSTYLE_CHECKGROUP;
        tbb[i].dwData = 0;
        tbb[i].iString = -1;
    }
    tbb[0].fsState |= TBSTATE_CHECKED;
    if (!SendMessage(m_hWnd, TB_ADDBUTTONS, MAX_CATEGORIES, (LPARAM)tbb))
        return NULL;

    for (int i = 0; i < MAX_CATEGORIES; i++)
    {
        m_nCounts[i] = -1;
        LoadString(g_hInstance, ID_VIEW_ALL + i, m_szFormats[i], MAX_CAPTION);
    }

    UpdateTexts();

    return m_hWnd;
}