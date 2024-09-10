static void countLeadingSpaces(const CString& utf8String, int32_t& pointerOffset, int32_t& characterOffset)
{
    pointerOffset = 0;
    characterOffset = 0;
    const char* stringData = utf8String.data();
    UChar32 character = 0;
    while (static_cast<unsigned>(pointerOffset) < utf8String.length()) {
        int32_t nextPointerOffset = pointerOffset;
        U8_NEXT(stringData, nextPointerOffset, static_cast<int32_t>(utf8String.length()), character);

        if (character < 0 || !u_isUWhiteSpace(character))
            return;

        pointerOffset = nextPointerOffset;
        characterOffset++;
    }
}