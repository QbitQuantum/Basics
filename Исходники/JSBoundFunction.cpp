EncodedJSValue JSC_HOST_CALL boundFunctionCall(ExecState* exec)
{
    JSBoundFunction* boundFunction = jsCast<JSBoundFunction*>(exec->jsCallee());

    JSArray* boundArgs = boundFunction->boundArgs();

    MarkedArgumentBuffer args;
    if (boundArgs) {
        for (unsigned i = 0; i < boundArgs->length(); ++i)
            args.append(boundArgs->getIndexQuickly(i));
    }
    for (unsigned i = 0; i < exec->argumentCount(); ++i)
        args.append(exec->uncheckedArgument(i));

    JSObject* targetFunction = boundFunction->targetFunction();
    CallData callData;
    CallType callType = getCallData(targetFunction, callData);
    ASSERT(callType != CallType::None);
    return JSValue::encode(call(exec, targetFunction, callType, callData, boundFunction->boundThis(), args));
}