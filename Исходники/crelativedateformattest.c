static void TestCombineDateTime()
{
    const CombineDateTimeTestItem *itemPtr;
    log_verbose("\nTesting ureldatefmt_combineDateAndTime() with various parameters\n");
    for (itemPtr = combTestItems; itemPtr->locale != NULL; itemPtr++) {
        URelativeDateTimeFormatter *reldatefmt = NULL;
        UErrorCode status = U_ZERO_ERROR;
        UChar ubufreldate[kUBufMax];
        UChar ubuftime[kUBufMax];
        UChar ubufget[kUBufMax];
        int32_t ulenreldate, ulentime, ulenget;

        reldatefmt = ureldatefmt_open(itemPtr->locale, NULL, itemPtr->width, itemPtr->capContext, &status);
        if ( U_FAILURE(status) ) {
            log_data_err("FAIL: ureldatefmt_open() for locale %s, width %d, capContext %d: %s\n",
                    itemPtr->locale, (int)itemPtr->width, (int)itemPtr->capContext, myErrorName(status) );
            continue;
        }

        ulenreldate = u_unescape(itemPtr->relativeDateString, ubufreldate, kUBufMax);
        ulentime    = u_unescape(itemPtr->timeString,         ubuftime,    kUBufMax);
        ulenget     = ureldatefmt_combineDateAndTime(reldatefmt, ubufreldate, ulenreldate, ubuftime, ulentime, ubufget, kUBufMax, &status);
        if ( U_FAILURE(status) ) {
            log_err("FAIL: ureldatefmt_combineDateAndTime() for locale %s, width %d, capContext %d: %s\n",
                itemPtr->locale, (int)itemPtr->width, (int)itemPtr->capContext, myErrorName(status) );
        } else {
            UChar ubufexp[kUBufMax];
            int32_t ulenexp = u_unescape(itemPtr->expectedResult, ubufexp, kUBufMax);
            if (ulenget != ulenexp || u_strncmp(ubufget, ubufexp, ulenexp) != 0) {
                char  bbufget[kBBufMax];
                u_austrncpy(bbufget, ubufget, kUBufMax);
                log_err("ERROR: ureldatefmt_combineDateAndTime() for locale %s, width %d, capContext %d;\n      expected %s\n      get      %s\n",
                    itemPtr->locale, (int)itemPtr->width, (int)itemPtr->capContext, itemPtr->expectedResult, bbufget );
            }
        }
        // preflight test
        status = U_ZERO_ERROR;
        ulenget = ureldatefmt_combineDateAndTime(reldatefmt, ubufreldate, ulenreldate, ubuftime, ulentime, NULL, 0, &status);
        if ( status != U_BUFFER_OVERFLOW_ERROR) {
            log_err("FAIL: ureldatefmt_combineDateAndTime() preflight for locale %s, width %d, capContext %d: expected U_BUFFER_OVERFLOW_ERROR, got %s\n",
                itemPtr->locale, (int)itemPtr->width, (int)itemPtr->capContext, myErrorName(status) );
        } else {
            UChar ubufexp[kUBufMax];
            int32_t ulenexp = u_unescape(itemPtr->expectedResult, ubufexp, kUBufMax);
            if (ulenget != ulenexp) {
                log_err("ERROR: ureldatefmt_combineDateAndTime() preflight for locale %s, width %d, capContext %d;\n      expected len %d, get len %d\n",
                    itemPtr->locale, (int)itemPtr->width, (int)itemPtr->capContext, ulenexp, ulenget );
            }
        }

        ureldatefmt_close(reldatefmt);
    }
}