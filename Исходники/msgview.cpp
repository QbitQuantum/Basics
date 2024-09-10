void CMsgView::OnContextMenu(CWnd *pWnd, CPoint point) 
{
    CFrameWnd *pFrame;
    CMenu menu;
    CMenu *pPopupMenu;
    int nStart;
    int nEnd;
    UINT uiEnable;

    // make sure window is active

    pFrame = GetParentFrame ();
    ASSERT (pFrame != NULL);
    if (pFrame != NULL)
    {
        pFrame->ActivateFrame ();
    };

    if (!menu.LoadMenu (IDR_COMPILEVW_POPUP))
    {
        return;
    }
    pPopupMenu = menu.GetSubMenu (0);
    ASSERT (pPopupMenu != NULL);
    if (pPopupMenu == NULL)
    {
        return;
    }
    GetEditCtrl().GetSel(nStart, nEnd);
    uiEnable = (nStart == nEnd) ? MF_DISABLED | MF_GRAYED : MF_ENABLED;
    pPopupMenu->EnableMenuItem(IDM_MSG_COPY, uiEnable);
    pPopupMenu->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}