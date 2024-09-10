BOOL CTraceTabBaseDlg::CreateAndPlaceDialogs()
{
    m_TabCtrl.ModifyStyle(m_TabStyleRemove, m_TabStyleAdd);

    size_t NumDlg = m_TabDlgVec.size();
    LONG Width = 0, Height = 0;
    for(size_t i = 0 ; i < NumDlg; ++i)
    {
        m_TabCtrl.InsertItem(m_TabDlgVec[i].DialogId , m_TabDlgVec[i].TabName);

        CDialog* pChild = m_TabDlgVec[i].Child;
        int DialogId = m_TabDlgVec[i].DialogId;
        if (!pChild->Create(DialogId, this))
        {
            LogEvent(LE_ERROR, "CTraceTabBaseDlg::CreateAndPlaceDialogs: Failed to build dialog. IDD = %d", DialogId);
            Assert(false);
            return FALSE;
        }
        CRect ChildRect;
        pChild->GetWindowRect(&ChildRect);
        Width = max(Width, ChildRect.right - ChildRect.left);
        Height = max(Height, ChildRect.bottom - ChildRect.top);
    }

    CRect TabWindowRect;
    m_TabCtrl.GetWindowRect(&TabWindowRect);
    LONG TabWidth = TabWindowRect.right - TabWindowRect.left;
    LONG TabHeight = TabWindowRect.bottom - TabWindowRect.top;
    Width = max(Width+10, TabWidth);
    Height = max(Height, TabHeight);
    TabWindowRect.right = TabWindowRect.left + Width;
    TabWindowRect.bottom = TabWindowRect.top + Height;
    LONG TabWindowLeft = TabWindowRect.left;
    LONG TabWindowTop = TabWindowRect.top;
    ScreenToClient(&TabWindowRect);
    m_TabCtrl.MoveWindow(TabWindowRect);
    //SetListBoxTopLeft(TabWindowRect.top + 5, 10+Width);
    //SetListBoxTopLeft(-1, 10+Width);
    SetListBoxTopLeft(-1, Width);

    LONG Left = MAXLONG, Top = 0;
    for(size_t i = 0 ; i < NumDlg; ++i)
	{
        CRect ItemRect;
        m_TabCtrl.GetItemRect(i, &ItemRect);
        Left = min(Left, ItemRect.left);
        Top = max(Top, ItemRect.bottom);
	}
    //Left += TabWindowLeft + 5;
    //Top += TabWindowTop + 5;
    Left += TabWindowLeft;
    Top += TabWindowTop + 2;
    for(size_t i = 0 ; i < NumDlg; ++i)
    {
        CDialog* pChild = m_TabDlgVec[i].Child;
        CRect ChildRect;
        pChild->GetWindowRect(&ChildRect);
        ChildRect.OffsetRect(Left - ChildRect.left, Top - ChildRect.top);
        ScreenToClient(ChildRect);
        pChild->MoveWindow(ChildRect);
    }

    if(!m_TabDlgVec.empty())
    {
        m_TabCtrl.SetCurSel(m_TabItem);
    }
    else
    {
        //no dialogs
        LogEvent(LE_INFO, "CTraceTabBaseDlg::CreateAndPlaceDialogs() No Dialogs so hide the Tab Control");
        m_TabCtrl.ShowWindow(SW_HIDE);
        SetListBoxTopLeft(-1, 8);
    }

    return TRUE;
}