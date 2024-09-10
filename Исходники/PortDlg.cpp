void CPortDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd *pWnd = GetWindow(GW_CHILD);
    while (pWnd)
    {
        ChangeSize(pWnd,cx,cy);
        pWnd = pWnd->GetWindow(GW_HWNDNEXT);
    }

    GetClientRect(&m_Rect);
}