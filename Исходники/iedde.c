/*
 * IEDDEDumpConversation
 */
BOOL IEDDEDumpConversation( HINSTANCE inst )
{
    HCONV       hconv;
    HSZ         hservice;
    HSZ         htopic;
    BOOL        ok;

    ok = IEDDEStart( inst );

    if( ok ) {
        hservice = DdeCreateStringHandle( IdInst, WRE_SERVICE_NAME, CP_WINANSI );
        ok = (hservice != (HSZ)NULL);
    }

    if( ok ) {
        htopic = DdeCreateStringHandle( IdInst, WRE_IMAGE_DUMP, CP_WINANSI );
        ok = (htopic != (HSZ)NULL);
    }

    if( ok ) {
        // We expect the server to reject this connect attempt.
        // If it doesn't, then we terminate the conversation.
        hconv = DdeConnect( IdInst, hservice, htopic, (LPVOID)NULL );
        if( hconv != (HCONV)NULL ) {
            DdeDisconnect( hconv );
        }
    }

    if( hservice != (HSZ)NULL ) {
        DdeFreeStringHandle( IdInst, hservice );
    }

    if( htopic != (HSZ)NULL ) {
        DdeFreeStringHandle( IdInst, htopic );
    }

    IEDDEEnd();

    if( !ok ) {
        IEDisplayErrorMsg( WIE_DDEINITTITLE, WIE_DDETERMINATIONMSG,
                           MB_OK | MB_ICONINFORMATION );
    }

    return( ok );

} /* IEDDEDumpConversation */