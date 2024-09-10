// ---------------------------------------------------------------------------
// CCmFmUpnpMngr::ScreenSizeL
// ---------------------------------------------------------------------------
//
void CCmFmUpnpMngr::ScreenSizeL()
{
    LOG(_L("[FILL MNGR]\t CCmFmUpnpMngr::ScreenSizeL start"));
    RWsSession session;
    TInt error = session.Connect() ;
    CleanupClosePushL( session );
    if ( !error )
    {
        CWsScreenDevice* screenDevice =
            new ( ELeave ) CWsScreenDevice( session );
        if ( screenDevice && !screenDevice->Construct() )
        {
            iScreenSize = screenDevice->SizeInPixels();
        }
        delete screenDevice;
        screenDevice = NULL;
    }
    else
    {
        TRACE(Print(_L("[FILL MNGR]\t ScreenSizeL error = %d"), error ));
    }

    CleanupStack::PopAndDestroy( &session );
    LOG(_L("[FILL MNGR]\t CCmFmUpnpMngr::ScreenSizeL end"));
}