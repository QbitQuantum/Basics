static PassRefPtr<InspectorValue> jsToInspectorValue(ScriptState* scriptState, JSValue value)
{
    if (!value) {
        ASSERT_NOT_REACHED();
        return 0;
    }
    if (value.isNull() || value.isUndefined())
        return InspectorValue::null();
    if (value.isBoolean())
        return InspectorBasicValue::create(value.getBoolean());
    if (value.isNumber())
        return InspectorBasicValue::create(value.uncheckedGetNumber());
    if (value.isString()) {
        UString s = value.getString(scriptState);
        return InspectorString::create(String(s.characters(), s.length()));
    }
    if (value.isObject()) {
        if (isJSArray(&scriptState->globalData(), value)) {
            RefPtr<InspectorArray> inspectorArray = InspectorArray::create();
            JSArray* array = asArray(value);
            unsigned length = array->length();
            for (unsigned i = 0; i < length; i++) {
                JSValue element = array->getIndex(i);
                RefPtr<InspectorValue> elementValue = jsToInspectorValue(scriptState, element);
                if (!elementValue) {
                    ASSERT_NOT_REACHED();
                    elementValue = InspectorValue::null();
                }
                inspectorArray->pushValue(elementValue);
            }
            return inspectorArray;
        }
        RefPtr<InspectorObject> inspectorObject = InspectorObject::create();
        JSObject* object = value.getObject();
        PropertyNameArray propertyNames(scriptState);
        object->getOwnPropertyNames(scriptState, propertyNames);
        for (size_t i = 0; i < propertyNames.size(); i++) {
            const Identifier& name =  propertyNames[i];
            JSValue propertyValue = object->get(scriptState, name);
            RefPtr<InspectorValue> inspectorValue = jsToInspectorValue(scriptState, propertyValue);
            if (!inspectorValue) {
                ASSERT_NOT_REACHED();
                inspectorValue = InspectorValue::null();
            }
            inspectorObject->setValue(String(name.characters(), name.length()), inspectorValue);
        }
        return inspectorObject;
    }
    ASSERT_NOT_REACHED();
    return 0;
}