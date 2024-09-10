void ComplexTextController::normalizeSpacesAndMirrorChars(const UChar* source, bool rtl, UChar* destination, int length)
{
    int position = 0;
    bool error = false;
    // Iterate characters in source and mirror character if needed.
    while (position < length) {
        UChar32 character;
        int nextPosition = position;
        U16_NEXT(source, nextPosition, length, character);
        if (Font::treatAsSpace(character))
            character = ' ';
        else if (Font::treatAsZeroWidthSpace(character))
            character = zeroWidthSpace;
        else if (rtl)
            character = u_charMirror(character);
        U16_APPEND(destination, position, length, character, error);
        ASSERT(!error);
        position = nextPosition;
    }
}