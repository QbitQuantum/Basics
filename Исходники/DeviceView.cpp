BOOL
CDeviceView::Initialize()
{
    BOOL bSuccess;

    /* Initialize the devices class */
    bSuccess = m_Devices->Initialize();
    if (bSuccess == FALSE) return FALSE;

    /* Create the main treeview */
    m_hTreeView = CreateWindowExW(WS_EX_CLIENTEDGE,
                                  WC_TREEVIEW,
                                  NULL,
                                  WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES |
                                   TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_LINESATROOT,
                                  0, 0, 0, 0,
                                  m_hMainWnd,
                                  (HMENU)IDC_TREEVIEW,
                                  g_hInstance,
                                  NULL);
    if (m_hTreeView)
    {
        /* Get the devices image list */
        m_ImageList = m_Devices->GetImageList();

        /* Set the image list against the treeview */
        (VOID)TreeView_SetImageList(m_hTreeView,
                                    m_ImageList,
                                    TVSIL_NORMAL);

        /* Give the treeview arrows instead of +/- boxes (on Win7) */
        SetWindowTheme(m_hTreeView, L"explorer", NULL);
    }

    return !!(m_hTreeView);
}