void LocaleDisplayNamesTest::TestUldnDisplayContext() {
    const LocNameDispContextItem * ctxtItemPtr;
    for (ctxtItemPtr = ctxtItems; ctxtItemPtr->displayLocale != NULL; ctxtItemPtr++) {
        UDisplayContext contexts[2] = {ctxtItemPtr->dialectHandling, ctxtItemPtr->capitalization};
        UErrorCode status = U_ZERO_ERROR;
        ULocaleDisplayNames * uldn = uldn_openForContext(ctxtItemPtr->displayLocale, contexts, 2, &status);
        if (U_FAILURE(status)) {
            errln(UnicodeString("FAIL: uldn_openForContext failed for locale ") + ctxtItemPtr->displayLocale +
                  ", dialectHandling " + ctxtItemPtr->dialectHandling + ", capitalization " +  ctxtItemPtr->capitalization);
        } else {
            UDisplayContext dialectHandling = uldn_getContext(uldn, UDISPCTX_TYPE_DIALECT_HANDLING, &status);
            UDisplayContext capitalization = uldn_getContext(uldn, UDISPCTX_TYPE_CAPITALIZATION, &status);
            if (U_FAILURE(status)) {
                errln(UnicodeString("FAIL: uldn_getContext status ") + (int)status);
            } else if (dialectHandling != ctxtItemPtr->dialectHandling || capitalization != ctxtItemPtr->capitalization) {
                errln("FAIL: uldn_getContext retrieved incorrect dialectHandling or capitalization");
            } else {
                UChar nameBuf[ULOC_FULLNAME_CAPACITY];
                int32_t len = uldn_localeDisplayName(uldn, ctxtItemPtr->localeToBeNamed, nameBuf, ULOC_FULLNAME_CAPACITY, &status);
                if (U_FAILURE(status)) {
                    dataerrln(UnicodeString("FAIL: uldn_localeDisplayName status: ") + u_errorName(status));
                } else if (u_strcmp(ctxtItemPtr->result, nameBuf) != 0) {
                    UnicodeString exp(ctxtItemPtr->result, u_strlen(ctxtItemPtr->result));
                    UnicodeString got(nameBuf, len);
                    dataerrln(UnicodeString("FAIL: uldn_localeDisplayName, capitalization ") + ctxtItemPtr->capitalization +
                          ", expected " + exp + ", got " + got );
                }
            }
            uldn_close(uldn);
        }
    }
}