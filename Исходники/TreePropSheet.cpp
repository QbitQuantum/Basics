BOOL CTreePropSheet::OnInitDialog()
{
    if (m_bTreeViewMode)
    {
        // be sure, there are no stacked tabs, because otherwise the
        // page caption will be to large in tree view mode
        EnableStackedTabs(FALSE);

        // Initialize image list.
        if (m_DefaultImages.GetSafeHandle())
        {
            IMAGEINFO   ii;
            m_DefaultImages.GetImageInfo(0, &ii);
            if (ii.hbmImage) DeleteObject(ii.hbmImage);
            if (ii.hbmMask) DeleteObject(ii.hbmMask);
            m_Images.Create(ii.rcImage.right-ii.rcImage.left, ii.rcImage.bottom-ii.rcImage.top, ILC_COLOR32|ILC_MASK, 0, 1);
        }
        else
            m_Images.Create(16, 16, ILC_COLOR32|ILC_MASK, 0, 1);
    }

    // perform default implementation
    BOOL bResult = CPropertySheet::OnInitDialog();

    if (!m_bTreeViewMode)
        // stop here, if we would like to use tabs
        return bResult;

    // Get tab control...
    CTabCtrl    *pTab = GetTabControl();
    if (!IsWindow(pTab->GetSafeHwnd()))
    {
        ASSERT(FALSE);
        return bResult;
    }

    // ... and hide it
    pTab->ShowWindow(SW_HIDE);
    pTab->EnableWindow(FALSE);

    // Place another (empty) tab ctrl, to get a frame instead
    CRect   rectFrame;
    pTab->GetWindowRect(rectFrame);
    ScreenToClient(rectFrame);

    m_pFrame = CreatePageFrame();
    if (!m_pFrame)
    {
        ASSERT(FALSE);
        AfxThrowMemoryException();
    }
    m_pFrame->Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, rectFrame, this, 0xFFFF);
    m_pFrame->ShowCaption(m_bPageCaption);

    // Lets make place for the tree ctrl
    const int   nTreeWidth = m_nPageTreeWidth;
    const int   nTreeSpace = 5;

    CRect   rectSheet;
    GetWindowRect(rectSheet);
    rectSheet.right+= nTreeWidth;
    SetWindowPos(NULL, -1, -1, rectSheet.Width(), rectSheet.Height(), SWP_NOZORDER|SWP_NOMOVE);
    CenterWindow();

    MoveChildWindows(nTreeWidth, 0);

    // Lets calculate the rectangle for the tree ctrl
    CRect   rectTree(rectFrame);
    rectTree.right = rectTree.left + nTreeWidth - nTreeSpace;

    // calculate caption height
    CTabCtrl    wndTabCtrl;
    wndTabCtrl.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, rectFrame, this, 0x1234);
    wndTabCtrl.InsertItem(0, _T(""));
    CRect   rectFrameCaption;
    wndTabCtrl.GetItemRect(0, rectFrameCaption);
    wndTabCtrl.DestroyWindow();
    m_pFrame->SetCaptionHeight(rectFrameCaption.Height());

    // if no caption should be displayed, make the window smaller in
    // height
    if (!m_bPageCaption)
    {
        // make frame smaller
        m_pFrame->GetWnd()->GetWindowRect(rectFrame);
        ScreenToClient(rectFrame);
        rectFrame.top+= rectFrameCaption.Height();
        m_pFrame->GetWnd()->MoveWindow(rectFrame);

        // move all child windows up
        MoveChildWindows(0, -rectFrameCaption.Height());

        // modify rectangle for the tree ctrl
        rectTree.bottom-= rectFrameCaption.Height();

        // make us smaller
        CRect   rect;
        GetWindowRect(rect);
        rect.top+= rectFrameCaption.Height()/2;
        rect.bottom-= rectFrameCaption.Height()-rectFrameCaption.Height()/2;
        if (GetParent())
            GetParent()->ScreenToClient(rect);
        MoveWindow(rect);
    }

    // finally create the tree control
    const DWORD dwTreeStyle = TVS_SHOWSELALWAYS|TVS_TRACKSELECT|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS;
    m_pwndPageTree = CreatePageTreeObject();
    if (!m_pwndPageTree)
    {
        ASSERT(FALSE);
        AfxThrowMemoryException();
    }

    // MFC7-support here (Thanks to Rainer Wollgarten)
    // YT: Cast tree control to CWnd and calls CWnd::CreateEx in all cases (VC 6 and7).
    ((CWnd*)m_pwndPageTree)->CreateEx(
        WS_EX_CLIENTEDGE|WS_EX_NOPARENTNOTIFY|TVS_EX_DOUBLEBUFFER,
        _T("SysTreeView32"), _T("PageTree"),
        WS_TABSTOP|WS_CHILD|WS_VISIBLE|dwTreeStyle,
        rectTree, this, s_unPageTreeId);

    if (m_bTreeImages)
    {
        m_pwndPageTree->SetImageList(&m_Images, TVSIL_NORMAL);
        m_pwndPageTree->SetImageList(&m_Images, TVSIL_STATE);
    }

    SetWindowTheme(m_pwndPageTree->GetSafeHwnd(), L"Explorer", NULL);

    // Fill the tree ctrl
    RefillPageTree();

    // Select item for the current page
    if (pTab->GetCurSel() > -1)
        SelectPageTreeItem(pTab->GetCurSel());

    return bResult;
}