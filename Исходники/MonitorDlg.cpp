DWORD WINAPI FileSystemWatcher::Routine( LPVOID lParam )
{
    FileSystemWatcher* pFsw = (FileSystemWatcher*)lParam;
	CString tem1,tem2;
	CString str = (_T("[") + pFsw->WatchedDir + "] 开始监视!");
    pFsw->hDir = CreateFile(
        pFsw->WatchedDir,
        GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );
    if( INVALID_HANDLE_VALUE == pFsw->hDir ) return false;

    char buf[ 2*(sizeof(FILE_NOTIFY_INFORMATION)+MAX_PATH) ];
    FILE_NOTIFY_INFORMATION* pNotify=(FILE_NOTIFY_INFORMATION *)buf;
    DWORD BytesReturned;
    while(true)
    {
        if( ReadDirectoryChangesW( pFsw->hDir,
            pNotify,
            sizeof(buf),
            true,
            FILE_NOTIFY_CHANGE_FILE_NAME|
            FILE_NOTIFY_CHANGE_DIR_NAME|
            FILE_NOTIFY_CHANGE_ATTRIBUTES|
            FILE_NOTIFY_CHANGE_SIZE|
            FILE_NOTIFY_CHANGE_LAST_WRITE|
            FILE_NOTIFY_CHANGE_LAST_ACCESS|
            FILE_NOTIFY_CHANGE_CREATION|
            FILE_NOTIFY_CHANGE_SECURITY,
            &BytesReturned,
            NULL,
            NULL ) )
        {
            char tmp[MAX_PATH], str1[MAX_PATH], str2[MAX_PATH];
            memset( tmp, 0, sizeof(tmp) );
            WideCharToMultiByte( CP_ACP,0,pNotify->FileName,pNotify->FileNameLength/2,tmp,99,NULL,NULL );
            strcpy_s( str1,260, tmp );

            if( 0 != pNotify->NextEntryOffset )
            {
                PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pNotify+pNotify->NextEntryOffset);
                memset( tmp, 0, sizeof(tmp) );
                WideCharToMultiByte( CP_ACP,0,p->FileName,p->FileNameLength/2,tmp,99,NULL,NULL );
                strcpy_s( str2,260, tmp );
            }
			tem1= str1;
			tem2= str2;
            pFsw->DealFunc((ACTION)pNotify->Action, tem1, tem2);
        } else
        {
            break;
        }
    }
    return 0;
}