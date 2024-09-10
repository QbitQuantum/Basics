// There are a lot of characters in USCRIPT_COMMON that can be covered
// by fonts for scripts closely related to them. See
// http://unicode.org/cldr/utility/list-unicodeset.jsp?a=[:Script=Common:]
// FIXME: make this more efficient with a wider coverage
UScriptCode getScriptBasedOnUnicodeBlock(int ucs4)
{
    UBlockCode block = ublock_getCode(ucs4);
    switch (block) {
    case UBLOCK_CJK_SYMBOLS_AND_PUNCTUATION:
        return USCRIPT_HAN;
    case UBLOCK_HIRAGANA:
    case UBLOCK_KATAKANA:
        return USCRIPT_KATAKANA_OR_HIRAGANA;
    case UBLOCK_ARABIC:
        return USCRIPT_ARABIC;
    case UBLOCK_THAI:
        return USCRIPT_THAI;
    case UBLOCK_GREEK:
        return USCRIPT_GREEK;
    case UBLOCK_DEVANAGARI:
        // For Danda and Double Danda (U+0964, U+0965), use a Devanagari
        // font for now although they're used by other scripts as well.
        // Without a context, we can't do any better.
        return USCRIPT_DEVANAGARI;
    case UBLOCK_ARMENIAN:
        return USCRIPT_ARMENIAN;
    case UBLOCK_GEORGIAN:
        return USCRIPT_GEORGIAN;
    case UBLOCK_KANNADA:
        return USCRIPT_KANNADA;
    case UBLOCK_GOTHIC:
        return USCRIPT_GOTHIC;
    default:
        return USCRIPT_COMMON;
    }
}