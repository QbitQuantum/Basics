// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_LISTENER* listener = NULL;
    WS_CHANNEL* channel = NULL;
    WS_MESSAGE* requestMessage = NULL;
    WS_MESSAGE* replyMessage = NULL;
    WS_HEAP* heap = NULL;
    WCHAR* certSubjectName = NULL;
    PCCERT_CONTEXT certContext = NULL;
    
    BOOL requireClientCert = TRUE;
    WS_SECURITY_BINDING_PROPERTY requireClientCertProperty = {};
    requireClientCertProperty.id = WS_SECURITY_BINDING_PROPERTY_REQUIRE_SSL_CLIENT_CERT;
    requireClientCertProperty.value = &requireClientCert;
    requireClientCertProperty.valueSize = sizeof(requireClientCert);
    
    // declare and initialize an SSL transport security binding
    WS_SSL_TRANSPORT_SECURITY_BINDING sslBinding = {}; // zero out the struct
    sslBinding.binding.bindingType = WS_SSL_TRANSPORT_SECURITY_BINDING_TYPE; // set the binding type
    sslBinding.binding.properties = &requireClientCertProperty;
    sslBinding.binding.propertyCount = 1;
    // NOTE: At the server, the SSL certificate for the listen URI must be
    // registered with http.sys using a tool such as httpcfg.exe.
    
    // declare and initialize the array of all security bindings
    WS_SECURITY_BINDING* securityBindings[1] = { &sslBinding.binding };
    
    // declare and initialize the security description
    WS_SECURITY_DESCRIPTION securityDescription = {}; // zero out the struct
    securityDescription.securityBindings = securityBindings;
    securityDescription.securityBindingCount = WsCountOf(securityBindings);
    
    static const WS_STRING uri = WS_STRING_VALUE(L"https://localhost:8443/example");
    
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
        WS_CHANNEL_TYPE_REPLY, 
        WS_HTTP_CHANNEL_BINDING, 
        NULL, 0, 
        &securityDescription, 
        &listener, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Open listener 
    hr = WsOpenListener(listener, &uri, NULL, error);
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
    
    
    // Receive requests / send replies
    for (int i = 0; i < 300; i++)
    {
        // Accept a request from the client
        hr = WsAcceptChannel(listener, channel, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Set up the descriptions of the expected messages. We expect either a purchase order
        // or a request for order status.
        const WS_MESSAGE_DESCRIPTION* requestMessageDescriptions[] =
        {
            &PurchaseOrder_wsdl.messages.PurchaseOrder,   // contains a _PurchaseOrderType in the body
            &PurchaseOrder_wsdl.messages.GetOrderStatus,  // contains a GetOrderStatus in the body
        };
        
        // Receive the message and deserialize the element of the body into the appropriate
        // structure, based on the message descriptions.  The value of the body will be
        // allocated in the specified WS_HEAP, and are valid until WsResetHeap is called.
        void* requestBodyPointer;
        ULONG indexOfMatchedMessageDescription;
        
        hr = WsReceiveMessage(channel, requestMessage, requestMessageDescriptions, WsCountOf(requestMessageDescriptions),
            WS_RECEIVE_REQUIRED_MESSAGE, WS_READ_REQUIRED_POINTER, heap,
            &requestBodyPointer, sizeof(requestBodyPointer), &indexOfMatchedMessageDescription, NULL, error);
        
        // Validate the client certificate.
        if (SUCCEEDED(hr))
        {
            // Another way to do client cert validation is to use
            // WS_MESSAGE_PROPERTY_TRANSPORT_SECURITY_WINDOWS_TOKEN here, assuming http.sys
            // is configured to map the cert into a windows token and was able to map the
            // cert to a user account.
            WS_BYTES encodedCert = {};
            hr = WsGetMessageProperty(
                requestMessage,
                WS_MESSAGE_PROPERTY_ENCODED_CERT,
                &encodedCert,
                sizeof(encodedCert),
                error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            _Analysis_assume_(encodedCert.bytes != NULL);
            certContext = CertCreateCertificateContext(
                X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                encodedCert.bytes,
                encodedCert.length);
        
            if (certContext == NULL)
            {
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Exit;
            }
        
            ULONG subjectNameLength = CertNameToStr(
                certContext->dwCertEncodingType,
                &certContext->pCertInfo->Subject,
                CERT_SIMPLE_NAME_STR,
                NULL,
                0);
        
            if (subjectNameLength == 0)
            {
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Exit;
            }
        
            certSubjectName = new WCHAR[subjectNameLength];
            if (certSubjectName == NULL)
            {
                hr = E_OUTOFMEMORY;
                goto Exit;
            }
        
            subjectNameLength = CertNameToStr(
                certContext->dwCertEncodingType,
                &certContext->pCertInfo->Subject,
                CERT_SIMPLE_NAME_STR,
                certSubjectName,
                subjectNameLength);
        
            if (subjectNameLength == 0)
            {
                hr = HRESULT_FROM_WIN32(GetLastError());
                goto Exit;
            }
        
            static const WCHAR expectedCertName[] = L"client.com";
        
            wprintf(L"Expected client cert name: %s\n", expectedCertName);
            wprintf(L"Received client cert name: %s\n", certSubjectName);
        
            if (CompareString(
                    LOCALE_INVARIANT,
                    NORM_IGNORECASE,
                    expectedCertName,
                    (int)::wcslen(expectedCertName),
                    certSubjectName,
                    (int)::wcslen(certSubjectName)) != CSTR_EQUAL)
            {
                hr = WS_E_SECURITY_VERIFICATION_FAILURE;
                goto Exit;
            }
        }
        
        // Process the request, and generate the reply
        const WS_MESSAGE_DESCRIPTION* replyMessageDescription = NULL;
        const void* replyBodyPointer = NULL;
        ULONG replyBodySize = 0;
        _OrderConfirmationType orderConfirmation;
        _GetOrderStatusResponseType getOrderStatusResponse;
        
        if (SUCCEEDED(hr))
        {
            // Get the message description that matched
            const WS_MESSAGE_DESCRIPTION* requestMessageDescription = requestMessageDescriptions[indexOfMatchedMessageDescription];
        
            if (requestMessageDescription == &PurchaseOrder_wsdl.messages.PurchaseOrder)
            {
                // The message was a purchase order.  Get the pointer to the deserialized value.
                _PurchaseOrderType* purchaseOrder = (_PurchaseOrderType*)requestBodyPointer;
        
                // Print out purchase order contents
                wprintf(L"%d, %s\n",
                    purchaseOrder->quantity,
                    purchaseOrder->productName);
        
                // Initialize order confirmation data
                orderConfirmation.expectedShipDate = L"1/1/2006";
                orderConfirmation.orderID = 123;
        
                // Setup up reply message
                replyMessageDescription = &PurchaseOrder_wsdl.messages.OrderConfirmation;
                replyBodyPointer = &orderConfirmation;
                replyBodySize = sizeof(orderConfirmation);
            }
            else if (requestMessageDescription == &PurchaseOrder_wsdl.messages.GetOrderStatus)
            {
                // The message was a order status request.  Get the pointer to the deserialized value.
                _GetOrderStatusType* getOrderStatus = (_GetOrderStatusType*)requestBodyPointer;
        
                // Generate a fault if we don't recognize the order ID
                if (getOrderStatus->orderID != 123)
                {
                    // Fill out details about the fault
                    _OrderNotFoundFaultType orderNotFound;
                    orderNotFound.orderID = getOrderStatus->orderID;
                    
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
                    
                    // Set fault detail information in the error object
                    hr = WsSetFaultErrorDetail(
                        error,
                        &orderNotFoundFaultTypeDescription,
                        WS_WRITE_REQUIRED_VALUE,
                        &orderNotFound,
                        sizeof(orderNotFound));
                    
                    if (FAILED(hr))
                    {
                        goto Exit;
                    }
                    
                    // Add an error string to the error object.  This string will
                    // be included in the fault that is sent.
                    static const WS_STRING errorMessage = WS_STRING_VALUE(L"Invalid order ID");
                    hr = WsAddErrorString(error, &errorMessage);
                    
                    if (FAILED(hr))
                    {
                        goto Exit;
                    }
        
                    // Use a failure code to indicate that a fault should be sent
                    hr = E_FAIL;
                }
                else
                {
                    // Initialize the order status response
                    getOrderStatusResponse.orderID = getOrderStatus->orderID;
                    getOrderStatusResponse.status = L"Pending";
        
                    // Specify which message description to use for reply
                    replyMessageDescription = &PurchaseOrder_wsdl.messages.GetOrderStatusResponse;
                    replyBodyPointer = &getOrderStatusResponse;
                    replyBodySize = sizeof(getOrderStatusResponse);
                }
            }
        }
        
        // If there was an error receiving the message
        if (FAILED(hr))
        {
            // Send a fault in the body of the reply message.  The information
            // accumulated in the error object is used to populate the fault.
            // The error code is not transmitted but instead is used to
            // generate an error string if no error strings are present in the
            // error object.
            hr = WsSendFaultMessageForError(
                channel,
                replyMessage,
                error,
                hr,
                WS_FULL_FAULT_DISCLOSURE,
                requestMessage,
                NULL,
                error);
        
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Reset the error so it can be used again
            hr = WsResetError(error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Reset the reply message so it can be used again
            hr = WsResetMessage(replyMessage, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        }
        else
        {
            // Send a reply message
            hr = WsSendReplyMessage(
                channel,
                replyMessage,
                replyMessageDescription,
                WS_WRITE_REQUIRED_VALUE,
                replyBodyPointer,
                replyBodySize,
                requestMessage,
                NULL,
                error);
        
            if (FAILED(hr))
            {
                goto Exit;
            }
        
            // Reset the reply message so it can be used again
            hr = WsResetMessage(replyMessage, error);
            if (FAILED(hr))
            {
                goto Exit;
            }
        }
        
        // Reset the request message so it can be used again
        hr = WsResetMessage(requestMessage, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        // Reset the heap, which will free any allocations made on it
        hr = WsResetHeap(heap, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Close the request
        hr = WsCloseChannel(channel, NULL, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Prepare channel for reuse
        hr = WsResetChannel(channel, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        // Delete the certificate name string if needed.
        if (certSubjectName != NULL)
        {
            delete[] certSubjectName;
            certSubjectName = NULL;
        }
    
        // Delete cert context if needed
        if (certContext != NULL)
        {
            CertFreeCertificateContext(certContext);
            certContext = NULL;
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
    if (requestMessage != NULL)
    {
        WsFreeMessage(requestMessage);
    }
    if (replyMessage != NULL)
    {
        WsFreeMessage(replyMessage);
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
    
    
    if (error != NULL)
    {
        WsFreeError(error);
    }
    if (heap != NULL)
    {
        WsFreeHeap(heap);
    }
    
    if (certSubjectName != NULL)
    {
        delete[] certSubjectName;
    }
    
    if (certContext != NULL)
    {
        CertFreeCertificateContext(certContext);
    }
    
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}