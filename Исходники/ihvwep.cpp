// Send the UI request and wait for the UI response.
DWORD
SendUIRequestToReceiveKey
(
    PADAPTER_DETAILS    pAdapterDetails,
    DWORD*              pdwKeyLen,
    BYTE**              ppbKeyData
)
{
    DWORD                           dwResult        =   ERROR_SUCCESS;
    DOT11EXT_IHV_UI_REQUEST         uiRequest       =   {0};
    PIHV_UI_REQUEST                 pIHVRequest     =   NULL;
    CHAR                            szTitle[]       =   UI_TITLE_STRING;
    CHAR                            szHelp[]        =   UI_HELP_STRING;
    BOOL                            bLocked         =   FALSE;
    HANDLE                          hUIResponse     =   NULL;



    // CLSID of COM class that implements the UI page. In a real
    // implementation this GUID could be dynamically obtained.
    CLSID                            uiPageClsid    =
    {
        /* 4A01F9F9-6012-4343-A8C4-10B5DF32672A */
        0x4A01F9F9,
        0x6012,
        0x4343,
        {0xA8, 0xC4, 0x10, 0xB5, 0xDF, 0x32, 0x67, 0x2A}
    };

    ASSERT( pAdapterDetails );

    // prepare the IHV request.
    uiRequest.dwByteCount = sizeof(IHV_UI_REQUEST);
    uiRequest.pvUIRequest = (BYTE*) PrivateMemoryAlloc( sizeof(IHV_UI_REQUEST) );
    if ( !(uiRequest.pvUIRequest) )
    {
        dwResult = ERROR_OUTOFMEMORY;
        BAIL( );
    }

    pIHVRequest = (IHV_UI_REQUEST*)uiRequest.pvUIRequest;


    memcpy(  pIHVRequest->szTitle ,  szTitle  , sizeof(szTitle) );
    memcpy(  pIHVRequest->szHelp  ,  szHelp   , sizeof(szHelp)  );

    uiRequest.dwSessionId = WTSGetActiveConsoleSessionId( );
    uiRequest.UIPageClsid = uiPageClsid;

    // acquire the lock to register the request.
    EnterCriticalSection( &g_csSynch );
    bLocked = TRUE;

    // create new request guid.
    dwResult = UuidCreate( &(uiRequest.guidUIRequest) );
    BAIL_ON_WIN32_ERROR(dwResult);

    // free the existing response.
    PrivateMemoryFree( pAdapterDetails->pbResponse );
    pAdapterDetails->pbResponse = NULL;

    // register the guid.
    pAdapterDetails->currentGuidUIRequest = uiRequest.guidUIRequest;

    // Initializing the event this thread
    // would be waiting on later.
    ResetEvent( pAdapterDetails->hUIResponse );

    hUIResponse = pAdapterDetails->hUIResponse;

    // leave the lock since this thread needs
    // to wait for the response.
    LeaveCriticalSection( &g_csSynch );
    bLocked = FALSE;


    // send the request.
    dwResult =
        (g_pDot11ExtApi->Dot11ExtSendUIRequest)
        (
            pAdapterDetails->hDot11SvcHandle,
            &uiRequest
        );
    BAIL_ON_WIN32_ERROR(dwResult);

    TRACE_MESSAGE( "Sent UI request to receive key." );

    // Waiting for UI response.
    // This would be triggered
    // off if no UI response
    // is received.
    dwResult =
        WaitForSingleObject
        (
            hUIResponse,
            1000 * 60 * 5                    // 5 minutes
        );

    // acquire the lock - required for both success and failure.
    EnterCriticalSection( &g_csSynch );
    bLocked = TRUE;

    ZeroMemory( &(pAdapterDetails->currentGuidUIRequest), sizeof( GUID ) );

    if ( WAIT_OBJECT_0 == dwResult )
    {
        dwResult = ERROR_SUCCESS;
    }
    BAIL_ON_WIN32_ERROR(dwResult);

    if ( NULL == pAdapterDetails->pbResponse )
    {
        dwResult = ERROR_INVALID_STATE;
        BAIL_ON_WIN32_ERROR(dwResult);
    }


    // At this point in the code a response
    // has been received, and the thread
    // has not been aborted.

    (*ppbKeyData) = pAdapterDetails->pbResponse;
    pAdapterDetails->pbResponse = NULL;

    (*pdwKeyLen) = pAdapterDetails->dwResponseLen;


    // Convert the Unicode string to ASCII.
    dwResult =
        ConvertStringToKey
        (
            *ppbKeyData,
            pdwKeyLen
        );
    BAIL_ON_WIN32_ERROR(dwResult);

    pAdapterDetails->bModifyCurrentProfile  =   TRUE;

error:
    if ( bLocked )
    {
        LeaveCriticalSection( &g_csSynch );
    }
    PrivateMemoryFree( uiRequest.pvUIRequest );
    return dwResult;
}