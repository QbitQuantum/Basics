std::unique_ptr<Length[]> newCoordsArray(const String& string, int& len)
{
    unsigned length = string.length();
    StringBuffer<UChar> spacified(length);
    for (unsigned i = 0; i < length; i++) {
        UChar cc = string[i];
        if (cc > '9' || (cc < '0' && cc != '-' && cc != '*' && cc != '.'))
            spacified[i] = ' ';
        else
            spacified[i] = cc;
    }
    RefPtr<StringImpl> str = StringImpl::adopt(spacified);

    str = str->simplifyWhiteSpace();

    len = countCharacter(*str, ' ') + 1;
    auto r = std::make_unique<Length[]>(len);

    int i = 0;
    unsigned pos = 0;
    size_t pos2;

    auto upconvertedCharacters = StringView(str.get()).upconvertedCharacters();
    while ((pos2 = str->find(' ', pos)) != notFound) {
        r[i++] = parseLength(upconvertedCharacters + pos, pos2 - pos);
        pos = pos2+1;
    }
    r[i] = parseLength(upconvertedCharacters + pos, str->length() - pos);

    ASSERT(i == len - 1);

    return r;
}