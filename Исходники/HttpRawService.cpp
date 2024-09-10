// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_SERVICE_HOST* host = NULL;
    WS_SERVICE_ENDPOINT serviceEndpoint = {};
    const WS_SERVICE_ENDPOINT* serviceEndpoints[1];
    WS_ERROR* error = NULL;
    
    serviceEndpoints[0] = &serviceEndpoint;
    
    // Specify that the HTTP channel should surface non-SOAP messages
    WS_CHANNEL_PROPERTY channelPropertyArray[2];
    WS_ENCODING rawEncoding = WS_ENCODING_RAW;
    channelPropertyArray[0].id = WS_CHANNEL_PROPERTY_ENCODING;
    channelPropertyArray[0].value = &rawEncoding;
    channelPropertyArray[0].valueSize = sizeof(rawEncoding);
    
    // Specify how HTTP requests and responses are mapped to the message object
    channelPropertyArray[1].id = WS_CHANNEL_PROPERTY_HTTP_MESSAGE_MAPPING;
    channelPropertyArray[1].value = const_cast<WS_HTTP_MESSAGE_MAPPING*>(&messageMapping);
    channelPropertyArray[1].valueSize = sizeof(messageMapping);
    
    WS_SERVICE_ENDPOINT_PROPERTY serviceEndpointPropertyArray[1]; 
    WS_SERVICE_PROPERTY_CLOSE_CALLBACK closeCallbackProperty = {CloseChannelCallback};
    serviceEndpointPropertyArray[0].id = WS_SERVICE_ENDPOINT_PROPERTY_CLOSE_CHANNEL_CALLBACK;
    serviceEndpointPropertyArray[0].value = &closeCallbackProperty;
    serviceEndpointPropertyArray[0].valueSize = sizeof(closeCallbackProperty);
    
    
    // Initialize service endpoint
    serviceEndpoint.address.url.chars = L"http://+:80/example"; // address given as uri
    serviceEndpoint.address.url.length = (ULONG)wcslen(serviceEndpoint.address.url.chars);
    serviceEndpoint.channelBinding = WS_HTTP_CHANNEL_BINDING; // channel binding for the endpoint
    serviceEndpoint.channelType = WS_CHANNEL_TYPE_REPLY; // the channel type
    serviceEndpoint.contract = &messageContract;  // the contract
    serviceEndpoint.properties = serviceEndpointPropertyArray;
    serviceEndpoint.propertyCount = WsCountOf(serviceEndpointPropertyArray);
    serviceEndpoint.channelProperties.properties = channelPropertyArray; // Channel properties
    serviceEndpoint.channelProperties.propertyCount = WsCountOf(channelPropertyArray); // Channel property Count
    serviceEndpoint.channelProperties.properties = channelPropertyArray;
    serviceEndpoint.channelProperties.propertyCount = WsCountOf(channelPropertyArray);
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
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