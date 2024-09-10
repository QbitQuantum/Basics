void COnlineUsersDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
    CMenu menu;
    menu.LoadMenu(IDR_MENU_ONLINEUSERS);
    TRANSLATE(menu);
    CMenu* pop = menu.GetSubMenu(0);
    if(!pop)
        return;

    UINT uCmd = pop->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN |
        TPM_RIGHTBUTTON, point.x, point.y,
        this, NULL );
    MenuCommand(uCmd);
}