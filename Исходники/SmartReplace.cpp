// This is mostly a port of the code in WebCore/editing/SmartReplaceCF.cpp
// except we use ICU instead of CoreFoundation character classes.
static USet* getSmartSet(bool isPreviousCharacter)
{
    static USet* preSmartSet = nullptr;
    static USet* postSmartSet = nullptr;
    USet* smartSet = isPreviousCharacter ? preSmartSet : postSmartSet;
    if (!smartSet) {
        // Whitespace and newline (kCFCharacterSetWhitespaceAndNewline)
        UErrorCode ec = U_ZERO_ERROR;
        String whitespaceAndNewline = ASCIILiteral("[[:WSpace:] [\\u000A\\u000B\\u000C\\u000D\\u0085]]");
        smartSet = uset_openPattern(StringView(whitespaceAndNewline).upconvertedCharacters(), whitespaceAndNewline.length(), &ec);
        ASSERT(U_SUCCESS(ec));

        // CJK ranges
        // FIXME: Looks like all these ranges include one extra character past the end.
        uset_addRange(smartSet, 0x1100, 0x1100 + 256); // Hangul Jamo (0x1100 - 0x11FF)
        uset_addRange(smartSet, 0x2E80, 0x2E80 + 352); // CJK & Kangxi Radicals (0x2E80 - 0x2FDF)
        uset_addRange(smartSet, 0x2FF0, 0x2FF0 + 464); // Ideograph Descriptions, CJK Symbols, Hiragana, Katakana, Bopomofo, Hangul Compatibility Jamo, Kanbun, & Bopomofo Ext (0x2FF0 - 0x31BF)
        uset_addRange(smartSet, 0x3200, 0x3200 + 29392); // Enclosed CJK, CJK Ideographs (Uni Han & Ext A), & Yi (0x3200 - 0xA4CF)
        uset_addRange(smartSet, 0xAC00, 0xAC00 + 11183); // Hangul Syllables (0xAC00 - 0xD7AF)
        uset_addRange(smartSet, 0xF900, 0xF900 + 352); // CJK Compatibility Ideographs (0xF900 - 0xFA5F)
        uset_addRange(smartSet, 0xFE30, 0xFE30 + 32); // CJK Compatibility From (0xFE30 - 0xFE4F)
        uset_addRange(smartSet, 0xFF00, 0xFF00 + 240); // Half/Full Width Form (0xFF00 - 0xFFEF)
        uset_addRange(smartSet, 0x20000, 0x20000 + 0xA6D7); // CJK Ideograph Exntension B
        uset_addRange(smartSet, 0x2F800, 0x2F800 + 0x021E); // CJK Compatibility Ideographs (0x2F800 - 0x2FA1D)

        if (isPreviousCharacter) {
            // FIXME: Silly to convert this to a WTF::String just to loop through the characters.
            addAllCodePoints(smartSet, ASCIILiteral("([\"\'#$/-`{"));
            preSmartSet = smartSet;
        } else {
            // FIXME: Silly to convert this to a WTF::String just to loop through the characters.
            addAllCodePoints(smartSet, ASCIILiteral(")].,;:?\'!\"%*-/}"));

            // Punctuation (kCFCharacterSetPunctuation)
            UErrorCode ec = U_ZERO_ERROR;
            String punctuationClass = ASCIILiteral("[:P:]");
            USet* icuPunct = uset_openPattern(StringView(punctuationClass).upconvertedCharacters(), punctuationClass.length(), &ec);
            ASSERT(U_SUCCESS(ec));
            uset_addAll(smartSet, icuPunct);
            uset_close(icuPunct);

            postSmartSet = smartSet;
        }
    }
    return smartSet;
}