void COutputWindowView::OnContextMenu( CWnd* pWnd, CPoint point )
{
    CMenu menu;
    CMenu* pPopupMenu;
    int iStart;
    int iEnd;

    if( pWnd->m_hWnd != m_hWnd )
    {
        return;
    }

    menu.LoadMenu( IDR_OUTPUTLOGEDIT_CONTEXT );
    pPopupMenu = menu.GetSubMenu( 0 );
    GetEditCtrl().GetSel( iStart, iEnd );
    if( iEnd == iStart )
    {
        pPopupMenu->EnableMenuItem( ID_OUTPUTLOGEDIT_COPY, MF_GRAYED );
    }
    pPopupMenu->TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y,
                                this, NULL );
    menu.DestroyMenu();
}