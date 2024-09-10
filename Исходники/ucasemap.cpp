U_NAMESPACE_USE

/* UCaseMap service object -------------------------------------------------- */

UCaseMap::UCaseMap(const char *localeID, uint32_t opts, UErrorCode *pErrorCode) :
#if !UCONFIG_NO_BREAK_ITERATION
        iter(NULL),
#endif
        caseLocale(UCASE_LOC_UNKNOWN), options(opts) {
    ucasemap_setLocale(this, localeID, pErrorCode);
}