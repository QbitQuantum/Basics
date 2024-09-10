int GUIGetFileName( gui_window *wnd, open_file_name *ofn )
{
    OPENFILENAME        wofn;
    bool                issave;
    int                 rc;
    unsigned            drive;
#if defined(HAVE_DRIVES)
    unsigned            old_drive;
    unsigned            drives;
#endif

    LastPath = NULL;
    if( ofn->initial_dir != NULL && ofn->initial_dir[0] != '\0' && ofn->initial_dir[1] == ':' ) {
        drive = ofn->initial_dir[0];
        memmove( ofn->initial_dir, ofn->initial_dir+2, strlen( ofn->initial_dir+2 ) + 1 );
    } else {
        drive = 0;
    }

    memset( &wofn, 0 , sizeof( wofn ) );

    if( ofn->flags & OFN_ISSAVE ) {
        issave = true;
    } else {
        issave = false;
    }

    wofn.Flags = 0;
    if( hookFileDlg ) {
        wofn.Flags |= OFN_ENABLEHOOK;
    }
    if( !(ofn->flags & OFN_CHANGEDIR) ) {
        wofn.Flags |= OFN_NOCHANGEDIR;
    }

    if( ofn->flags & OFN_OVERWRITEPROMPT ) {
        wofn.Flags |= OFN_OVERWRITEPROMPT;
    }
    if( ofn->flags & OFN_HIDEREADONLY ) {
        wofn.Flags |= OFN_HIDEREADONLY;
    }
    if( ofn->flags & OFN_FILEMUSTEXIST ) {
        wofn.Flags |= OFN_FILEMUSTEXIST;
    }
    if( ofn->flags & OFN_PATHMUSTEXIST ) {
        wofn.Flags |= OFN_PATHMUSTEXIST;
    }
    if( ofn->flags & OFN_ALLOWMULTISELECT ) {
        wofn.Flags |= OFN_ALLOWMULTISELECT;
    }
    wofn.hwndOwner = GUIGetParentFrameHWND( wnd );
    wofn.hInstance = GUIMainHInst;
    wofn.lStructSize = sizeof( wofn );
    wofn.lpstrFilter = ofn->filter_list;
    wofn.nFilterIndex = ofn->filter_index;
    wofn.lpstrFile = ofn->file_name;
    wofn.nMaxFile = ofn->max_file_name;
    wofn.lpstrFileTitle = ofn->base_file_name;
    wofn.nMaxFileTitle = ofn->max_base_file_name;
    wofn.lpstrTitle = ofn->title;
    wofn.lpstrInitialDir = ofn->initial_dir;
    wofn.lpfnHook = (LPOFNHOOKPROC)NULL;
    if( hookFileDlg ) {
        wofn.lpfnHook = (LPOFNHOOKPROC)MakeOpenFileHookProcInstance( OpenHook, GUIMainHInst );
    }

#if defined( HAVE_DRIVES )
    if( drive ) {
        _dos_getdrive( &old_drive );
        _dos_setdrive( tolower( drive ) - 'a' + 1, &drives );
    }
#endif
    if( issave ) {
        rc = GetSaveFileName( &wofn );
    } else {
        rc = GetOpenFileName( &wofn );
    }

    if( hookFileDlg ) {
        (void)FreeProcInstance( (FARPROC)wofn.lpfnHook );
    }

    if( LastPath && ( !rc || !( ofn->flags & OFN_WANT_LAST_PATH ) ) ) {
        GUIMemFree( LastPath );
        LastPath = NULL;
    }
    ofn->last_path = LastPath;
#if defined( HAVE_DRIVES )
    if( drive ) {
        _dos_setdrive( old_drive, &drives );
    }
#endif
    if( rc ) {
        return( OFN_RC_FILE_SELECTED );
    }
    if( !CommDlgExtendedError() ) {
        return( OFN_RC_NO_FILE_SELECTED );
    }
    return( OFN_RC_FAILED_TO_INITIALIZE );
} /* _GUIGetFileName */