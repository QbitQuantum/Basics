EncodedJSValue JSC_HOST_CALL regExpProtoFuncToString(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&RegExpObject::s_info)) {
        if (thisValue.inherits(&RegExpPrototype::s_info))
            return JSValue::encode(jsNontrivialString(exec, "//"));
        return throwVMTypeError(exec);
    }

    RegExpObject* thisObject = asRegExpObject(thisValue);

    StringRecursionChecker checker(exec, thisObject);
    if (EncodedJSValue earlyReturnValue = checker.earlyReturnValue())
        return earlyReturnValue;

    char postfix[5] = { '/', 0, 0, 0, 0 };
    int index = 1;
    if (thisObject->get(exec, exec->propertyNames().global).toBoolean(exec))
        postfix[index++] = 'g';
    if (thisObject->get(exec, exec->propertyNames().ignoreCase).toBoolean(exec))
        postfix[index++] = 'i';
    if (thisObject->get(exec, exec->propertyNames().multiline).toBoolean(exec))
        postfix[index] = 'm';
    UString source = thisObject->get(exec, exec->propertyNames().source).toString(exec);
    // If source is empty, use "/(?:)/" to avoid colliding with comment syntax
    return JSValue::encode(jsMakeNontrivialString(exec, "/", source.length() ? source : UString("(?:)"), postfix));
}