    static HRESULT CALLBACK Clear(
        __in const WS_OPERATION_CONTEXT* context,
        __in const WS_ASYNC_CONTEXT* asyncContext,
        __in_opt WS_ERROR* error)
    {
        UNREFERENCED_PARAMETER(asyncContext);

        HRESULT hr = S_OK;
        SessionfulCalculator* calculator = NULL;
        hr = WsGetOperationContextProperty(
                 context,
                 WS_OPERATION_CONTEXT_PROPERTY_CHANNEL_USER_STATE,
                 &calculator,
                 sizeof(SessionfulCalculator*),
                 error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        hr = calculator->Clear();
Exit:
        return hr;
    }