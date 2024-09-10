BOOL PASCAL _Cover_mciSetYieldProc (UINT uDeviceID, YIELDPROC fpYieldProc,
                DWORD dwYieldData)
{
    return( mciSetYieldProc( uDeviceID,
        SetProc( (FARPROC)fpYieldProc, GETPROC_MMSYSTEM_YIELDPROC ), dwYieldData ) );
}