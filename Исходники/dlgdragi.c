void UpdateControls( HWND hwndDlg )
{
    int  i;
    char szFromUl[ 9 ];
    HWND hwndLB;

    hwndLB = WinWindowFromID( hwndDlg, LB_CONTROL );
    WinSendMsg( hwndLB, LM_SELECTITEM, MPFROMSHORT( LIT_NONE ),
                MPFROMLONG( FALSE ) );
    for( i = 0; i < cControlTypes; i++ )
        if( dlgInfo.fsControl & dcControl[ i ].iItem )
            WinSendMsg( hwndLB, LM_SELECTITEM, MPFROMSHORT( i ),
                        MPFROMLONG( TRUE ) );

    hwndLB = WinWindowFromID( hwndDlg, LB_SUPPORTEDOPS );
    WinSendMsg( hwndLB, LM_SELECTITEM, MPFROMSHORT( LIT_NONE ),
                MPFROMLONG( FALSE ) );
    for( i = 0; i < cSupportedOps; i++ )
        if( dlgInfo.fsSupportedOps & dcSupportedOp[ i ].iItem )
            WinSendMsg( hwndLB, LM_SELECTITEM, MPFROMSHORT( i ),
                        MPFROMLONG( TRUE ) );

    for( i = 0; i < cOperations; i++ )
        if( dlgInfo.usOperation == dcOperation[ i ].iItem )
        {
            WinSetDlgItemText( hwndDlg, CB_OPERATION, dcOperation[ i ].szItem );
            break;
        }
    if( i == cOperations )
        WinSetDlgItemText( hwndDlg, CB_OPERATION,
                           _ultoa( (ULONG)dlgInfo.usOperation, szFromUl, 16 ) );

    if( dlgInfo.ulItemID )
        WinSetDlgItemText( hwndDlg, EF_ITEMID,
                           _ultoa( dlgInfo.ulItemID, szFromUl, 16 ) );
    else
        WinSetDlgItemText( hwndDlg, EF_ITEMID, "" );

    WinSetDlgItemText( hwndDlg, CB_TYPE, dlgInfo.szType );
    for( i = 0; i < cTypes; i++ )
    {
       if( !stricmp( ntsType[ i ].szString, dlgInfo.szType ) )
           WinSetDlgItemText( hwndDlg, CB_TYPE, ntsType[ i ].szName );
    }

    WinSetDlgItemText( hwndDlg, EF_CNR_NAME, dlgInfo.szContainerName );
    WinSetDlgItemText( hwndDlg, EF_SOURCE_NAME, dlgInfo.szSourceName );
    WinSetDlgItemText( hwndDlg, EF_TARGET_NAME, dlgInfo.szTargetName );

    WinCheckButton( hwndDlg, CHK_OVERRIDE_ID, dlgInfo.fUseDlgItemID );
    WinCheckButton( hwndDlg, CHK_OVERRIDE_HSTRS, dlgInfo.fUseDlgDragNames );

    WinEnableControl( hwndDlg, EF_ITEMID, dlgInfo.fUseDlgItemID );
    WinEnableControl( hwndDlg, ST_ITEMID, dlgInfo.fUseDlgItemID );
    WinEnableControl( hwndDlg, EF_CNR_NAME, dlgInfo.fUseDlgDragNames );
    WinEnableControl( hwndDlg, EF_SOURCE_NAME, dlgInfo.fUseDlgDragNames );
    WinEnableControl( hwndDlg, EF_TARGET_NAME, dlgInfo.fUseDlgDragNames );
    WinEnableControl( hwndDlg, ST_CNR_NAME, dlgInfo.fUseDlgDragNames );
    WinEnableControl( hwndDlg, ST_SOURCE_NAME, dlgInfo.fUseDlgDragNames );
    WinEnableControl( hwndDlg, ST_TARGET_NAME, dlgInfo.fUseDlgDragNames );
}