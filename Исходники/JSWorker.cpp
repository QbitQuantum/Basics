EncodedJSValue JSC_HOST_CALL jsWorkerPrototypeFunctionTerminate(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSWorker::s_info))
        return throwVMTypeError(exec);
    JSWorker* castedThis = static_cast<JSWorker*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, &JSWorker::s_info);
    Worker* imp = static_cast<Worker*>(castedThis->impl());

    imp->terminate();
    return JSValue::encode(jsUndefined());
}