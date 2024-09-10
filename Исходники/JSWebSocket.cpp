EncodedJSValue JSC_HOST_CALL jsWebSocketPrototypeFunctionSend(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSWebSocket::s_info))
        return throwVMTypeError(exec);
    JSWebSocket* castedThis = static_cast<JSWebSocket*>(asObject(thisValue));
    WebSocket* imp = static_cast<WebSocket*>(castedThis->impl());
    if (exec->argumentCount() < 1)
        return JSValue::encode(jsUndefined());
    ExceptionCode ec = 0;
    const String& data(ustringToString(exec->argument(0).toString(exec)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());


    JSC::JSValue result = jsBoolean(imp->send(data, ec));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}