AtomicString AtomicString::convertToASCIILowercase() const
{
    StringImpl* impl = this->impl();
    if (UNLIKELY(!impl))
        return AtomicString();

    // Convert short strings without allocating a new StringImpl, since
    // there's a good chance these strings are already in the atomic
    // string table and so no memory allocation will be required.
    unsigned length;
    const unsigned localBufferSize = 100;
    if (impl->is8Bit() && (length = impl->length()) <= localBufferSize) {
        const LChar* characters = impl->characters8();
        unsigned failingIndex;
        for (unsigned i = 0; i < length; ++i) {
            if (UNLIKELY(isASCIIUpper(characters[i]))) {
                failingIndex = i;
                goto SlowPath;
            }
        }
        return *this;
SlowPath:
        LChar localBuffer[localBufferSize];
        for (unsigned i = 0; i < failingIndex; ++i)
            localBuffer[i] = characters[i];
        for (unsigned i = failingIndex; i < length; ++i)
            localBuffer[i] = toASCIILower(characters[i]);
        return AtomicString(localBuffer, length);
    }

    RefPtr<StringImpl> convertedString = impl->convertToASCIILowercase();
    if (LIKELY(convertedString == impl))
        return *this;

    AtomicString result;
    result.m_string = addSlowCase(*convertedString);
    return result;
}