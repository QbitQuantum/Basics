U_CFUNC int32_t
ustrcase_getCaseLocale(const char *locale) {
    if (locale == NULL) {
        locale = uloc_getDefault();
    }
    if (*locale == 0) {
        return UCASE_LOC_ROOT;
    } else {
        return ucase_getCaseLocale(locale);
    }
}