/*
 * GetThreadInfo
 */
BOOL GetThreadInfo( DWORD pid, DWORD tid, ThreadStats *info ) {

    BOOL                        noerror;
    HANDLE                      hdl;
    THREADENTRY32               thrddata;

    noerror = FALSE;
    memset( &thrddata, 0, sizeof( THREADENTRY32 ) );
    thrddata.dwSize =  sizeof( THREADENTRY32 );
    hdl = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 );
    noerror = Thread32First( hdl, &thrddata );
    while( noerror ) {
        if( tid == thrddata.th32ThreadID ) {
            if( pid == thrddata.th32OwnerProcessID ) {
                break;
            }
        }
        noerror = Thread32Next( hdl, &thrddata );
    }
    if( noerror ) {
        info->tid = tid;
        info->pid = pid;
        info->base_pri = thrddata.tpBasePri;
        info->cur_pri = thrddata.tpBasePri + thrddata.tpDeltaPri;
        info->state = -1;
        info->wait_reason = -1;
    }
    CloseHandle( hdl );
    return( noerror );
}