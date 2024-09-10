EncodedJSValue JSC_HOST_CALL JSWebSocketConstructor::constructJSWebSocket(ExecState* exec)
{
    JSWebSocketConstructor* jsConstructor = static_cast<JSWebSocketConstructor*>(exec->callee());
    ScriptExecutionContext* context = jsConstructor->scriptExecutionContext();
    if (!context)
        return throwVMError(exec, createReferenceError(exec, "WebSocket constructor associated document is unavailable"));

    if (!exec->argumentCount())
        return throwVMError(exec, createSyntaxError(exec, "Not enough arguments"));

    String urlString = ustringToString(exec->argument(0).toString(exec)->value(exec));
    if (exec->hadException())
        return throwVMError(exec, createSyntaxError(exec, "wrong URL"));
    RefPtr<WebSocket> webSocket = WebSocket::create(context);
    ExceptionCode ec = 0;
    if (exec->argumentCount() < 2)
        webSocket->connect(urlString, ec);
    else {
        JSValue protocolsValue = exec->argument(1);
        if (isJSArray(protocolsValue)) {
            Vector<String> protocols;
            JSArray* protocolsArray = asArray(protocolsValue);
            for (unsigned i = 0; i < protocolsArray->length(); ++i) {
                String protocol = ustringToString(protocolsArray->getIndex(i).toString(exec)->value(exec));
                if (exec->hadException())
                    return JSValue::encode(JSValue());
                protocols.append(protocol);
            }
            webSocket->connect(urlString, protocols, ec);
        } else {
            String protocol = ustringToString(protocolsValue.toString(exec)->value(exec));
            if (exec->hadException())
                return JSValue::encode(JSValue());
            webSocket->connect(urlString, protocol, ec);
        }
    }
    setDOMException(exec, ec);
    return JSValue::encode(CREATE_DOM_WRAPPER(exec, jsConstructor->globalObject(), WebSocket, webSocket.get()));
}