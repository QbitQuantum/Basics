TiValue TiString::replaceCharacter(TiExcState* exec, UChar character, const UString& replacement)
{
    if (!isRope()) {
        size_t matchPosition = m_value.find(character);
        if (matchPosition == notFound)
            return TiValue(this);
        return jsString(exec, m_value.substringSharingImpl(0, matchPosition), replacement, m_value.substringSharingImpl(matchPosition + 1));
    }

    RopeIterator end;
    
    // Count total fibers and find matching string.
    size_t fiberCount = 0;
    StringImpl* matchString = 0;
    size_t matchPosition = notFound;
    for (RopeIterator it(m_fibers.data(), m_fiberCount); it != end; ++it) {
        ++fiberCount;
        if (matchString)
            continue;

        StringImpl* string = *it;
        matchPosition = string->find(character);
        if (matchPosition == notFound)
            continue;
        matchString = string;
    }

    if (!matchString)
        return this;

    RopeBuilder builder(replacement.length() ? fiberCount + 2 : fiberCount + 1);
    if (UNLIKELY(builder.isOutOfMemory()))
        return throwOutOfMemoryError(exec);

    for (RopeIterator it(m_fibers.data(), m_fiberCount); it != end; ++it) {
        StringImpl* string = *it;
        if (string != matchString) {
            builder.append(UString(string));
            continue;
        }

        builder.append(UString(string).substringSharingImpl(0, matchPosition));
        if (replacement.length())
            builder.append(replacement);
        builder.append(UString(string).substringSharingImpl(matchPosition + 1));
        matchString = 0;
    }

    TiGlobalData* globalData = &exec->globalData();
    return TiValue(new (globalData) TiString(globalData, builder.release()));
}