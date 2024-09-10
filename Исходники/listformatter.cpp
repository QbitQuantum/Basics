static ListFormatInternal* loadListFormatInternal(
        const Locale& locale, const char * style, UErrorCode& errorCode) {
    UResourceBundle* rb = ures_open(NULL, locale.getName(), &errorCode);
    if (U_FAILURE(errorCode)) {
        ures_close(rb);
        return NULL;
    }
    rb = ures_getByKeyWithFallback(rb, "listPattern", rb, &errorCode);
    rb = ures_getByKeyWithFallback(rb, style, rb, &errorCode);

    // TODO(Travis Keep): This is a hack until fallbacks can be added for
    // listPattern/duration and listPattern/duration-narrow in CLDR.
    if (errorCode == U_MISSING_RESOURCE_ERROR) {
        errorCode = U_ZERO_ERROR;
        rb = ures_getByKeyWithFallback(rb, "standard", rb, &errorCode);
    }
    if (U_FAILURE(errorCode)) {
        ures_close(rb);
        return NULL;
    }
    UnicodeString two, start, middle, end;
    getStringByKey(rb, "2", two, errorCode);
    getStringByKey(rb, "start", start, errorCode);
    getStringByKey(rb, "middle", middle, errorCode);
    getStringByKey(rb, "end", end, errorCode);
    ures_close(rb);
    if (U_FAILURE(errorCode)) {
        return NULL;
    }
    ListFormatInternal* result = new ListFormatInternal(two, start, middle, end);
    if (result == NULL) {
        errorCode = U_MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    return result;
}