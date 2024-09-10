// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_SERVICE_HOST* host = NULL;
    WS_SERVICE_ENDPOINT* serviceEndpoint = NULL;
    const  WS_SERVICE_ENDPOINT* serviceEndpoints[1];
    WS_ERROR* error = NULL;
    WS_HEAP* heap = NULL;
    const WS_STRING url = WS_STRING_VALUE(L"https://localhost:8443/example");
    
    
    WS_SERVICE_PROPERTY_CLOSE_CALLBACK closeCallbackProperty = {CloseChannelCallback};
    WS_SERVICE_ENDPOINT_PROPERTY serviceProperties[1];
    serviceProperties[0].id = WS_SERVICE_ENDPOINT_PROPERTY_CLOSE_CHANNEL_CALLBACK;
    serviceProperties[0].value = &closeCallbackProperty;
    serviceProperties[0].valueSize = sizeof(closeCallbackProperty);
    
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
    
    hr = DefaultBinding_ICalculator_CreateServiceEndpoint(
        NULL,
        &url,
        (DefaultBinding_ICalculatorFunctionTable*)&calculatorFunctions,
        NULL,
        serviceProperties,
        WsCountOf(serviceProperties),
        heap,
        &serviceEndpoint,
        error);
    
    if (FAILED(hr))
    {
        goto Exit;
    }
    serviceEndpoints[0] = serviceEndpoint;
    
    hr = WsCreateServiceHost(serviceEndpoints, 1, NULL, 0, &host, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // WsOpenServiceHost to start the listeners in the service host 
    hr = WsOpenServiceHost(host, NULL, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create Event object for closing the server
    closeServer = CreateEvent(
        NULL, 
        TRUE, 
        FALSE, 
        NULL);
    if (closeServer == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Exit;
    }   
    WaitForSingleObject(closeServer, INFINITE);
    // Close the service host
    hr = WsCloseServiceHost(host, NULL, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
Exit:
    if (FAILED(hr))
    {
        // Print out the error
        PrintError(hr, error);
    }
    if (host != NULL)
    {
        WsFreeServiceHost(host);
    }
    
    
    if (heap != NULL)
    {
        WsFreeHeap(heap);
    }
    if (error != NULL)
    {
        WsFreeError(error);
    }
    if (closeServer != NULL)
    {
        CloseHandle(closeServer);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}