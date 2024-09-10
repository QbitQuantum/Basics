static RefPtr<IDBKey> createIDBKeyFromValue(ExecState* exec, JSValue value, Vector<JSArray*>& stack)
{
    if (value.isNumber() && !std::isnan(value.toNumber(exec)))
        return IDBKey::createNumber(value.toNumber(exec));
    if (value.isString())
        return IDBKey::createString(value.toString(exec)->value(exec));
    if (value.inherits(DateInstance::info()) && !std::isnan(valueToDate(exec, value)))
        return IDBKey::createDate(valueToDate(exec, value));
    if (value.isObject()) {
        JSObject* object = asObject(value);
        if (isJSArray(object) || object->inherits(JSArray::info())) {
            JSArray* array = asArray(object);
            size_t length = array->length();

            if (stack.contains(array))
                return nullptr;
            if (stack.size() >= maximumDepth)
                return nullptr;
            stack.append(array);

            Vector<RefPtr<IDBKey>> subkeys;
            for (size_t i = 0; i < length; i++) {
                JSValue item = array->getIndex(exec, i);
                RefPtr<IDBKey> subkey = createIDBKeyFromValue(exec, item, stack);
                if (!subkey)
                    subkeys.append(IDBKey::createInvalid());
                else
                    subkeys.append(subkey);
            }

            stack.removeLast();
            return IDBKey::createArray(subkeys);
        }
    }
    return nullptr;
}