// Main entry point
int __cdecl wmain()
{

    HRESULT hr = S_OK;
    WS_SERVICE_HOST* host = NULL;
    WS_SERVICE_ENDPOINT serviceEndpoint = {};
    const WS_SERVICE_ENDPOINT* serviceEndpoints[1];
    WS_ERROR* error = NULL;
    WS_SERVICE_ENDPOINT_PROPERTY serviceProperties[1];
    const ULONG maxConcurrency = 100;
    serviceEndpoints[0] = &serviceEndpoint;
    serviceProperties[0].id = WS_SERVICE_ENDPOINT_PROPERTY_MAX_CONCURRENCY;
    serviceProperties[0].value = (void*)&maxConcurrency;
    serviceProperties[0].valueSize = sizeof(maxConcurrency);

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

    // Initialize service endpoint
    serviceEndpoint.address.url.chars = L"net.tcp://+/example"; // address given as uri
    serviceEndpoint.address.url.length = (ULONG)wcslen(serviceEndpoint.address.url.chars);
    serviceEndpoint.channelBinding = WS_TCP_CHANNEL_BINDING; // channel binding for the endpoint
    serviceEndpoint.channelType = WS_CHANNEL_TYPE_DUPLEX_SESSION; // the channel type
    serviceEndpoint.contract = &blockServiceContract;  // the contract
    serviceEndpoint.properties = serviceProperties;
    serviceEndpoint.propertyCount = WsCountOf(serviceProperties);
    // Create an error object for storing rich error information
    hr = WsCreateError(
             NULL,
             0,
             &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    // Creating a service host
    hr = WsCreateServiceHost(
             serviceEndpoints,
             1,
             NULL,
             0,
             &host,
             error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    // WsOpenServiceHost to start the listeners in the service host
    hr = WsOpenServiceHost(
             host,
             NULL,
             error);
    if (FAILED(hr))
    {
        goto Exit;
    }


    WaitForSingleObject(closeServer, INFINITE);

    // Aborts the service host so that the blocked method can complete.
    WsAbortServiceHost(host, NULL);
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