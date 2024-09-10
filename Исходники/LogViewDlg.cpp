void CLogViewDlg::OnNMRClickListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    *pResult = 0;

    POINT Pt;
    GetCursorPos(&Pt);
    CMenu menu;
    menu.LoadMenu(IDR_MAIN_MENU);
    menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON, Pt.x, Pt.y, this);
}