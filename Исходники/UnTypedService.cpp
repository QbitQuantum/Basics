HRESULT CALLBACK ProcessMessage(
    __in const WS_OPERATION_CONTEXT* context, 
    __in_opt const WS_ASYNC_CONTEXT* asyncContext, 
    __in_opt WS_ERROR* error)
{
    UNREFERENCED_PARAMETER(asyncContext);

    WS_CHANNEL* channel = NULL;
    HRESULT hr = NOERROR;
    WS_HEAP* heap = NULL;
    WS_MESSAGE* replyMessage = NULL;

    hr = WsGetOperationContextProperty(
        context, 
        WS_OPERATION_CONTEXT_PROPERTY_HEAP, 
        &heap, 
        sizeof(heap), 
        error);
if (FAILED(hr))
{
    goto Exit;
}
    
    WS_MESSAGE* requestMessage = NULL;
    hr = WsGetOperationContextProperty(
        context, 
        WS_OPERATION_CONTEXT_PROPERTY_INPUT_MESSAGE, 
        &requestMessage, 
        sizeof(requestMessage), 
        error);
if (FAILED(hr))
{
    goto Exit;
}
    
    hr = WsGetOperationContextProperty(
    context, 
    WS_OPERATION_CONTEXT_PROPERTY_CHANNEL, 
    &channel, 
    sizeof(channel), 
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
    
    // Get action value
    WS_XML_STRING receivedAction;
    hr = WsGetHeader(
        requestMessage, 
        WS_ACTION_HEADER, 
        WS_XML_STRING_TYPE,
        WS_READ_REQUIRED_VALUE, 
        NULL, 
        &receivedAction, 
        sizeof(receivedAction), 
        error);
if (FAILED(hr))
{
    goto Exit;
}

    // Make sure action is what we expect
    if (WsXmlStringEquals(
        &receivedAction, 
        PurchaseOrder_wsdl.messages.PurchaseOrder.action, 
        error) != S_OK)
    {
        hr = WS_E_ENDPOINT_ACTION_NOT_SUPPORTED;
        goto Exit;
    }

    // Read purchase order
    _PurchaseOrderType purchaseOrder;
    hr = WsReadBody(
        requestMessage, 
        &PurchaseOrder_wsdl.globalElements.PurchaseOrderType, 
        WS_READ_REQUIRED_VALUE, 
        heap, &purchaseOrder, 
        sizeof(purchaseOrder), 
        error);
if (FAILED(hr))
{
    goto Exit;
}
    
    // Read end of message
    hr = WsReadMessageEnd(
        channel, 
        requestMessage, 
        NULL, 
        error);
if (FAILED(hr))
{
    goto Exit;
}
    
    // Print out purchase order contents
    wprintf(L"%ld, %s\n", 
        purchaseOrder.quantity, 
        purchaseOrder.productName);
    
    // Initialize order confirmation data
    _OrderConfirmationType orderConfirmation;
    orderConfirmation.expectedShipDate = L"1/1/2006";
    orderConfirmation.orderID = 123;

    // Send a reply message
    hr = WsSendReplyMessage(
        channel, 
        replyMessage, 
        &PurchaseOrder_wsdl.messages.OrderConfirmation, 
        WS_WRITE_REQUIRED_VALUE,
        &orderConfirmation, 
        sizeof(orderConfirmation),
        requestMessage, 
        NULL, 
        error);
if (FAILED(hr))
{
    goto Exit;
}
    
    hr = WS_S_END;
    
Exit:
    fflush(stdout);
    if (replyMessage != NULL)
    {
        WsFreeMessage(
            replyMessage);
    }
    return hr;    
}