// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_CHANNEL* channel = NULL;
    WS_MESSAGE* message = NULL;
    static const WS_STRING serviceUrl = WS_STRING_VALUE(L"soap.udp://localhost:809");
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create a UDP duplex channel
    hr = WsCreateChannel(
        WS_CHANNEL_TYPE_DUPLEX, 
        WS_UDP_CHANNEL_BINDING, 
        NULL, 
        0, 
        NULL, 
        &channel, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    
    // Initialize address of service
    WS_ENDPOINT_ADDRESS address;
    address.url = serviceUrl;
    address.headers = NULL;
    address.extensions = NULL;
    address.identity = NULL;
    
    // Open channel to address
    hr = WsOpenChannel(channel, &address, NULL, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsCreateMessageForChannel(
        channel,
        NULL, 
        0, 
        &message, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Send some messages
    for (int i = 0; i < 5; i++)
    {
        // Initialize body data
        _PurchaseOrderType purchaseOrder;
        purchaseOrder.quantity = 100;
        purchaseOrder.productName = L"Pencil";
    
        // Send a message
        hr = WsSendMessage(
            channel, 
            message, 
            &PurchaseOrder_wsdl.messages.PurchaseOrder, 
            WS_WRITE_REQUIRED_VALUE,
            &purchaseOrder, 
            sizeof(purchaseOrder),
            NULL, 
            error);
    
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Reset message so it can be used again
        hr = WsResetMessage(message, error);
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
    
    if (channel != NULL)
    {
        // Close the channel
        WsCloseChannel(channel, NULL, error);
    }
    
    if (message != NULL)
    {
        WsFreeMessage(message);
    }
    if (channel != NULL)
    {
        WsFreeChannel(channel);
    }
    
    
    if (error != NULL)
    {
        WsFreeError(error);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}