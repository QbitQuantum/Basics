// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_CHANNEL* channel = NULL;
    WS_MESSAGE* message = NULL;
    HANDLE receiverThreadHandle = NULL;
    static const WS_STRING serviceUrl = WS_STRING_VALUE(L"soap.udp://[FF02::C]:809");
    static const WS_STRING toUrl = WS_STRING_VALUE(L"http://localhost/request");
    ULONG addressFamily = AF_INET6;
    ULONG retVal = 0;
    IP_ADAPTER_ADDRESSES* adapterAddresses = NULL;
    
    // To get list of adapters GetAdaptersAddresses is called twice - first to get size of the list
    // and second to get the actual list. As the number of adapters may change between these two calls
    // to GetAdaptersAddresses, we retry up to 4 times.
    for (ULONG i = 0; i < 4; i++)
    {
        // Free memory if it was not big enough
        if (adapterAddresses != NULL)
        {
            HeapFree(GetProcessHeap(), 0, adapterAddresses);
            adapterAddresses = NULL;
        }
        
        // First see how much space is needed for adapter addresses
        ULONG adapterBufferSize = 0;
        retVal = GetAdaptersAddresses(addressFamily, 0, NULL, NULL, &adapterBufferSize);
        if (retVal != ERROR_BUFFER_OVERFLOW)
        {
            hr = HRESULT_FROM_WIN32(retVal);
            goto Exit;
        }
            
        // Allocate space for information about adapters
        adapterAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, adapterBufferSize);
        if (adapterAddresses == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto Exit;
        }
    
        // Get list of adapters
        retVal = GetAdaptersAddresses(
            AF_INET6,
            0, NULL, adapterAddresses, &adapterBufferSize);
        
        if (retVal != ERROR_BUFFER_OVERFLOW)
        {
            break;
        }
        // number of adapter have changed between calls to GetAdaptersAddresses, retry.
    }
    
    if (retVal != 0)
    {
        hr = HRESULT_FROM_WIN32(retVal);
        goto Exit;
    }
    
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    WS_IP_VERSION ipVersion = WS_IP_VERSION_6;
    WS_CHANNEL_PROPERTY ipVersionProperty;
    ipVersionProperty.id = WS_CHANNEL_PROPERTY_IP_VERSION;
    ipVersionProperty.value = &ipVersion;
    ipVersionProperty.valueSize = sizeof(ipVersion);
    // Create a UDP duplex channel for IPv6 addressing
    hr = WsCreateChannel(
        WS_CHANNEL_TYPE_DUPLEX, 
        WS_UDP_CHANNEL_BINDING, 
        &ipVersionProperty, 
        1, 
        NULL, 
        &channel, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    
    // Initialize address to the multicast address to send to
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
    
    // Generate a unique message ID that will be used for all messages
    WS_UNIQUE_ID messageID;
    ZeroMemory(&messageID, sizeof(messageID));
    if (UuidCreate(&messageID.guid) != RPC_S_OK)
    {
        hr = E_FAIL;
        goto Exit;
    }
    
    // Create a thread that will receive messages
    THREAD_INFO receiverThreadInfo;
    receiverThreadInfo.channel = channel;
    receiverThreadHandle = CreateThread(NULL, 0, ReceiverThread, &receiverThreadInfo, 0, NULL);
    if (receiverThreadHandle == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
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
    
    // Initialize body data
    _PurchaseOrderType purchaseOrder;
    purchaseOrder.quantity = 100;
    purchaseOrder.productName = L"Pencil";
    
    // Send the same message twice
    for (int i = 0; i < 2; i++)
    {
        // For each adapter
        for (IP_ADAPTER_ADDRESSES* adapterAddress = adapterAddresses; 
             adapterAddress != NULL; adapterAddress = adapterAddress->Next)
        {
            // Only send on the loopback adapter
            if (adapterAddress->IfType != IF_TYPE_SOFTWARE_LOOPBACK)
            {
                continue;
            }
        
            // Get multicast interface index
            ULONG interfaceIndex = adapterAddress->Ipv6IfIndex;
        
            // Set property on channel which controls which multicast adapater address
            // is used when sending to a multicast address.
            hr = WsSetChannelProperty(channel, WS_CHANNEL_PROPERTY_MULTICAST_INTERFACE, 
                &interfaceIndex, sizeof(interfaceIndex), error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Initialize message headers
            hr = WsInitializeMessage(message, WS_BLANK_MESSAGE, NULL, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Add the action header
            hr = WsSetHeader(
                message, 
                WS_ACTION_HEADER, 
                WS_XML_STRING_TYPE,
                WS_WRITE_REQUIRED_VALUE,
                PurchaseOrder_wsdl.messages.PurchaseOrder.action, 
                sizeof(*PurchaseOrder_wsdl.messages.PurchaseOrder.action), 
                error);
        
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Add the message ID
            hr = WsSetHeader(
                message, 
                WS_MESSAGE_ID_HEADER, 
                WS_UNIQUE_ID_TYPE,
                WS_WRITE_REQUIRED_VALUE,
                &messageID, 
                sizeof(messageID), 
                error);
        
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Set the reply to address to be a anonymous URI (modeled as a 0 length URI), which 
            // indicates to the receiver that they should reply using the source IP address.
            WS_ENDPOINT_ADDRESS replyTo;
            ZeroMemory(&replyTo, sizeof(replyTo));
        
            hr = WsSetHeader(
                message, 
                WS_REPLY_TO_HEADER, 
                WS_ENDPOINT_ADDRESS_TYPE,
                WS_WRITE_REQUIRED_VALUE,
                &replyTo, 
                sizeof(replyTo),
                error);
        
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Address the message to differ from the destination.  When the message
            // is addressed manually, the endpoint address specified at open time 
            // will only be used to determine the destination of the message (not
            // to determine the value of the To header).  In this case, the message is
            // addressed to a stable address.
            WS_ENDPOINT_ADDRESS to;
            ZeroMemory(&to, sizeof(to));
            to.url = toUrl;
        
            hr = WsAddressMessage(message, &to, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Write the message headers
            hr = WsWriteMessageStart(channel, message, NULL, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Write the body data
            hr = WsWriteBody(
                message, 
                &PurchaseOrder_wsdl.globalElements.PurchaseOrderType, 
                WS_WRITE_REQUIRED_VALUE,
                &purchaseOrder, 
                sizeof(purchaseOrder),
                error);
        
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Send the entire message
            hr = WsWriteMessageEnd(channel, message, NULL, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Reset message so it can used again
            hr = WsResetMessage(message, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        }
    }
    
    // Wait for replies to be processed by the receiver thread
    Sleep(1000);
    
Exit:
    if (FAILED(hr))
    {
        // Print out the error
        PrintError(hr, error);
    }
    
    if (receiverThreadHandle != NULL)
    {
        // Abort the channel. This will cause the next receive to fail.
        WsAbortChannel(channel, error);
    
        // Wait for the receive thread to exit, and clean up the handle.
        WaitForSingleObject(receiverThreadHandle, INFINITE);
        CloseHandle(receiverThreadHandle);
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
    if (adapterAddresses != NULL)
    {
        HeapFree(GetProcessHeap(), 0, adapterAddresses);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}