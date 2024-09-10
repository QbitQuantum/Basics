JSValue JSCommandLineAPIHost::getEventListeners(ExecState& state)
{
    if (state.argumentCount() < 1)
        return jsUndefined();

    JSValue value = state.uncheckedArgument(0);
    if (!value.isObject() || value.isNull())
        return jsUndefined();

    Node* node = JSNode::toWrapped(value);
    if (!node)
        return jsUndefined();

    Vector<EventListenerInfo> listenersArray;
    wrapped().getEventListenersImpl(node, listenersArray);

    JSObject* result = constructEmptyObject(&state);
    for (size_t i = 0; i < listenersArray.size(); ++i) {
        JSArray* listeners = getJSListenerFunctions(state, &node->document(), listenersArray[i]);
        if (!listeners->length())
            continue;
        AtomicString eventType = listenersArray[i].eventType;
        result->putDirect(state.vm(), Identifier::fromString(&state, eventType.impl()), JSValue(listeners));
    }

    return result;
}