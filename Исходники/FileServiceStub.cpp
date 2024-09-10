// <StubDefinitions>
HRESULT __stdcall
Stub_GetFileList
(   IUnknown* server
,   IWSDServiceMessaging* service
,   WSD_EVENT* event
)
{
    HRESULT hr = S_OK;
    IFileService* pServer = NULL;

    RESPONSEBODY_FileService_GetFileList result;
    ::ZeroMemory(&result,sizeof(result));

    hr = server->QueryInterface( __uuidof(IFileService), (void**)&pServer );
    if( S_OK == hr )
    {
        hr =
        pServer->GetFileList
        (   &result.parameters
        );

        pServer->Release();
        pServer = NULL;
    }
    if (SUCCEEDED(hr))
    {
        hr = service->SendResponse(&result,event->Operation,event->MessageParameters);
    }
    if (FAILED(hr))
    {
        hr = service->FaultRequest(&event->Soap->Header,event->MessageParameters, NULL);
    }

    // Clean up memory from outparams
    if (NULL != result.parameters)
    {
        WSDFreeLinkedMemory( (void*) (result.parameters) );
    }

    return hr;
}