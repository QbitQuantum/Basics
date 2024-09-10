U_DRAFT int32_t U_EXPORT2
ulocdata_getLocaleSeparator(ULocaleData *uld,
                            UChar *result,
                            int32_t resultCapacity,
                            UErrorCode *status)  {
    UResourceBundle *separatorBundle;
    int32_t len = 0;
    const UChar *separator = NULL;
    UErrorCode localStatus = U_ZERO_ERROR;

    if (U_FAILURE(*status))
        return 0;

    separatorBundle = ures_getByKey(uld->bundle, "localeDisplayPattern", NULL, &localStatus);

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

    u_strncpy(result, separator, resultCapacity);
    return len;

}