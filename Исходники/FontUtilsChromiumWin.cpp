// FIXME:
//  - Handle 'Inherited', 'Common' and 'Unknown'
//    (see http://www.unicode.org/reports/tr24/#Usage_Model )
//    For 'Inherited' and 'Common', perhaps we need to
//    accept another parameter indicating the previous family
//    and just return it.
//  - All the characters (or characters up to the point a single
//    font can cover) need to be taken into account
const UChar* getFallbackFamily(const UChar* characters,
                               int length,
                               FontDescription::GenericFamilyType generic,
                               UChar32* charChecked,
                               UScriptCode* scriptChecked)
{
    ASSERT(characters && characters[0] && length > 0);
    UScriptCode script = USCRIPT_COMMON;

    // Sometimes characters common to script (e.g. space) is at
    // the beginning of a string so that we need to skip them
    // to get a font required to render the string.
    int i = 0;
    UChar32 ucs4 = 0;
    while (i < length && script == USCRIPT_COMMON || script == USCRIPT_INVALID_CODE) {
        U16_NEXT(characters, i, length, ucs4);
        UErrorCode err = U_ZERO_ERROR;
        script = uscript_getScript(ucs4, &err);
        // silently ignore the error
    }

    // For the full-width ASCII characters (U+FF00 - U+FF5E), use the font for
    // Han (determined in a locale-dependent way above). Full-width ASCII
    // characters are rather widely used in Japanese and Chinese documents and
    // they're fully covered by Chinese, Japanese and Korean fonts.
    if (0xFF00 < ucs4 && ucs4 < 0xFF5F)
        script = USCRIPT_HAN;

    // There are a lot of characters in USCRIPT_COMMON that can be covered
    // by fonts for scripts closely related to them. See
    // http://unicode.org/cldr/utility/list-unicodeset.jsp?a=[:Script=Common:]
    // FIXME: make this more efficient with a wider coverage
    if (script == USCRIPT_COMMON || script == USCRIPT_INHERITED) {
        UBlockCode block = ublock_getCode(ucs4);
        switch (block) {
        case UBLOCK_BASIC_LATIN:
            script = USCRIPT_LATIN;
            break;
        case UBLOCK_CJK_SYMBOLS_AND_PUNCTUATION:
            script = USCRIPT_HAN;
            break;
        case UBLOCK_HIRAGANA:
        case UBLOCK_KATAKANA:
            script = USCRIPT_HIRAGANA;
            break;
        case UBLOCK_ARABIC:
            script = USCRIPT_ARABIC;
            break;
        case UBLOCK_GREEK:
            script = USCRIPT_GREEK;
            break;
        case UBLOCK_DEVANAGARI:
            // For Danda and Double Danda (U+0964, U+0965), use a Devanagari
            // font for now although they're used by other scripts as well.
            // Without a context, we can't do any better.
            script = USCRIPT_DEVANAGARI;
            break;
        case UBLOCK_ARMENIAN:
            script = USCRIPT_ARMENIAN;
            break;
        case UBLOCK_GEORGIAN:
            script = USCRIPT_GEORGIAN;
            break;
        case UBLOCK_KANNADA:
            script = USCRIPT_KANNADA;
            break;
        }
    }

    // Another lame work-around to cover non-BMP characters.
    const UChar* family = getFontFamilyForScript(script, generic);
    if (!family) {
        int plane = ucs4 >> 16;
        switch (plane) {
        case 1:
            family = L"code2001";
            break;
        case 2:
            family = L"simsun-extb";
            break;
        default:
            family = L"lucida sans unicode";
        }
    }