void CSystemDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here
    if (m_list_dialupass.IsWindowVisible())
        return;

    CMenu	popup;
    popup.LoadMenu(IDR_PSLIST);
    CMenu*	pM = popup.GetSubMenu(0);
    CPoint	p;
    GetCursorPos(&p);

    pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
    *pResult = 0;
}