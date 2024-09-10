static EncodedJSValue JSC_HOST_CALL functionGetPID(ExecState*)
{
    return JSValue::encode(jsNumber(getCurrentProcessID()));
}