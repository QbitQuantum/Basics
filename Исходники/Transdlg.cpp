void CTransDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
    CPoint lpt = point;
    ClientToScreen(&lpt);
    CMenu* popup = m_popup.GetSubMenu(0);

    // display the popup menu
    popup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, lpt.x, lpt.y,
                          (CWnd*) this, NULL);

    // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
    GetParent()->PostMessage(WM_NULL, 0, 0);

    CDialog::OnRButtonDown(nFlags, point);
}