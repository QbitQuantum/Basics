void CP4ListBrowse::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // Slide the OK and Cancel buttons to the bottom of dlg
    CWnd *pRefresh = GetDlgItem(IDC_REFRESH);
    CWnd *pBack = GetDlgItem(IDC_BACK);
    CWnd *pOK   = GetDlgItem(IDOK);
    CWnd *pCancel = GetDlgItem(IDCANCEL);
    CWnd *pDescribe = GetDlgItem(IDC_DESCRIBE);

    if(!pOK)
        return;

    CRect rect;
    GetWindowRect(&rect);
    int dx = rect.Width() - m_LastRect.Width();
    int dy = rect.Height() - m_LastRect.Height();
    // Save the new size
    m_LastRect = rect;

    // Move down
    pRefresh->GetWindowRect(&rect);
    ScreenToClient(rect);
    pRefresh->SetWindowPos(NULL, rect.left, rect.top + dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // Move down and slide right
    pBack->GetWindowRect(&rect);
    ScreenToClient(rect);
    pBack->SetWindowPos(NULL, rect.left + dx, rect.top + dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    pOK->GetWindowRect(&rect);
    ScreenToClient(rect);
    pOK->SetWindowPos(NULL, rect.left + dx, rect.top + dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    pCancel->GetWindowRect(&rect);
    ScreenToClient(rect);
    pCancel->SetWindowPos(NULL, rect.left + dx, rect.top + dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    pDescribe->GetWindowRect(&rect);
    ScreenToClient(rect);
    pDescribe->SetWindowPos(NULL, rect.left + dx, rect.top + dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // Increase the size of the list both horiz and vert
    CWnd *pList = GetDlgItem(IDC_P4LIST);
    pList->GetWindowRect(&rect);
    pList->SetWindowPos(NULL, 0, 0, rect.right - rect.left + dx,
                        rect.bottom - rect.top + dy, SWP_NOMOVE | SWP_NOZORDER);
    RedrawWindow();
}