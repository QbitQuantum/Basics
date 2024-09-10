HRESULT CALLBACK PurchaseOrderImpl(
    __in const WS_OPERATION_CONTEXT* context,
    __in int quantity,
    __in_opt __nullterminated WCHAR* productName,
    __out unsigned int* orderID,
    __out_opt __deref __nullterminated WCHAR** expectedShipDate,
    __in_opt const WS_ASYNC_CONTEXT* asyncContext,
    __in_opt WS_ERROR* error)
{
    UNREFERENCED_PARAMETER(asyncContext);

    WS_HEAP* heap = NULL;
    HRESULT hr = S_OK;
    
    wprintf(L"%ld, %s\n", quantity, productName);
    fflush(stdout);
    
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
    
    hr = WsAlloc(
        heap, 
        sizeof(ExpectedShipDate), 
        (void**)expectedShipDate, 
        error);
if (FAILED(hr))
{
    goto Exit;
}
    
    hr = StringCbCopyW(
        *expectedShipDate, 
        sizeof(ExpectedShipDate), 
        ExpectedShipDate);
if (FAILED(hr))
{
    goto Exit;
}
    
    *orderID = 123;
    
Exit:
    return hr;
}