HRESULT CALLBACK AuthorizationCallback(
    __in const WS_OPERATION_CONTEXT* context, 
    __out BOOL* authorized, 
    __in_opt WS_ERROR* error)
{
    HRESULT hr = S_OK;
    const WS_STRING fixedUsername = WS_STRING_VALUE(L"usr1");
    WS_MESSAGE* message = NULL;
    WS_STRING usernameIdentity = {};
    *authorized = FALSE;
    
    hr = WsGetOperationContextProperty(context, WS_OPERATION_CONTEXT_PROPERTY_INPUT_MESSAGE, &message, sizeof(message), error);
    if (FAILED(hr))
    {
        return hr;
    }
    
    hr = WsGetMessageProperty(message, WS_MESSAGE_PROPERTY_USERNAME, &usernameIdentity, sizeof(usernameIdentity), error);
    if (FAILED(hr))
    {
        return hr;
    }
        
    *authorized = CompareWsString(&usernameIdentity, &fixedUsername);
    return S_OK;
}