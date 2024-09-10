JSValue JSC_HOST_CALL jsInspectorFrontendHostPrototypeFunctionCloseWindow(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInspectorFrontendHost::s_info))
        return throwError(exec, TypeError);
    JSInspectorFrontendHost* castedThisObj = static_cast<JSInspectorFrontendHost*>(asObject(thisValue));
    InspectorFrontendHost* imp = static_cast<InspectorFrontendHost*>(castedThisObj->impl());

    imp->closeWindow();
    return jsUndefined();
}