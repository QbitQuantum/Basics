void WREDDEEnd( void )
{
    int         i;

    if( IdInst != 0 ) {
        DdeNameService( IdInst, (HSZ)NULL, (HSZ)NULL, DNS_UNREGISTER );
        for( i = 0; i < NUM_TOPICS; i++ ) {
            if( Topics[i].htopic != (HSZ)NULL ) {
                DdeFreeStringHandle( IdInst, Topics[i].htopic );
            }
        }
        for( i = 0; i < NUM_SERVERS; i++ ) {
            if( EditServers[i].htopic != (HSZ)NULL ) {
                DdeFreeStringHandle( IdInst, EditServers[i].htopic );
            }
            if( EditServers[i].hservice != (HSZ)NULL ) {
                DdeFreeStringHandle( IdInst, EditServers[i].hservice );
            }
        }
        if( hDialogDump != (HSZ)NULL ) {
            DdeFreeStringHandle( IdInst, hDialogDump );
        }
        if( hImageDump != (HSZ)NULL ) {
            DdeFreeStringHandle( IdInst, hImageDump );
        }
        if( hFileItem != (HSZ)NULL ) {
            DdeFreeStringHandle( IdInst, hFileItem );
        }
        if( hIs32BitItem != (HSZ)NULL ) {
            DdeFreeStringHandle( IdInst, hIs32BitItem );
        }
        if( hDataItem != (HSZ)NULL ) {
            DdeFreeStringHandle( IdInst, hDataItem );
        }
        if( hNameItem != (HSZ)NULL ) {
            DdeFreeStringHandle( IdInst, hNameItem );
        }
        if( hServiceName != (HSZ)NULL ) {
            DdeFreeStringHandle( IdInst, hServiceName );
        }
        DdeUninitialize( IdInst );
    }
    if( DdeProc != (FARPROC)NULL ) {
        FreeProcInstance( DdeProc );
    }
}