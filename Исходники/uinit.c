U_CAPI void U_EXPORT2
u_init(UErrorCode *status) {
    UTRACE_ENTRY_OC(UTRACE_U_INIT);
    /* Make sure the global mutexes are initialized. */
    umtx_init(NULL);
    umtx_lock(&gICUInitMutex);
    if (gICUInitialized || U_FAILURE(*status)) {
        umtx_unlock(&gICUInitMutex);
        UTRACE_EXIT_STATUS(*status);
        return;
    }

#if 1
    /*
     * 2005-may-02
     *
     * ICU4C 3.4 (jitterbug 4497) hardcodes the data for Unicode character
     * properties for APIs that want to be fast.
     * Therefore, we need not load them here nor check for errors.
     * Instead, we load the converter alias table to see if any ICU data
     * is available.
     * Users should really open the service objects they need and check
     * for errors there, to make sure that the actual items they need are
     * available.
     */
#if !UCONFIG_NO_CONVERSION
    ucnv_io_countKnownConverters(status);
#endif
#else
    /* Do any required init for services that don't have open operations
     * and use "only" the double-check initialization method for performance
     * reasons (avoiding a mutex lock even for _checking_ whether the
     * initialization had occurred).
     */

    /* Char Properties */
    uprv_haveProperties(status);

    /* load the case and bidi properties but don't fail if they are not available */
    u_isULowercase(0x61);
    u_getIntPropertyValue(0x200D, UCHAR_JOINING_TYPE); /* ZERO WIDTH JOINER: Join_Causing */

#if !UCONFIG_NO_NORMALIZATION
    /*  Normalization  */
    unorm_haveData(status);
#endif
#endif
    gICUInitialized = TRUE;    /* TODO:  don't set if U_FAILURE? */
    umtx_unlock(&gICUInitMutex);
    UTRACE_EXIT_STATUS(*status);
}