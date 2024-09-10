HRESULT
UserScanInit (
    _Inout_  PUSER_SCAN_CONTEXT Context
    )
/*++

Routine Description:

    This routine initializes all the necessary data structures and forks listening threads.
    The caller thread is responsible for calling UserScanFinalize(...) to cleanup the 
    data structures and close the listening threads.

Arguments:

    Context    - User scan context, please see userscan.h

Return Value:

    S_OK if successful. Otherwise, it returns a HRESULT error value.

--*/
{
    HRESULT  hr = S_OK;
    ULONG    i = 0;
    HANDLE   hEvent = NULL;
    PSCANNER_THREAD_CONTEXT  scanThreadCtxes = NULL;
    HANDLE   hListenAbort = NULL;
    AV_CONNECTION_CONTEXT connectionCtx = {0};
    
    if (NULL == Context) {
    
        return MAKE_HRESULT(SEVERITY_ERROR, 0, E_POINTER);
    }
    
    //
    //  Create the abort listening thead.
    //  This thread is particularly listening the abortion event.
    //
    
    hListenAbort = CreateThread( NULL,
                                 0,
                                 (LPTHREAD_START_ROUTINE)UserScanListenAbortProc,
                                 Context,
                                 CREATE_SUSPENDED,
                                 NULL );
    
    if (NULL == hListenAbort) {
    
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Cleanup;
    }
    
    //
    //  Initialize scan thread contexts.
    //
    
    scanThreadCtxes = HeapAlloc(GetProcessHeap(), 0, sizeof(SCANNER_THREAD_CONTEXT) * USER_SCAN_THREAD_COUNT);
    if (NULL == scanThreadCtxes) {
    
        hr = MAKE_HRESULT(SEVERITY_ERROR, 0, E_OUTOFMEMORY);
        goto Cleanup;
    }
    
    ZeroMemory(scanThreadCtxes, sizeof(SCANNER_THREAD_CONTEXT) * USER_SCAN_THREAD_COUNT);
    
    //
    //  Create scan listening threads.
    //
    
    for (i = 0;
         i < USER_SCAN_THREAD_COUNT;
         i ++ ) {
         
        scanThreadCtxes[i].Handle = CreateThread( NULL,
                                                  0,
                                                  (LPTHREAD_START_ROUTINE)UserScanWorker,
                                                  Context,
                                                  CREATE_SUSPENDED,
                                                  &scanThreadCtxes[i].ThreadId );
        
        if (NULL == scanThreadCtxes[i].Handle) {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Cleanup;
        }
        InitializeCriticalSection(&(scanThreadCtxes[i].Lock));
    }
    
    //
    //  Prepare the scan communication port.
    //
    
    connectionCtx.Type = AvConnectForScan;
    hr = FilterConnectCommunicationPort( AV_SCAN_PORT_NAME,
                                         0,
                                         &connectionCtx,
                                         sizeof(AV_CONNECTION_CONTEXT),
                                         NULL,
                                         &Context->ConnectionPort );
    if (FAILED(hr)) {
    
        Context->ConnectionPort = NULL;
        goto Cleanup;
    }
    
    //
    //  Create the IO completion port for asynchronous message passing. 
    //
    
    Context->Completion = CreateIoCompletionPort( Context->ConnectionPort,
                                                  NULL,
                                                  0,
                                                  USER_SCAN_THREAD_COUNT );
    
    if ( NULL == Context->Completion ) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Cleanup;
    }
    
    Context->ScanThreadCtxes = scanThreadCtxes;
    Context->AbortThreadHandle = hListenAbort;
    
    //
    //  Resume all the scanning threads.
    //
    
    for (i = 0;
         i < USER_SCAN_THREAD_COUNT;
         i ++ ) {
         if ( ResumeThread( scanThreadCtxes[i].Handle ) == -1) {
         
            fprintf(stderr, "[UserScanInit]: ResumeThread scan listening thread failed.\n");
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Cleanup;
         }
    }
    
    //
    //  Resume abort listening thread.
    //
    
    if ( ResumeThread( hListenAbort ) == -1 ) {
        fprintf(stderr, "[UserScanInit]: ResumeThread abort listening thread failed.\n");
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Cleanup;
    }
    
    //
    //  Pump messages into queue of completion port.
    //
    
    for (i = 0;
         i < USER_SCAN_THREAD_COUNT;
         i ++ ) {

        PSCANNER_MESSAGE msg = HeapAlloc( GetProcessHeap(), 0, sizeof( SCANNER_MESSAGE ) );
        
        if (NULL == msg) {
        
            hr = MAKE_HRESULT(SEVERITY_ERROR, 0, E_OUTOFMEMORY);
            goto Cleanup;
        }
        
        FillMemory( &msg->Ovlp, sizeof(OVERLAPPED), 0);
        hr = FilterGetMessage( Context->ConnectionPort,
                               &msg->MessageHeader,
                               FIELD_OFFSET( SCANNER_MESSAGE, Ovlp ),
                               &msg->Ovlp );

        if (hr == HRESULT_FROM_WIN32( ERROR_IO_PENDING )) {
        
            hr = S_OK;
            
        } else {
        
            fprintf(stderr, "[UserScanInit]: FilterGetMessage failed.\n");
            DisplayError(hr);
            HeapFree(GetProcessHeap(), 0, msg );
            goto Cleanup;
        }
    }
    
    return hr;
    
Cleanup:

    if (Context->Completion && !CloseHandle(Context->Completion)) {
    
        fprintf(stderr, "[UserScanInit] Error! Close completion port failed.\n");
        DisplayError(HRESULT_FROM_WIN32(GetLastError()));
    }
    if (Context->ConnectionPort && !CloseHandle(Context->ConnectionPort)) {
    
        fprintf(stderr, "[UserScanInit] Error! Close connection port failed.\n");
        DisplayError(HRESULT_FROM_WIN32(GetLastError()));
    }
    if (scanThreadCtxes) {
    
        for (i = 0;
         i < USER_SCAN_THREAD_COUNT;
         i ++ ) {

            if (scanThreadCtxes[i].Handle && !CloseHandle(scanThreadCtxes[i].Handle)) {

                fprintf(stderr, "[UserScanInit] Error! Close scan thread failed.\n");
                DisplayError(HRESULT_FROM_WIN32(GetLastError()));
            }
            DeleteCriticalSection(&(scanThreadCtxes[i].Lock));
        }
        HeapFree(GetProcessHeap(), 0, scanThreadCtxes);
    }
    if (hListenAbort && !CloseHandle(hListenAbort)) {
    
        fprintf(stderr, "[UserScanInit] Error! Close listen abort thread failed.\n");
        DisplayError(HRESULT_FROM_WIN32(GetLastError()));
    }
    if (hEvent && !CloseHandle(hEvent)) {
    
        fprintf(stderr, "[UserScanInit] Error! Close event handle failed.\n");
        DisplayError(HRESULT_FROM_WIN32(GetLastError()));
    }
    
    return hr;
}