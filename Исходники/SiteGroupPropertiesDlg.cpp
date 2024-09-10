void CSiteGroupPropertiesDlg::EnableOK(bool enable)
{
    CWnd *ok = GetDlgItem(IDOK);
    ASSERT(ok);

    if (ok->IsWindowEnabled()) {
        if (enable == false)
            ok->EnableWindow(FALSE);
    } else {
        if (enable)
            ok->EnableWindow(TRUE);
    }
}