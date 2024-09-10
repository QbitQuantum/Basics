JSC::JSValue jsStringWithCache(JSC::ExecState* exec, const String& s)
{
    JSC::VM& vm = exec->vm();
    StringImpl* stringImpl = s.impl();
    if (!stringImpl || !stringImpl->length())
        return jsEmptyString(&vm);

    if (stringImpl->length() == 1) {
        UChar singleCharacter = (*stringImpl)[0u];
        if (singleCharacter <= JSC::maxSingleCharacterString)
            return vm.smallStrings.singleCharacterString(static_cast<unsigned char>(singleCharacter));
    }

    auto addResult = vm.stringCache.add(stringImpl, nullptr);
    if (addResult.isNewEntry)
        addResult.iterator->value = JSC::jsString(&vm, String(stringImpl));
    return JSC::JSValue(addResult.iterator->value.get());
}