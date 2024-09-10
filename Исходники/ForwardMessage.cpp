// Messages are relayed from the sender thread to the receiver thread by this thread
DWORD WINAPI RelayThread(void* parameter)
{
    HRESULT hr;
    THREADINFO* threadInfo = (THREADINFO*)parameter;
    HANDLE relayReadyEvent = threadInfo->event;
    WS_ERROR* error = NULL;
    WS_CHANNEL* sendChannel = NULL;
    WS_CHANNEL* receiveChannel = NULL;
    WS_MESSAGE* sendMessage = NULL;
    WS_MESSAGE* receiveMessage = NULL;
    WS_LISTENER* listener = NULL;
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create a listener
    hr = WsCreateListener(WS_CHANNEL_TYPE_DUPLEX_SESSION, WS_TCP_CHANNEL_BINDING, NULL, 0, NULL, &listener, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Open listener using TCP duplex session
    hr = WsOpenListener(listener, &relayUrl, NULL, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create a TCP duplex session channel
    hr = WsCreateChannel(WS_CHANNEL_TYPE_DUPLEX_SESSION,
        WS_TCP_CHANNEL_BINDING, NULL, 0, NULL, &sendChannel, error);
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
    hr = WsOpenChannel(sendChannel, &address, NULL, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create a channel
    hr = WsCreateChannelForListener(listener, NULL, 0, &receiveChannel, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Notify that thread is ready
    threadInfo->hr = NOERROR;
    SetEvent(relayReadyEvent);
    
    // Accept a channel from the client
    hr = WsAcceptChannel(listener, receiveChannel, NULL, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsCreateMessageForChannel(
        receiveChannel,
        NULL, 
        0, 
        &receiveMessage, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsCreateMessageForChannel(
        sendChannel,
        NULL, 
        0, 
        &sendMessage, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Forward all messages
    for (;;)
    {
        // Receive start of message (headers)
        hr = WsReadMessageStart(receiveChannel, receiveMessage, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        if (hr == WS_S_END)
        {
            // No more messages on this channel
            break;
        }
    
        // Copy headers from received message
        hr = WsInitializeMessage(sendMessage, WS_DUPLICATE_MESSAGE, receiveMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Send message start (headers)
        hr = WsWriteMessageStart(sendChannel, sendMessage, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Get reader for receive message
        WS_XML_READER* xmlReader;
        hr = WsGetMessageProperty(receiveMessage, WS_MESSAGE_PROPERTY_BODY_READER, &xmlReader, sizeof(xmlReader), error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Get writer for send message
        WS_XML_WRITER* xmlWriter;
        hr = WsGetMessageProperty(sendMessage, WS_MESSAGE_PROPERTY_BODY_WRITER, &xmlWriter, sizeof(xmlWriter), error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Read and write contents of body
        for (;;)
        {
            const WS_XML_NODE* node;
            hr = WsGetReaderNode(xmlReader, &node, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
    
            if (node->nodeType == WS_XML_NODE_TYPE_END_ELEMENT)
            {
                break;
            }
    
            hr = WsCopyNode(xmlWriter, xmlReader, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        }
    
        // Receive message end
        hr = WsReadMessageEnd(receiveChannel, receiveMessage, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Send message end
        hr = WsWriteMessageEnd(sendChannel, sendMessage, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Reset message to enable reuse
        hr = WsResetMessage(sendMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Reset message to enable reuse
        hr = WsResetMessage(receiveMessage, error);
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
    fflush(
        stdout);
    
    if (sendChannel != NULL)
    {
        // Close the channel
        WsCloseChannel(sendChannel, NULL, error);
    }
    if (sendChannel != NULL)
    {
        WsFreeChannel(sendChannel);
    }
    
    if (receiveChannel != NULL)
    {
        // Close the channel
        WsCloseChannel(receiveChannel, NULL, error);
    }
    if (receiveChannel != NULL)
    {
        WsFreeChannel(receiveChannel);
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
    
    if (receiveMessage != NULL)
    {
        WsFreeMessage(receiveMessage);
    }
    if (sendMessage != NULL)
    {
        WsFreeMessage(sendMessage);
    }
    if (error != NULL)
    {
        WsFreeError(error);
    }
    if (FAILED(hr))
    {
        // Notify that thread is ready
        threadInfo->hr = hr;
        SetEvent(relayReadyEvent);
    }
    return 1;
}