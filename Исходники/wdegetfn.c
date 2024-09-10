char *WdeGetFileName( WdeGetFileStruct *gf, DWORD flags, WdeGetFileNameAction action )
{
    OPENFILENAME        wdeofn;
    HWND                owner_window;
    DWORD               error;
    char                fn_drive[_MAX_DRIVE];
    char                fn_dir[_MAX_DIR];
    char                fn_name[_MAX_FNAME];
    char                fn_ext[_MAX_EXT];
    char                ext[_MAX_EXT + 1];
    HINSTANCE           app_inst;
    int                 len;
    int                 filter;
    bool                ret;

    if( gf == NULL ) {
        return( NULL );
    }

    owner_window = WdeGetMainWindowHandle();
    app_inst = WdeGetAppInstance();

    if( app_inst == NULL || owner_window == NULL ) {
        return( NULL );
    }

    /* set the initial directory */
    if( *wde_initial_dir == '\0' ) {
        getcwd( wde_initial_dir, MAXFILENAME );
    }

    if( gf->title != NULL ) {
        len = strlen( gf->title );
        if ( len < MAX_NAME ) {
            memcpy( wdefntitle, gf->title, len + 1 );
        } else {
            memcpy( wdefntitle, gf->title, MAX_NAME );
            wdefntitle[MAX_NAME - 1] = 0;
        }
    } else {
        wdefntitle[0] = 0;
    }

    filter = 0;

    if( gf->file_name != NULL && *gf->file_name != '\0' ) {
        _splitpath( gf->file_name, fn_drive, fn_dir, fn_name, fn_ext );
        if( *fn_drive != '\0' || *fn_dir != '\0' ) {
            _makepath( wde_initial_dir, fn_drive, fn_dir, NULL, NULL );
        }
        _makepath( wde_file_name, NULL, NULL, fn_name, fn_ext );
        if( fn_ext[0] != '\0' ) {
            ext[0] = '*';
            strcpy( ext + 1, fn_ext );
            filter = WdeFindFileFilterIndex( gf->filter, ext );
        }
    } else {
        wde_file_name[0] = 0;
    }

    if( filter == 0 ) {
        filter = WdeFindFileFilterIndex( gf->filter, WdeFileFilter );
        if( filter < 1 ) {
            filter = 1;
        }
    }

    // CTL3D no longer requires this
#if !defined( __NT__ )
    flags |= OFN_ENABLEHOOK;
#endif
    /* initialize the OPENFILENAME struct */
    memset( &wdeofn, 0, sizeof( OPENFILENAME ) );

    /* fill in non-variant fields of OPENFILENAME struct */
    wdeofn.lStructSize = sizeof( OPENFILENAME );
    wdeofn.hwndOwner = owner_window;
    wdeofn.hInstance = app_inst;
    wdeofn.lpstrFilter = gf->filter;
    wdeofn.lpstrCustomFilter = NULL;
    wdeofn.nMaxCustFilter = 0;
    wdeofn.nFilterIndex = filter;
    wdeofn.lpstrFile = wde_file_name;
    wdeofn.nMaxFile = MAXFILENAME;
    wdeofn.lpstrFileTitle = wdefntitle;
    wdeofn.nMaxFileTitle = MAXFILENAME;
    wdeofn.lpstrInitialDir = wde_initial_dir;
    wdeofn.lpstrTitle = wdefntitle;
    wdeofn.Flags = flags;
#if !defined( __NT__ )
    wdeofn.lpfnHook = (LPOFNHOOKPROC)MakeProcInstance( (FARPROC)WdeOpenHookProc, app_inst );
#endif

#if 0
    wdeofn.nFileOffset = 0L;
    wdeofn.nFileExtension = 0L;
    wdeofn.lpstrDefExt = NULL;
    wdeofn.lCustData = NULL;
    wdeofn.lpfnHook = NULL;
    wdeofn.lpTemplateName = NULL;
#endif

    if( action == WDEOPENFILE ) {
        ret = GetOpenFileName( (LPOPENFILENAME)&wdeofn );
    } else if( action == WDESAVEFILE ) {
        ret = GetSaveFileName( (LPOPENFILENAME)&wdeofn );
    } else {
        return( NULL );
    }

#ifndef __NT__
    if( wdeofn.lpfnHook != NULL ) {
        FreeProcInstance( (FARPROC)wdeofn.lpfnHook );
    }
#endif

    gf->fn_offset = wdeofn.nFileOffset;
    gf->ext_offset = wdeofn.nFileExtension;

    /* show the dialog box */
    if( !ret ) {
        error = CommDlgExtendedError();
        if( error ) {
            WdeDisplayErrorMsg( WDE_ERRORSELECTINGFILE );
        }
        return( NULL );
    } else {
        memcpy( wde_initial_dir, wde_file_name, wdeofn.nFileOffset );
        if( wde_initial_dir[wdeofn.nFileOffset - 1] == '\\' &&
            wde_initial_dir[wdeofn.nFileOffset - 2] != ':' ) {
            wde_initial_dir[wdeofn.nFileOffset - 1] = '\0';
        } else {
            wde_initial_dir[wdeofn.nFileOffset] = '\0';
        }
        _splitpath( wde_file_name, NULL, NULL, NULL, fn_ext + 1 );
        if( fn_ext[1] != '\0' ) {
            fn_ext[0] = '*';
            WdeSetFileFilter( fn_ext );
        } else {
            char *out_ext;
            out_ext = WdeFindFileFilterFromIndex( gf->filter, wdeofn.nFilterIndex );
            if( out_ext[2] != '*' ) {
                strcat( wde_file_name, &out_ext[1] );
            }
        }
    }

    UpdateWindow( WdeGetMainWindowHandle() );

    return( WdeStrDup( wde_file_name ) );
}