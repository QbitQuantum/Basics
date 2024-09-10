// caller needs to free() the result
WCHAR *DecodeHtmlEntitites(const char *string, UINT codepage)
{
    WCHAR *fixed = str::conv::FromCodePage(string, codepage), *dst = fixed;
    const WCHAR *src = fixed;

    while (*src) {
        if (*src != '&') {
            *dst++ = *src++;
            continue;
        }
        src++;
        // numeric entities
        int unicode;
        if (str::Parse(src, L"#%d;", &unicode) ||
            str::Parse(src, L"#x%x;", &unicode)) {
            *dst++ = IntToChar(unicode);
            src = str::FindChar(src, ';') + 1;
            continue;
        }

        // named entities
        int rune = -1;
        const WCHAR *entityEnd = src;
        while (iswalnum(*entityEnd))
            entityEnd++;
        if (entityEnd != src) {
            size_t entityLen = entityEnd - src;
            rune = HtmlEntityNameToRune(src, entityLen);
        }
        if (-1 != rune) {
            *dst++ = IntToChar(rune);
            src = entityEnd;
            if (*src == ';')
                ++src;
        } else {
            *dst++ = '&';
        }
    }
    *dst = '\0';

    return fixed;
}