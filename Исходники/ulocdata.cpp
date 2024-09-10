U_CAPI int32_t U_EXPORT2
ulocdata_getLocaleSeparator(ULocaleData *uld,
                            UChar *result,
                            int32_t resultCapacity,
                            UErrorCode *status)  {
    UResourceBundle *separatorBundle;
    int32_t len = 0;
    const UChar *separator = NULL;
    UErrorCode localStatus = U_ZERO_ERROR;
    UChar *p0, *p1;
    static const UChar sub0[4] = { 0x007b, 0x0030, 0x007d , 0x0000 }; /* {0} */
    static const UChar sub1[4] = { 0x007b, 0x0031, 0x007d , 0x0000 }; /* {1} */
    static const int32_t subLen = 3;

    if (U_FAILURE(*status))
        return 0;

    separatorBundle = ures_getByKey(uld->langBundle, "localeDisplayPattern", NULL, &localStatus);

    if ( (localStatus == U_USING_DEFAULT_WARNING) && uld->noSubstitute ) {
        localStatus = U_MISSING_RESOURCE_ERROR;
    }

    if (localStatus != U_ZERO_ERROR) {
        *status = localStatus;
    }

    if (U_FAILURE(*status)){
        ures_close(separatorBundle);
        return 0;
    }

    separator = ures_getStringByKey(separatorBundle, "separator", &len, &localStatus);
    ures_close(separatorBundle);

    if ( (localStatus == U_USING_DEFAULT_WARNING) && uld->noSubstitute ) {
        localStatus = U_MISSING_RESOURCE_ERROR;
    }

    if (localStatus != U_ZERO_ERROR) {
        *status = localStatus;
    }

    if (U_FAILURE(*status)){
        return 0;
    }

    /* For backwards compatibility, if we have a pattern, return the portion between {0} and {1} */
    p0=u_strstr(separator, sub0);
    p1=u_strstr(separator, sub1);
    if (p0!=NULL && p1!=NULL && p0<=p1) {
        separator = (const UChar *)p0 + subLen;
        len = static_cast<int32_t>(p1 - separator);
        /* Desired separator is no longer zero-terminated; handle that if necessary */
        if (len < resultCapacity) {
            u_strncpy(result, separator, len);
            result[len] = 0;
            return len;
        }
    }

    u_strncpy(result, separator, resultCapacity);
    return len;
}