LRESULT	CDebugCommandsView::OnSizing(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CRect listRect;
    m_CommandList.GetWindowRect(listRect);

    CRect headRect;
    CHeaderCtrl listHead = m_CommandList.GetHeader();
    listHead.GetWindowRect(&headRect);

    int rowsHeight = listRect.Height() - headRect.Height();

    int nRows = (rowsHeight / m_RowHeight);

    if (m_CommandListRows != nRows)
    {
        m_CommandListRows = nRows;
        ShowAddress(m_StartAddress, TRUE);
    }

    m_RegisterTabs.RedrawCurrentTab();

    // Fix cmd list header
    listHead.ResizeClient(listRect.Width(), headRect.Height());

    return FALSE;
}