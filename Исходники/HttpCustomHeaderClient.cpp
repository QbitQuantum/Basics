// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_SERVICE_PROXY* serviceProxy = NULL;
    WS_HEAP* heap = NULL;
    WS_ENDPOINT_ADDRESS address = {0};
    static const WS_STRING serviceUrl = WS_STRING_VALUE(L"http://localhost/example");
    address.url = serviceUrl;
    WS_CALL_PROPERTY callProperties[2];
    _OrderSession orderSession;
    orderSession.sessionId = L"ExampleSession";
    WS_PROXY_MESSAGE_CALLBACK_CONTEXT inputMessageContext = {0};
    WS_PROXY_MESSAGE_CALLBACK_CONTEXT outputMessageContext = {0};
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    // Create a heap to store deserialized data
    hr = WsCreateHeap(
        /*maxSize*/ 2048, 
        /*trimSize*/ 512, 
        NULL, 
        0, 
        &heap, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsCreateServiceProxy(
        WS_CHANNEL_TYPE_REQUEST, 
        WS_HTTP_CHANNEL_BINDING, 
        NULL, 
        NULL,
        0,
        NULL, 
        0, 
        &serviceProxy, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    
    // Open channel to address
    hr = WsOpenServiceProxy(
        serviceProxy, 
        &address, 
        NULL, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    inputMessageContext.callback = AddSessionHeader;
    inputMessageContext.state = &orderSession;
    outputMessageContext.callback = RetrieveSessionHeader;
    outputMessageContext.state = &orderSession;
    
    callProperties[0].id = WS_CALL_PROPERTY_SEND_MESSAGE_CONTEXT;
    callProperties[0].value = &inputMessageContext;
    callProperties[0].valueSize = sizeof(inputMessageContext);
    
    callProperties[1].id = WS_CALL_PROPERTY_RECEIVE_MESSAGE_CONTEXT;
    callProperties[1].value = &outputMessageContext;
    callProperties[1].valueSize = sizeof(outputMessageContext);
    
    for (int i = 0; i < 100; i++)
    {
        static const WCHAR* productName = L"Pencil";
        WCHAR* expectedShipDate = {0};
        unsigned int orderID;
    
        hr = PurchaseOrderBinding_Order(
            serviceProxy, 
            100, 
            (WCHAR*)productName, 
            &orderID, 
            &expectedShipDate, 
            heap, 
            callProperties, 
            WsCountOf(callProperties), 
            NULL, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Print out confirmation contents
        wprintf(L"Expected ship date for order %lu is %s\n",
            orderID,
            expectedShipDate);
    
        hr = WsResetHeap(heap, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
    
        
    }
    
Exit:
    if (FAILED(hr))
    {
        // Print out the error
        PrintError(hr, error);
    }
    if (serviceProxy != NULL)
    {
        WsCloseServiceProxy(serviceProxy, NULL, NULL);
        WsFreeServiceProxy(serviceProxy);
    }
    
    
    if (heap != NULL)
    {
        WsFreeHeap(heap);
    }
    if (error != NULL)
    {
        WsFreeError(error);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}