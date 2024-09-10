JSValue JSInjectedScriptHost::getEventListeners(ExecState* exec)
{
    if (exec->argumentCount() < 1)
        return jsUndefined();
    JSValue value = exec->argument(0);
    if (!value.isObject() || value.isNull())
        return jsUndefined();
    Node* node = toNode(value);
    if (!node)
        return jsUndefined();
    // This can only happen for orphan DocumentType nodes.
    Document* document = node->document();
    if (!node->document())
        return jsUndefined();

    Vector<EventListenerInfo> listenersArray;
    impl()->getEventListenersImpl(node, listenersArray);

    JSObject* result = constructEmptyObject(exec);
    for (size_t i = 0; i < listenersArray.size(); ++i) {
        JSArray* listeners = getJSListenerFunctions(exec, document, listenersArray[i]);
        if (!listeners->length())
            continue;
        AtomicString eventType = listenersArray[i].eventType;
        result->putDirect(exec->globalData(), Identifier(exec, eventType.impl()), JSValue(listeners));
    }

    return result;
}