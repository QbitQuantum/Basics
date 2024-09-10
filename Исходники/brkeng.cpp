DictionaryMatcher *
ICULanguageBreakFactory::loadDictionaryMatcherFor(UScriptCode script, int32_t /* brkType */) {
    UErrorCode status = U_ZERO_ERROR;
    // open root from brkitr tree.
    UResourceBundle *b = ures_open(U_ICUDATA_BRKITR, "", &status);
    b = ures_getByKeyWithFallback(b, "dictionaries", b, &status);
    int32_t dictnlength = 0;
    const UChar *dictfname =
        ures_getStringByKeyWithFallback(b, uscript_getShortName(script), &dictnlength, &status);
    if (U_FAILURE(status)) {
        ures_close(b);
        return NULL;
    }
    CharString dictnbuf;
    CharString ext;
    const UChar *extStart = u_memrchr(dictfname, 0x002e, dictnlength);  // last dot
    if (extStart != NULL) {
        int32_t len = (int32_t)(extStart - dictfname);
        ext.appendInvariantChars(UnicodeString(FALSE, extStart + 1, dictnlength - len - 1), status);
        dictnlength = len;
    }
    dictnbuf.appendInvariantChars(UnicodeString(FALSE, dictfname, dictnlength), status);
    ures_close(b);

    UDataMemory *file = udata_open(U_ICUDATA_BRKITR, ext.data(), dictnbuf.data(), &status);
    if (U_SUCCESS(status)) {
        // build trie
        const uint8_t *data = (const uint8_t *)udata_getMemory(file);
        const int32_t *indexes = (const int32_t *)data;
        const int32_t offset = indexes[DictionaryData::IX_STRING_TRIE_OFFSET];
        const int32_t trieType = indexes[DictionaryData::IX_TRIE_TYPE] & DictionaryData::TRIE_TYPE_MASK;
        DictionaryMatcher *m = NULL;
        if (trieType == DictionaryData::TRIE_TYPE_BYTES) {
            const int32_t transform = indexes[DictionaryData::IX_TRANSFORM];
            const char *characters = (const char *)(data + offset);
            m = new BytesDictionaryMatcher(characters, transform, file);
        }
        else if (trieType == DictionaryData::TRIE_TYPE_UCHARS) {
            const UChar *characters = (const UChar *)(data + offset);
            m = new UCharsDictionaryMatcher(characters, file);
        }
        if (m == NULL) {
            // no matcher exists to take ownership - either we are an invalid
            // type or memory allocation failed
            udata_close(file);
        }
        return m;
    } else if (dictfname != NULL) {
        // we don't have a dictionary matcher.
        // returning NULL here will cause us to fail to find a dictionary break engine, as expected
        status = U_ZERO_ERROR;
        return NULL;
    }
    return NULL;
}