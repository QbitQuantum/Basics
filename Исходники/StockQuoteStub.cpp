// <StubDefinitions>
HRESULT __stdcall
Stub_GetLastTradePrice
(   IUnknown* server
,   IWSDServiceMessaging* service
,   WSD_EVENT* event
)
{
    HRESULT hr = S_OK;
    IStockQuote* pServer = NULL;

    REQUESTBODY_StockQuotePortType_GetLastTradePrice* p = reinterpret_cast<REQUESTBODY_StockQuotePortType_GetLastTradePrice*>(event->Soap->Body);
    RESPONSEBODY_StockQuotePortType_GetLastTradePrice result;
    ::ZeroMemory(&result,sizeof(result));

    hr = server->QueryInterface( __uuidof(IStockQuote), (void**)&pServer );
    if( S_OK == hr )
    {
        hr =
        pServer->GetLastTradePrice
        (   p->body
        ,   &result.body
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
    if (NULL != result.body)
    {
        WSDFreeLinkedMemory( (void*) (result.body) );
    }

    return hr;
}