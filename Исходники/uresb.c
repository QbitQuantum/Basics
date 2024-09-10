const UChar *getErrorName(UErrorCode errorNumber) {
    UErrorCode status = U_ZERO_ERROR;
    int32_t len = 0;

    UResourceBundle *error = ures_open(currdir, locale, &status);

    UResourceBundle *errorcodes = ures_getByKey(error, "errorcodes", NULL, &status);

    const UChar *result = ures_getStringByIndex(errorcodes, errorNumber, &len, &status);

    ures_close(errorcodes);
    ures_close(error);

    if(U_SUCCESS(status)) {
        return result;
    } else {
        return baderror;
    }

}