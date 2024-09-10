//////////////////////////////////////////////////////////////////////////////
// AsyncOperationComplete - Called when the GetFile operation is complete
//////////////////////////////////////////////////////////////////////////////
HRESULT STDMETHODCALLTYPE CGetFileAsyncCallback::AsyncOperationComplete(
    IWSDAsyncResult* pAsyncResult,
    IUnknown* pAsyncState)
{
    UNREFERENCED_PARAMETER(pAsyncState);

    GET_FILE_RESPONSE* pResponse = NULL;
    HRESULT hr = S_OK;

    //
    // When the GetFile operation completes, we enter this callback.  It's
    // then our responsibility to call EndGetFile to actually retrieve
    // the results.
    //
    _cwprintf(L"Asynchronous GetFile operation completed.\r\n");
    hr = m_pFileServiceSecureProxy->EndGetFile( pAsyncResult, &pResponse );

    // Call into our helper method to save the attachment to disk
    if( S_OK == hr && NULL != pResponse )
    {
        hr = ReceiveBinary( pResponse->Attachment, m_szFile );
    }
    else
    {
        _cwprintf(L"    GetFile operation failed or returned NULL response: ");
        print_result( hr );
    }

    // cleanup
    if( NULL != pResponse )
    {
        WSDFreeLinkedMemory( pResponse );
        pResponse = NULL;
    }

    return hr;
}