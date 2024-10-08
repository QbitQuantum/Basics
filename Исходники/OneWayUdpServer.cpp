// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_MESSAGE* message = NULL;
    WS_CHANNEL* channel = NULL;
    WS_LISTENER* listener = NULL;
    WS_HEAP* heap = NULL;
    
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
    
    // Create a listener
    hr = WsCreateListener(
        WS_CHANNEL_TYPE_DUPLEX, 
        WS_UDP_CHANNEL_BINDING, 
        NULL, 
        0, 
        NULL, 
        &listener, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Open listener at address
    WS_STRING uri;
    uri.chars = L"soap.udp://localhost:809";
    uri.length = (ULONG)wcslen(uri.chars);
    
    hr = WsOpenListener(
        listener, 
        &uri, 
        NULL, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsCreateChannelForListener(
        listener, 
        NULL, 
        0, 
        &channel, 
        error);
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
    
    
    for (ULONG i = 0; i < 5; i++)
    {
        // Accept a channel from the client
        hr = WsAcceptChannel(listener, channel, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Set up the descriptions of the expected messages.  In this case, we only expect purchase orders.
        const WS_MESSAGE_DESCRIPTION* messageDescriptions[] = {&PurchaseOrder_wsdl.messages.PurchaseOrder};
        
        // Receive the message and deserialize the element of the body into a _PurchaseOrderType structure.
        // The values of the fields of the _PurchaseOrderType structure are allocated in the specified
        // WS_HEAP, and are valid until WsResetHeap is called.
        _PurchaseOrderType purchaseOrder;
        hr = WsReceiveMessage(channel, message, 
            messageDescriptions, WsCountOf(messageDescriptions),
            WS_RECEIVE_OPTIONAL_MESSAGE, WS_READ_REQUIRED_VALUE, heap, 
            &purchaseOrder, sizeof(purchaseOrder), NULL, NULL, error);
        
        if (hr == WS_S_END)
        {
            // No more messages on channel
            break;
        }
        
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Print out purchase order contents
        wprintf(L"%ld, %s\n", 
            purchaseOrder.quantity, 
            purchaseOrder.productName);
        
        // Reset the message so it can be used again
        hr = WsResetMessage(
                message,
                error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Reset the heap, which will free any allocations made on it
        hr = WsResetHeap(
                heap,
                error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        hr = WsCloseChannel(channel, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        hr = WsResetChannel(channel, error);
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
    if (channel != NULL)
    {
        WsFreeChannel(channel);
    }
    
    if (listener != NULL)
    {
        // Close the listener if it was opened
        WsCloseListener(listener, NULL, error);
    }
    if (listener != NULL)
    {
        WsFreeListener(listener);
    }
    
    if (message != NULL)
    {
        WsFreeMessage(message);
    }
    
    
    if (error != NULL)
    {
        WsFreeError(error);
    }
    if (heap != NULL)
    {
        WsFreeHeap(heap);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}