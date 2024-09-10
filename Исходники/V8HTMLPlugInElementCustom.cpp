v8::Handle<v8::Value> npObjectIndexedGetter(uint32_t index, const v8::AccessorInfo& info)
{
    HTMLPlugInElement* imp = C::toNative(info.Holder());
    ScriptInstance scriptInstance = imp->getInstance();
    if (!scriptInstance)
        return v8Undefined();

    v8::Local<v8::Object> instance = v8::Local<v8::Object>::New(scriptInstance->instance());
    if (instance.IsEmpty())
        return v8Undefined();

    return npObjectGetIndexedProperty(instance, index, info);
}