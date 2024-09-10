U_CDECL_END

U_NAMESPACE_BEGIN

Locale *locale_set_default_internal(const char *id, UErrorCode& status) {
    // Synchronize this entire function.
    Mutex lock(&gDefaultLocaleMutex);

    UBool canonicalize = FALSE;

    // If given a NULL string for the locale id, grab the default
    //   name from the system.
    //   (Different from most other locale APIs, where a null name means use
    //    the current ICU default locale.)
    if (id == NULL) {
        id = uprv_getDefaultLocaleID();   // This function not thread safe? TODO: verify.
        canonicalize = TRUE; // always canonicalize host ID
    }

    char localeNameBuf[512];

    if (canonicalize) {
        uloc_canonicalize(id, localeNameBuf, sizeof(localeNameBuf)-1, &status);
    } else {
        uloc_getName(id, localeNameBuf, sizeof(localeNameBuf)-1, &status);
    }
    localeNameBuf[sizeof(localeNameBuf)-1] = 0;  // Force null termination in event of
                                                 //   a long name filling the buffer.
                                                 //   (long names are truncated.)
                                                 //
    if (U_FAILURE(status)) {
        return gDefaultLocale;
    }

    if (gDefaultLocalesHashT == NULL) {
        gDefaultLocalesHashT = uhash_open(uhash_hashChars, uhash_compareChars, NULL, &status);
        if (U_FAILURE(status)) {
            return gDefaultLocale;
        }
        uhash_setValueDeleter(gDefaultLocalesHashT, deleteLocale);
        ucln_common_registerCleanup(UCLN_COMMON_LOCALE, locale_cleanup);
    }

    Locale *newDefault = (Locale *)uhash_get(gDefaultLocalesHashT, localeNameBuf);
    if (newDefault == NULL) {
        newDefault = new Locale(Locale::eBOGUS);
        if (newDefault == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return gDefaultLocale;
        }
        newDefault->init(localeNameBuf, FALSE);
        uhash_put(gDefaultLocalesHashT, (char*) newDefault->getName(), newDefault, &status);
        if (U_FAILURE(status)) {
            return gDefaultLocale;
        }
    }
    gDefaultLocale = newDefault;
    return gDefaultLocale;
}