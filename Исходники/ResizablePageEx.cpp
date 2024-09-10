BOOL CResizablePageEx::OnInitDialog()
{
    CPropertyPageEx::OnInitDialog();

    // set the initial size as the min track size
    CRect rc;
    GetWindowRect(&rc);
    SetMinTrackSize(rc.Size());

    // HACK:  temporarily abandon subclassing
    // CAUSE: system subclasses this window after this message
    // ISSUE: our WindowProc is not the first to be called
    //        and we miss some painting related messages
    if (Attach(UnsubclassWindow()))
    {
        CWnd* pParent = GetParent();
        pParent->LockWindowUpdate();
        Post_SheetPageExHack(pParent->GetSafeHwnd(), m_hWnd);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}