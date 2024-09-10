static UBool doTestUCharNames(const char *name, const char *standard, const char **expected, int32_t size) {
    UErrorCode err = U_ZERO_ERROR;
    UEnumeration *myEnum = ucnv_openStandardNames(name, standard, &err);
    int32_t enumCount = uenum_count(myEnum, &err);
    int32_t idx, repeatTimes = 3;
    
    if (err == U_FILE_ACCESS_ERROR) {
        log_data_err("Unable to open standard names for %s of standard: %s\n", name, standard);
        return 0;
    }
    
    if (size != enumCount) {
        log_err("FAIL: different size arrays. Got %d. Expected %d\n", enumCount, size);
        return 0;
    }
    if (size < 0 && myEnum) {
        log_err("FAIL: size < 0, but recieved an actual object\n");
        return 0;
    }
    log_verbose("\n%s %s\n", name, standard);
    while (repeatTimes-- > 0) {
        for (idx = 0; idx < enumCount; idx++) {
            UChar testName[256];
            int32_t len;
            const UChar *enumName = uenum_unext(myEnum, &len, &err);
            u_uastrncpy(testName, expected[idx], UPRV_LENGTHOF(testName));
            if (u_strcmp(enumName, testName) != 0 || U_FAILURE(err)
                || len != (int32_t)uprv_strlen(expected[idx]))
            {
                log_err("FAIL: uenum_next(%d) == \"%s\". expected \"%s\", len=%d, error=%s\n",
                    idx, enumName, testName, len, u_errorName(err));
            }
            log_verbose("%s\n", expected[idx]);
            err = U_ZERO_ERROR;
        }
        log_verbose("\n    reset\n");
        uenum_reset(myEnum, &err);
        if (U_FAILURE(err)) {
            log_err("FAIL: uenum_reset() for %s{%s} failed with %s\n",
                name, standard, u_errorName(err));
            err = U_ZERO_ERROR;
        }
    }
    uenum_close(myEnum);
    return 1;
}