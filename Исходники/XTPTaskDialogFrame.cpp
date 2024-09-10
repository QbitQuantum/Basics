LRESULT CXTPTaskDialogFrame::OnDialogUpdateIcon(WPARAM wParam, LPARAM lParam)
{
    if (wParam == TDIE_ICON_MAIN)
    {
        SAFE_DELETE_HICON(m_hIconMain);
        m_hIconMain = CreateIcon((HICON)lParam, (PCWSTR)lParam, m_sizeIconMain, IsMainIconHandleUsed());

        RecalcLayout();
        return TRUE;
    }

    if (wParam == TDIE_ICON_FOOTER)
    {
        SAFE_DELETE_HICON(m_hIconFooter);
        m_hIconFooter = CreateIcon((HICON)lParam, (PCWSTR)lParam, m_sizeIconFooter, IsFooterIconHandleUsed());

        RecalcLayout();
        return TRUE;
    }

    return FALSE;
}