void CHistoryCombo::SetAutoComplete(DWORD flags)
{
    // use for ComboEx
    HWND hwndEdit = (HWND)::SendMessage(this->m_hWnd, CBEM_GETEDITCONTROL, 0, 0);
    if (NULL == hwndEdit)
    {
        // Try the unofficial way of getting the edit control CWnd*
        CWnd* pWnd = this->GetDlgItem(1001);
        if(pWnd)
        {
            hwndEdit = pWnd->GetSafeHwnd();
        }
    }
    if (hwndEdit)
        SHAutoComplete(hwndEdit, flags);
}