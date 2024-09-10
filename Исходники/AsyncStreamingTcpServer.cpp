HRESULT CALLBACK Receive8(
    __in HRESULT hr, 
    __in WS_CALLBACK_MODEL callbackModel, 
    __in void* state, 
    __inout WS_ASYNC_OPERATION* next, 
    __in_opt const WS_ASYNC_CONTEXT* asyncContext, 
    __in_opt WS_ERROR* error)
{
    UNREFERENCED_PARAMETER(callbackModel);
    UNREFERENCED_PARAMETER(asyncContext);

    RECEIVE_STATE* receiveState = (RECEIVE_STATE*) state;
    if (FAILED(hr))
    {
        return hr;
    }

    // Read purchase order into heap, if there are any more to read.
    _PurchaseOrderType* purchaseOrder;
    hr = WsReadElement(receiveState->reader, &PurchaseOrder_wsdl.globalElements.PurchaseOrderType, 
        WS_READ_OPTIONAL_POINTER, receiveState->heap, &purchaseOrder, sizeof(purchaseOrder), error);
    if (FAILED(hr))
    {
        return hr;
    }

    // If NULL indicates no more purchase orders
    if (purchaseOrder == NULL)
    {
        next->function = Receive9;
        return S_OK;
    }

    wprintf(L"%ld, %s\n", 
        purchaseOrder->quantity, 
        purchaseOrder->productName);
    fflush(stdout);

    // Free purchase order
    hr = WsResetHeap(receiveState->heap, error);
    if (FAILED(hr))
    {
        return hr;
    }

    next->function = Receive6;
    return S_OK;
}