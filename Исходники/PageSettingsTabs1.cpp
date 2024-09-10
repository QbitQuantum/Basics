LRESULT PageSettingsTabs1::OnBtnBrowseIcon(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    DoDataExchange(DDX_SAVE);

    int index = 0;
    WCHAR path[MAX_PATH];
    ::GetModuleFileName(NULL, path, ARRAYSIZE(path));

    if( PickIconDlg(NULL, path, ARRAYSIZE(path), &index) == 1 )
    {
        if( index != 0 )
            m_strIcon.Format(L"%s,%d", path, index);
        else
            m_strIcon = path;
        DoDataExchange(DDX_LOAD);
    }

    return 0;
}