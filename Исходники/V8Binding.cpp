v8::Local<v8::String> v8ExternalString(const String& string)
{
    StringImpl* stringImpl = string.impl();
    if (!stringImpl || !stringImpl->length())
        return v8::String::Empty();

    if (!stringImplCacheEnabled)
        return makeExternalString(string);

    StringCache& stringCache = getStringCache();
    v8::String* cachedV8String = stringCache.get(stringImpl);
    if (cachedV8String)
    {
        v8::Persistent<v8::String> handle(cachedV8String);
        if (!handle.IsNearDeath() && !handle.IsEmpty())
            return v8::Local<v8::String>::New(handle);
    }

    v8::Local<v8::String> newString = makeExternalString(string);
    if (newString.IsEmpty())
        return newString;

    v8::Persistent<v8::String> wrapper = v8::Persistent<v8::String>::New(newString);
    if (wrapper.IsEmpty())
        return newString;

    stringImpl->ref();
    wrapper.MakeWeak(stringImpl, cachedStringCallback);
    stringCache.set(stringImpl, *wrapper);

    return newString;
}