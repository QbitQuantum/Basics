U_CAPI UTransliterator* U_EXPORT2
utrans_open(const char* id,
            UTransDirection dir,
            const UChar* rules,         /* may be Null */
            int32_t rulesLength,        /* -1 if null-terminated */
            UParseError* parseError,    /* may be Null */
            UErrorCode* status) {
    UnicodeString ID(id, -1, US_INV); // use invariant converter
    return utrans_openU(ID.getBuffer(), ID.length(), dir,
                        rules, rulesLength,
                        parseError, status);
}