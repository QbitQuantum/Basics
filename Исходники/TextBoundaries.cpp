unsigned endOfFirstWordBoundaryContext(StringView text)
{
    unsigned length = text.length();
    for (unsigned i = 0; i < length; ) {
        unsigned first = i;
        UChar32 ch;
        U16_NEXT(text, i, length, ch);
        if (!requiresContextForWordBoundary(ch))
            return first;
    }
    return length;
}