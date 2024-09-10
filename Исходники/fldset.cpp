int32_t FieldsSet::parseFrom(const UnicodeString& str, const
                             FieldsSet* inheritFrom, UErrorCode& status) {

    int goodFields = 0;

    if(U_FAILURE(status)) {
        return -1;
    }

    int32_t destCount = 0;
    UnicodeString *dest = split(str, 0x002C /* ',' */, destCount);

    for(int i = 0; i < destCount; i += 1) {
        int32_t dc = 0;
        UnicodeString *kv = split(dest[i], 0x003D /* '=' */, dc);

        if(dc != 2) {
            it_errln(UnicodeString("dc == ") + dc + UnicodeString("?"));
        }

        int32_t field = handleParseName(inheritFrom, kv[0], kv[1], status);

        if(U_FAILURE(status)) {
            char ch[256];
            const UChar *u = kv[0].getBuffer();
            int32_t len = kv[0].length();
            u_UCharsToChars(u, ch, len);
            ch[len] = 0; /* include terminating \0 */
            it_errln(UnicodeString("Parse Failed: Field ") + UnicodeString(ch) + UnicodeString(", err ") + UnicodeString(u_errorName(status)));
            return -1;
        }

        if(field != -1) {
            handleParseValue(inheritFrom, field, kv[1], status);

            if(U_FAILURE(status)) {
                char ch[256];
                const UChar *u = kv[1].getBuffer();
                int32_t len = kv[1].length();
                u_UCharsToChars(u, ch, len);
                ch[len] = 0; /* include terminating \0 */
                it_errln(UnicodeString("Parse Failed: Value ") + UnicodeString(ch) + UnicodeString(", err ") + UnicodeString(u_errorName(status)));
                return -1;
            }

            goodFields += 1;
        }

        delete[] kv;
    }

    delete[] dest;

    return goodFields;
}