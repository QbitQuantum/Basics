// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_SERVICE_HOST* host = NULL;
    WS_SERVICE_ENDPOINT typedHttpEndpoint = {};
    WS_SERVICE_ENDPOINT unTypedHttpEndpoint = {};
    const WS_SERVICE_ENDPOINT* serviceEndpoints[] = {&typedHttpEndpoint, &unTypedHttpEndpoint};
    WS_ERROR* error = NULL;
    WS_SERVICE_PROPERTY serviceProperties[1];
    WS_SERVICE_METADATA serviceMetadata = {};
    WS_SERVICE_ENDPOINT_PROPERTY serviceEndpointPropertiesTypedContract[3];
    WS_SERVICE_ENDPOINT_PROPERTY serviceEndpointPropertiesMetadata[2];
    WS_SERVICE_PROPERTY_CLOSE_CALLBACK closeCallbackProperty = {CloseChannelCallback};
    WS_SERVICE_ENDPOINT_METADATA endpointMetadata = {};
    WS_METADATA_EXCHANGE_TYPE metadataExchangeTypeMex = WS_METADATA_EXCHANGE_TYPE_MEX;
    WS_METADATA_EXCHANGE_TYPE metadataExchangeTypeHttpGet = WS_METADATA_EXCHANGE_TYPE_HTTP_GET;
    
    // Configure Port on the endpoint for Mex
    endpointMetadata.portName = (WS_XML_STRING*)&portName;
    endpointMetadata.bindingName = (WS_XML_STRING*)&bindingName;
    endpointMetadata.bindingNs = (WS_XML_STRING*)&bindingNs;                    
    
    serviceEndpointPropertiesTypedContract[0].id = WS_SERVICE_ENDPOINT_PROPERTY_CLOSE_CHANNEL_CALLBACK;
    serviceEndpointPropertiesTypedContract[0].value = &closeCallbackProperty;
    serviceEndpointPropertiesTypedContract[0].valueSize = sizeof(closeCallbackProperty);
    
    // Specifying Port on the endpoint.
    serviceEndpointPropertiesTypedContract[1].id = WS_SERVICE_ENDPOINT_PROPERTY_METADATA;
    serviceEndpointPropertiesTypedContract[1].value = &endpointMetadata;
    serviceEndpointPropertiesTypedContract[1].valueSize = sizeof(endpointMetadata);
    
    // Marking the endpoint to service WS-MetadataExchnage Requests
    serviceEndpointPropertiesTypedContract[2].id = WS_SERVICE_ENDPOINT_PROPERTY_METADATA_EXCHANGE_TYPE;
    serviceEndpointPropertiesTypedContract[2].value = &metadataExchangeTypeMex;
    serviceEndpointPropertiesTypedContract[2].valueSize = sizeof(metadataExchangeTypeMex);
    
    typedHttpEndpoint.address.url.chars = L"http://+:80/example"; // address given as uri
    typedHttpEndpoint.address.url.length = (ULONG)wcslen(typedHttpEndpoint.address.url.chars);
    typedHttpEndpoint.channelBinding = WS_HTTP_CHANNEL_BINDING; // channel binding for the endpoint
    typedHttpEndpoint.channelType = WS_CHANNEL_TYPE_REPLY; // the channel type
    typedHttpEndpoint.contract = (WS_SERVICE_CONTRACT*)&purchaseOrderContract;  // the contract
    typedHttpEndpoint.properties = serviceEndpointPropertiesTypedContract;
    typedHttpEndpoint.propertyCount = WsCountOf(serviceEndpointPropertiesTypedContract);
    
    serviceEndpointPropertiesMetadata[0].id = WS_SERVICE_ENDPOINT_PROPERTY_METADATA_EXCHANGE_TYPE;
    serviceEndpointPropertiesMetadata[0].value = &metadataExchangeTypeHttpGet;
    serviceEndpointPropertiesMetadata[0].valueSize = sizeof(metadataExchangeTypeHttpGet);
    
    serviceEndpointPropertiesMetadata[1].id = WS_SERVICE_ENDPOINT_PROPERTY_CLOSE_CHANNEL_CALLBACK;
    serviceEndpointPropertiesMetadata[1].value = &closeCallbackProperty;
    serviceEndpointPropertiesMetadata[1].valueSize = sizeof(closeCallbackProperty);
    
    unTypedHttpEndpoint.address.url.chars = L"http://+:80/metadata"; // address given as uri
    unTypedHttpEndpoint.address.url.length = (ULONG)wcslen(unTypedHttpEndpoint.address.url.chars);
    unTypedHttpEndpoint.channelBinding = WS_HTTP_CHANNEL_BINDING; // channel binding for the endpoint
    unTypedHttpEndpoint.channelType = WS_CHANNEL_TYPE_REPLY; // the channel type
    unTypedHttpEndpoint.contract = &messageContract;
    unTypedHttpEndpoint.properties = serviceEndpointPropertiesMetadata;
    unTypedHttpEndpoint.propertyCount = WsCountOf(serviceEndpointPropertiesMetadata);
    
    
    // Specifying WSDL document
    serviceMetadata.documentCount = WsCountOf(metadataDocuments);
    serviceMetadata.documents = (WS_SERVICE_METADATA_DOCUMENT**) metadataDocuments;
    
    // Initializing name of the service
    serviceMetadata.serviceName = (WS_XML_STRING*)&serviceName;
    
    // Note that this should concide be the target namespace of the wsdl document 
    serviceMetadata.serviceNs = (WS_XML_STRING*)&serviceNamespace;
    
    // Specifying metadata document
    serviceProperties[0].id = WS_SERVICE_PROPERTY_METADATA;
    serviceProperties[0].value =  &serviceMetadata;
    serviceProperties[0].valueSize = sizeof(serviceMetadata);
    
    
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
    hr = WsCreateServiceHost(serviceEndpoints, WsCountOf(serviceEndpoints), serviceProperties, WsCountOf(serviceProperties), &host, error);
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