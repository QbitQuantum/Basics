// <ProxyFunctionImplementations>
HRESULT STDMETHODCALLTYPE
CFileServiceProxy::GetFileList
(   /* [out] */ GET_FILE_LIST_RESPONSE** parametersOut
)
{
    HRESULT hr = S_OK;

    // Initialize Output Pointers
    if( NULL != parametersOut )
    {
        *parametersOut = NULL;
    }

    // Validate Response Parameters
    if( NULL == parametersOut )
    {
        hr = E_POINTER;
        return hr;
    }

    if( NULL == m_genericProxy )
    {
        hr = E_ABORT;
        return hr;
    }

    IWSDEndpointProxy* ep = NULL;
    hr = m_genericProxy->GetEndpointProxy(&ep);
    if( FAILED(hr) || NULL == ep )
    {
        hr = E_ABORT;
        return hr;
    }

    WSD_SYNCHRONOUS_RESPONSE_CONTEXT context;
    ::ZeroMemory(&context, sizeof(context));
    context.eventHandle = ::CreateEvent(NULL, FALSE, FALSE, NULL);
    if (NULL == context.eventHandle)
    {
        DWORD dw = ::GetLastError();
        hr = HRESULT_FROM_WIN32(dw);
        ep->Release();
        return hr;
    }
    hr = 
        ep->SendTwoWayRequest
        (   NULL
        ,   &Operations_FileService[0]
        ,   &context
        );

    if (SUCCEEDED(hr))
    {
        if ( WAIT_FAILED == ::WaitForSingleObject(context.eventHandle, INFINITE) )
        {
             DWORD dw = ::GetLastError();
             hr = HRESULT_FROM_WIN32(dw);
        }
    }

    ::CloseHandle(context.eventHandle);
    context.eventHandle = NULL;

    if (SUCCEEDED(hr))
    {
        if (SUCCEEDED(context.hr))
        {
            if( NULL != context.results )
            {
                RESPONSEBODY_FileService_GetFileList* response = reinterpret_cast<RESPONSEBODY_FileService_GetFileList*>(context.results);

                WSDDetachLinkedMemory( (void*) response->parameters );
                *parametersOut = response->parameters;

                WSDFreeLinkedMemory( context.results );
                context.results = NULL;
            }
            else
            {
                hr = E_FAIL;
            }
        }
        else
        {
            hr = context.hr;
            if( context.results )
            {
                ep->ProcessFault( (const WSD_SOAP_FAULT*)context.results );
            }
        }
    }

    if ( NULL != context.messageParameters )
    {
        context.messageParameters->Release();
        context.messageParameters = NULL;
    }

    ep->Release();
    return hr;
}