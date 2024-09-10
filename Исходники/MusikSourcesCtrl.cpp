void CMusikSourcesCtrl::DoDrag( CMusikPropTreeItem* pItem )
{
    if ( !pItem )
        return;

    COleDataSource datasrc;
    HGLOBAL        hgDrop;
    DROPFILES*     pDrop;
    CStringList    lsDraggedFiles;
    POSITION       pos;
    CString        sFile;
    UINT           uBuffSize = 0;
    TCHAR*         pszBuff;
    FORMATETC      etc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

    // get a list of filenames with the currently
    // selected items...
    CStdStringArray files;

    int nMode = pItem->GetPlaylistType();

    // standard playlist dragged
    if ( nMode == MUSIK_PLAYLIST_TYPE_STANDARD )
        m_Library->GetStdPlaylistFns( pItem->GetPlaylistID(), files, false );

    // now playing dragged..
    else if ( nMode == MUSIK_SOURCES_TYPE_NOWPLAYING )
    {
        if ( m_Player->GetPlaylist() )
        {
            m_Library->BeginTransaction();
            for ( size_t i = 0; i < m_Player->GetPlaylist()->GetCount(); i++ )
                files.push_back( m_Player->GetPlaylist()->GetField( i, MUSIK_LIBRARY_TYPE_FILENAME ) );
            m_Library->EndTransaction();
        }
    }

    // library playlist dragged
    else if ( nMode == MUSIK_SOURCES_TYPE_LIBRARY )
    {
        CMainFrame* pMain = (CMainFrame*)m_Parent;
        if ( pMain->m_LibPlaylist )
        {
            m_Library->BeginTransaction();
            for ( size_t i = 0; i < pMain->m_LibPlaylist->GetCount(); i++ )
                files.push_back( pMain->m_LibPlaylist->GetField( i, MUSIK_LIBRARY_TYPE_FILENAME ) );
            m_Library->EndTransaction();
        }
    }

    else if ( nMode == MUSIK_PLAYLIST_TYPE_DYNAMIC )
        MessageBox( "This operation is not supported yet.", "Musik", MB_ICONINFORMATION | MB_OK );


    if ( !files.size() )
        return;

    // CStringList containing files
    for ( size_t i = 0; i < files.size(); i++ )
    {
        lsDraggedFiles.AddTail( files.at( i ) );
        uBuffSize += files.at( i ).GetLength() + 1;
    }

    files.clear();

    // Add 1 extra for the final null char, and the size of the DROPFILES struct.
    uBuffSize = sizeof(DROPFILES) + sizeof(TCHAR) * (uBuffSize + 1);

    // Allocate memory from the heap for the DROPFILES struct.
    hgDrop = GlobalAlloc ( GHND | GMEM_SHARE, uBuffSize );

    if ( !hgDrop )
        return;

    pDrop = (DROPFILES*) GlobalLock ( hgDrop );

    if ( !pDrop )
    {
        GlobalFree ( hgDrop );
        return;
    }

    // Fill in the DROPFILES struct.
    pDrop->pFiles = sizeof(DROPFILES);

    // If we're compiling for Unicode, set the Unicode flag in the struct to
    // indicate it contains Unicode strings.
#ifdef _UNICODE
    pDrop->fWide = TRUE;
#endif;

    // Copy all the filenames into memory after the end of the DROPFILES struct.
    pos = lsDraggedFiles.GetHeadPosition();
    pszBuff = (TCHAR*) (LPBYTE(pDrop) + sizeof(DROPFILES));

    while ( pos )
    {
        lstrcpy ( pszBuff, (LPCTSTR) lsDraggedFiles.GetNext ( pos ) );
        pszBuff = 1 + _tcschr ( pszBuff, '\0' );
    }

    GlobalUnlock ( hgDrop );

    // Put the data in the data source.
    datasrc.CacheGlobalData ( CF_HDROP, hgDrop, &etc );

    // Add in our own custom data, so we know that the drag originated from our
    // window.  CMyDropTarget::DragEnter() checks for this custom format, and
    // doesn't allow the drop if it's present.  This is how we prevent the user
    // from dragging and then dropping in our own window.
    // The data will just be a dummy bool.
    HGLOBAL hgBool;

    hgBool = GlobalAlloc ( GHND | GMEM_SHARE, sizeof(bool) );

    if ( NULL == hgBool )
    {
        GlobalFree ( hgDrop );
        return;
    }

    // Put the data in the data source.
    etc.cfFormat = m_DropID;
    datasrc.CacheGlobalData ( m_DropID, hgBool, &etc );

    // Start the drag 'n' drop!
    DROPEFFECT dwEffect = datasrc.DoDragDrop ( DROPEFFECT_COPY | DROPEFFECT_MOVE );

    // If the DnD completed OK, we remove all of the dragged items from our
    // list.
    switch ( dwEffect )
    {
    case DROPEFFECT_COPY:
    case DROPEFFECT_MOVE:
    {
        // the copy completed successfully
        // do whatever we need to do here
        TRACE0( "DND from playlist completed successfully. The data has a new owner.\n" );
    }
    break;

    case DROPEFFECT_NONE:
    {
        // This needs special handling, because on NT, DROPEFFECT_NONE
        // is returned for move operations, instead of DROPEFFECT_MOVE.
        // See Q182219 for the details.
        // So if we're on NT, we check each selected item, and if the
        // file no longer exists, it was moved successfully and we can
        // remove it from the list.
        if ( m_IsWinNT )
        {
            // the copy completed successfully
            // on a windows nt machine.
            // do whatever we need to do here

            bool bDeletedAnything = false;
            if ( ! bDeletedAnything )
            {
                // The DnD operation wasn't accepted, or was canceled, so we
                // should call GlobalFree() to clean up.
                GlobalFree ( hgDrop );
                GlobalFree ( hgBool );

                TRACE0( "DND had a problem. We had to manually free the data.\n" );
            }
        }

        // not windows NT
        else
        {
            // We're on 9x, and a return of DROPEFFECT_NONE always means
            // that the DnD operation was aborted.  We need to free the
            // allocated memory.
            GlobalFree ( hgDrop );
            GlobalFree ( hgBool );

            TRACE0( "DND had a problem. We had to manually free the data.\n" );
        }
    }

    break;
    }
}