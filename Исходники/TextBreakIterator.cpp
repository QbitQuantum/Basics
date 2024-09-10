unsigned numGraphemeClusters(StringView string)
{
    unsigned stringLength = string.length();
    
    if (!stringLength)
        return 0;

    // The only Latin-1 Extended Grapheme Cluster is CRLF.
    if (string.is8Bit()) {
        auto* characters = string.characters8();
        unsigned numCRLF = 0;
        for (unsigned i = 1; i < stringLength; ++i)
            numCRLF += characters[i - 1] == '\r' && characters[i] == '\n';
        return stringLength - numCRLF;
    }

    NonSharedCharacterBreakIterator iterator { string };
    if (!iterator) {
        ASSERT_NOT_REACHED();
        return stringLength;
    }

    unsigned numGraphemeClusters = 0;
    while (ubrk_next(iterator) != UBRK_DONE)
        ++numGraphemeClusters;
    return numGraphemeClusters;
}