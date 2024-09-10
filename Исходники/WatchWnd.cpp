/**
 * WM_WATCHTAB_CONTEXTMENU handler. This message is sent by the tab
 * control on right mouse button click.
 *
 * @param           wparam: not used
 *                  lparam: pointer to WatchTabHitInfo
 * @return          0
 * @exception       -
 * @see             
*/
LRESULT CWatchWindow::OnWatchTabContextMenu (WPARAM wparam, LPARAM lparam)
{
    WatchTabHitInfo *pHitInfo;
    CMenu menuBar;
    CMenu *pMenu;
    bool bEnable;


    // LPARAM is a pointer to WatchTabHitInfo.
    //////////////////////////////////////////

    pHitInfo = (WatchTabHitInfo *)lparam;
    if (pHitInfo == NULL)
        return (0);


    // Remember the tab we hit (-1 if none). Menu item command
    // handlers might find this information useful.
    //////////////////////////////////////////////////////////

    m_iContextMenuTab = pHitInfo->m_iTabIndex;


    // Load the context menu and enable/disable menu items according to where the user clicked.
    // "Add Pane" is always enabled.
    // "Remove Pane" is enabled only if the user hit a tab, this tab is a custom pane tab and
    // we have more than one custom pane tab.
    ///////////////////////////////////////////////////////////////////////////////////////////

    if (!menuBar.LoadMenu (IDM_WATCH_TABMENU))
        return (0);

    pMenu = menuBar.GetSubMenu (0);
    if (pMenu == 0)
        return (0);

    pMenu->EnableMenuItem (ID_WATCH_ADD_PANE, MF_BYCOMMAND | MF_ENABLED);
    bEnable = m_iContextMenuTab != -1 &&
              m_iCustomPaneCount > 1 &&
              pHitInfo->m_iTabIndex >= 0 &&
              pHitInfo->m_iTabIndex < m_iCustomPaneCount;
    pMenu->EnableMenuItem (ID_WATCH_REMOVE_PANE, MF_BYCOMMAND | (bEnable ? MF_ENABLED : MF_GRAYED));


    // Show and track popup menu. Command handlers are called from inside here.
    ///////////////////////////////////////////////////////////////////////////

    pMenu->TrackPopupMenu (TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pHitInfo->m_Point.x, pHitInfo->m_Point.y, this);

    return (0);
}