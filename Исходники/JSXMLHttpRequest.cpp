JSValue JSC_HOST_CALL jsXMLHttpRequestPrototypeFunctionAbort(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSXMLHttpRequest::s_info))
        return throwError(exec, TypeError);
    JSXMLHttpRequest* castedThisObj = static_cast<JSXMLHttpRequest*>(asObject(thisValue));
    XMLHttpRequest* imp = static_cast<XMLHttpRequest*>(castedThisObj->impl());

    imp->abort();
    return jsUndefined();
}