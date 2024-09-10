int HEFileOpen(HWND hwnd,char *filename,int enableReload)
{
char *buf = NULL;
ULONG size;
int ret = 0;

    WinSendMsg(hwndHMLE,HMLM_NEWDOC,0L,0L);

    size = fileRead2Buf( filename, &buf );

    if( buf != NULL )
    {
        BOOL readOnly = ( BOOL )WinSendMsg( hwndHMLE, HMLM_QUERYREADONLY, 0, 0 );

        WinSendMsg( hwndHMLE, HMLM_SETREADONLY, MPFROMLONG( FALSE ), 0 );

        WinSendMsg(hwndHMLE,HMLM_SETIMPORTEXPORT,buf,MPFROMLONG(size+1));
        WinSendMsg(hwndHMLE,HMLM_IMPORT,0,0);
        WinSendMsg(hwndHMLE,HMLM_SETFIRSTCHAR,MPFROMLONG(0),0);

        WinSendMsg( hwndHMLE, HMLM_SETREADONLY, MPFROMLONG( readOnly ), 0 );
/*
        _fullpath( szFullPath,filename, sizeof( szFullPath ));
        extractDirname();
        _chdir2(szDir);
*/
        if (enableReload) EnableReloadButton(hwnd);
        ret = queryHanTypeBuf( buf );
        free( buf );
    }
    else
    {
//        szFullPath[0]=0;
        ret = -1;
    }

    _fullpath( szFullPath,filename, sizeof( szFullPath ));
    extractDirname();
    _chdir2(szDir);

    HESetTitlebarText(hwnd);
    WinPostMsg(hwndStatbar,STATBAR_USERM_SETMODIFIED,0L,0L);
    WinPostMsg(hwndHMLE,HMLM_SETCHANGED,0,0);
    WinPostMsg(hwndHMLE,HMLM_REFRESH,0,0);

    return ret;
}