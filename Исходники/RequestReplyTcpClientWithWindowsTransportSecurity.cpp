// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_CHANNEL* channel = NULL;
    WS_MESSAGE* requestMessage = NULL;
    WS_MESSAGE* replyMessage = NULL;
    WS_HEAP* heap = NULL;
    
    // declare and initialize a windows credential
    WS_DEFAULT_WINDOWS_INTEGRATED_AUTH_CREDENTIAL windowsCredential = {}; // zero out the struct
    windowsCredential.credential.credentialType = WS_DEFAULT_WINDOWS_INTEGRATED_AUTH_CREDENTIAL_TYPE; // set the credential type
    
    ULONG impersonation = SecurityImpersonation;
    // declare and initialize properties to change the impersonation level from the default
    WS_SECURITY_BINDING_PROPERTY tcpSspiBindingProperties[1] =
    {
        { WS_SECURITY_BINDING_PROPERTY_ALLOWED_IMPERSONATION_LEVEL, &impersonation, sizeof(impersonation) }
    };
    
    // declare and initialize an Windows SSPI transport security binding
    WS_TCP_SSPI_TRANSPORT_SECURITY_BINDING tcpSspiBinding = {}; // zero out the struct
    tcpSspiBinding.binding.bindingType = WS_TCP_SSPI_TRANSPORT_SECURITY_BINDING_TYPE; // set the binding type
    tcpSspiBinding.binding.properties = tcpSspiBindingProperties;
    tcpSspiBinding.binding.propertyCount = WsCountOf(tcpSspiBindingProperties);
    tcpSspiBinding.clientCredential = &windowsCredential.credential;
    
    // declare and initialize the array of all security bindings
    WS_SECURITY_BINDING* securityBindings[1] = { &tcpSspiBinding.binding };
    
    // declare and initialize the security description
    WS_SECURITY_DESCRIPTION securityDescription = {}; // zero out the struct
    securityDescription.securityBindings = securityBindings;
    securityDescription.securityBindingCount = WsCountOf(securityBindings);
    
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
    
    
    // Create a TCP duplex session channel
    hr = WsCreateChannel(
        WS_CHANNEL_TYPE_DUPLEX_SESSION, 
        WS_TCP_CHANNEL_BINDING, 
        NULL, 
        0, 
        &securityDescription, 
        &channel, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Initialize address of service
    WS_ENDPOINT_ADDRESS address;
    address.url.chars = L"net.tcp://localhost/example";
    address.url.length = (ULONG)::wcslen(address.url.chars);
    address.headers = NULL;
    address.extensions = NULL;
    address.identity = NULL;
    
    // Open channel to address
    hr = WsOpenChannel(
        channel, 
        &address, 
        NULL, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsCreateMessageForChannel(
        channel,
        NULL, 
        0, 
        &requestMessage, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsCreateMessageForChannel(
        channel,
        NULL, 
        0, 
        &replyMessage, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Send some request-replies
    for (int i = 0; i < 100; i++)
    {
        // Initialize purchase order
        _PurchaseOrderType purchaseOrder;
        purchaseOrder.quantity = 100;
        purchaseOrder.productName = L"Pencil";
        
        _OrderConfirmationType orderConfirmation;
        
        // Send purchase order, get order confirmation
        hr = WsRequestReply(
            channel,
            requestMessage, 
            &PurchaseOrder_wsdl.messages.PurchaseOrder, 
            WS_WRITE_REQUIRED_VALUE,
            &purchaseOrder,
            sizeof(purchaseOrder),
            replyMessage, 
            &PurchaseOrder_wsdl.messages.OrderConfirmation, 
            WS_READ_REQUIRED_VALUE, 
            heap, 
            &orderConfirmation, 
            sizeof(orderConfirmation), 
            NULL, 
            error);
        
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Print out confirmation contents
        wprintf(L"Expected ship date for order %lu is %s\n",
            orderConfirmation.orderID,
            orderConfirmation.expectedShipDate);
        
        // Reset the message so it can be used again
        hr = WsResetMessage(requestMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Reset the message so it can be used again
        hr = WsResetMessage(replyMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Initialize request for order status
        _GetOrderStatusType getOrderStatus;
        getOrderStatus.orderID = orderConfirmation.orderID;
        
        _GetOrderStatusResponseType getOrderStatusResponse;
        
        // Send order status request, get order status reply
        hr = WsRequestReply(
            channel,
            requestMessage, 
            &PurchaseOrder_wsdl.messages.GetOrderStatus, 
            WS_WRITE_REQUIRED_VALUE,
            &getOrderStatus,
            sizeof(getOrderStatus),
            replyMessage, 
            &PurchaseOrder_wsdl.messages.GetOrderStatusResponse, 
            WS_READ_REQUIRED_VALUE, 
            heap, 
            &getOrderStatusResponse, 
            sizeof(getOrderStatusResponse), 
            NULL, 
            error);
        
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Print out order status
        wprintf(L"Order status for order %lu is: %s\n",
            getOrderStatusResponse.orderID,
            getOrderStatusResponse.status);
        
        // Reset the message so it can be used again
        hr = WsResetMessage(requestMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Reset the message so it can be used again
        hr = WsResetMessage(replyMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Make same request, but this time with an invalid order ID
        getOrderStatus.orderID = 321;
        hr = WsRequestReply(
            channel,
            requestMessage, 
            &PurchaseOrder_wsdl.messages.GetOrderStatus, 
            WS_WRITE_REQUIRED_VALUE,
            &getOrderStatus,
            sizeof(getOrderStatus),
            replyMessage, 
            &PurchaseOrder_wsdl.messages.GetOrderStatusResponse, 
            WS_READ_REQUIRED_VALUE, 
            heap, 
            &getOrderStatusResponse, 
            sizeof(getOrderStatusResponse), 
            NULL, 
            error);
        
        // Check to see if we got a fault
        if (hr == WS_E_ENDPOINT_FAULT_RECEIVED)
        {
            // Print the strings in the error object
            PrintError(hr, error);
        
            static const WS_XML_STRING _faultDetailName = WS_XML_STRING_VALUE("OrderNotFound");
            static const WS_XML_STRING _faultDetailNs = WS_XML_STRING_VALUE("http://example.com");
            static const WS_XML_STRING _faultAction = WS_XML_STRING_VALUE("http://example.com/fault");
            static const WS_ELEMENT_DESCRIPTION _faultElementDescription = 
            { 
                (WS_XML_STRING*)&_faultDetailName, 
                (WS_XML_STRING*)&_faultDetailNs, 
                WS_UINT32_TYPE, 
                NULL 
            };
            static const WS_FAULT_DETAIL_DESCRIPTION orderNotFoundFaultTypeDescription = 
            { 
                (WS_XML_STRING*)&_faultAction, 
                (WS_ELEMENT_DESCRIPTION*)&_faultElementDescription 
            };
        
            // Try to get the fault detail from the error object
            _OrderNotFoundFaultType* orderNotFound;
            hr = WsGetFaultErrorDetail(
                error,
                &orderNotFoundFaultTypeDescription,
                WS_READ_OPTIONAL_POINTER,
                heap,
                &orderNotFound,
                sizeof(orderNotFound));
                
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            if (orderNotFound != NULL)
            {
                // Print out the fault detail
                wprintf(L"Order %lu was not found\n", orderNotFound->orderID);
            }
        
            // Reset error so it can be used again
            hr = WsResetError(error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        }
        
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Reset the message so it can be used again
        hr = WsResetMessage(requestMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Reset the message so it can be used again
        hr = WsResetMessage(replyMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        wprintf(L"\n");
        
        // Reset the heap
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
    
    if (channel != NULL)
    {
        // Close the channel
        WsCloseChannel(channel, NULL, error);
    }
    if (requestMessage != NULL)
    {
        WsFreeMessage(requestMessage);
    }
    if (replyMessage != NULL)
    {
        WsFreeMessage(replyMessage);
    }
    if (channel != NULL)
    {
        WsFreeChannel(channel);
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