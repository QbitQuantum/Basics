void CFileTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
    if (point.x == -1)
    {
        HTREEITEM ht = GetSelectedItem();
        RECT rect;

        GetItemRect( ht, &rect, true );
        ClientToScreen( &rect );

        /* Offset the popup menu origin so
        * we can read some of the text
        */

        point.x = rect.left + 15;
        point.y = rect.top + 8;
    }

    CMenu menu;
    menu.LoadMenu(IDR_MENU_TREEVIEW);

    CMenu * pop;
    pop = menu.GetSubMenu(0);

    UINT uCmd = pop->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN |	TPM_RIGHTBUTTON, point.x, point.y, this, NULL );

    /* Menu item chosen ? */
    if (uCmd != 0)
    {
        switch(uCmd)
        {
            case ID_TREEVIEW_REFRESH:
                OnFileRefresh();
                break;

            case ID_TREEVIEW_COPYPATH:
                OnFileCopyPathToClipboard();
                break;

            case ID_TREEVIEW_OPENPATH:
                OnOpenPathInExplorer();
                break;

        }
    }

    menu.DestroyMenu();
}