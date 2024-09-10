Boolean CLocaleBuilder::IsValidVariantSubtag(
    /* [in] */ const String& subTag)
{
    // The BCP-47 spec states that :
    // - Subtags can be between [5, 8] alphanumeric chars in length.
    // - Subtags that start with a number are allowed to be 4 chars in length.
    if (subTag.GetLength() >= 5 && subTag.GetLength() <= 8) {
        if (CLocale::IsAsciiAlphaNum(subTag)) {
            return TRUE;
        }
    }
    else if (subTag.GetLength() == 4) {
        Char32 firstChar = subTag.GetChar(0);
        if ((firstChar >= '0' && firstChar <= '9') && CLocale::IsAsciiAlphaNum(subTag)) {
            return TRUE;
        }
    }

    return FALSE;
}