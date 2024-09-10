static void TestRelativeCrash(void) {
       static const UChar tzName[] = { 0x0055, 0x0053, 0x002F, 0x0050, 0x0061, 0x0063, 0x0069, 0x0066, 0x0069, 0x0063, 0 };
       static const UDate aDate = -631152000000.0;

    UErrorCode status = U_ZERO_ERROR;
    UErrorCode expectStatus = U_ILLEGAL_ARGUMENT_ERROR;
    UDateFormat icudf;

    icudf = udat_open(UDAT_NONE, UDAT_SHORT_RELATIVE, "en", tzName, -1, NULL, 0, &status);
    if ( U_SUCCESS(status) ) {
        const char *what = "???";
        {
            UErrorCode subStatus = U_ZERO_ERROR;
            what = "udat_set2DigitYearStart";
            log_verbose("Trying %s on a relative date..\n", what);
            udat_set2DigitYearStart(icudf, aDate, &subStatus); 
            if(subStatus == expectStatus) {
                log_verbose("Success: did not crash on %s, but got %s.\n", what, u_errorName(subStatus));
            } else {
                log_err("FAIL: didn't crash on %s, but got success %s instead of %s. \n", what, u_errorName(subStatus), u_errorName(expectStatus));
            }            
        }
        {
            /* clone works polymorphically. try it anyways */
            UErrorCode subStatus = U_ZERO_ERROR;
            UDateFormat *oth;
            what = "clone";
            log_verbose("Trying %s on a relative date..\n", what);
            oth = udat_clone(icudf, &subStatus);
            if(subStatus == U_ZERO_ERROR) {
                log_verbose("Success: did not crash on %s, but got %s.\n", what, u_errorName(subStatus));
                udat_close(oth); /* ? */
            } else {
                log_err("FAIL: didn't crash on %s, but got  %s instead of %s. \n", what, u_errorName(subStatus), u_errorName(expectStatus));
            }            
        }
        {
            UErrorCode subStatus = U_ZERO_ERROR;
            what = "udat_get2DigitYearStart";
            log_verbose("Trying %s on a relative date..\n", what);
            udat_get2DigitYearStart(icudf, &subStatus); 
            if(subStatus == expectStatus) {
                log_verbose("Success: did not crash on %s, but got %s.\n", what, u_errorName(subStatus));
            } else {
                log_err("FAIL: didn't crash on %s, but got success %s instead of %s. \n", what, u_errorName(subStatus), u_errorName(expectStatus));
            }            
        }
        {
            /* Now udat_toPattern works for relative date formatters, unless localized is TRUE */
            UErrorCode subStatus = U_ZERO_ERROR;
            what = "udat_toPattern";
            log_verbose("Trying %s on a relative date..\n", what);
            udat_toPattern(icudf, TRUE,NULL,0, &subStatus); 
            if(subStatus == expectStatus) {
                log_verbose("Success: did not crash on %s, but got %s.\n", what, u_errorName(subStatus));
            } else {
                log_err("FAIL: didn't crash on %s, but got success %s instead of %s. \n", what, u_errorName(subStatus), u_errorName(expectStatus));
            }            
        }
        {
            UErrorCode subStatus = U_ZERO_ERROR;
            what = "udat_applyPattern";
            log_verbose("Trying %s on a relative date..\n", what);
            udat_applyPattern(icudf, FALSE,tzName,-1); 
            subStatus = U_ILLEGAL_ARGUMENT_ERROR; /* what it should be, if this took an errorcode. */
            if(subStatus == expectStatus) {
                log_verbose("Success: did not crash on %s, but got %s.\n", what, u_errorName(subStatus));
            } else {
                log_err("FAIL: didn't crash on %s, but got success %s instead of %s. \n", what, u_errorName(subStatus), u_errorName(expectStatus));
            }            
        }
        {
        	UChar erabuf[32];
            UErrorCode subStatus = U_ZERO_ERROR;
            what = "udat_getSymbols";
            log_verbose("Trying %s on a relative date..\n", what);
            udat_getSymbols(icudf, UDAT_ERAS,0,erabuf,sizeof(erabuf)/sizeof(erabuf[0]), &subStatus);
            if(subStatus == U_ZERO_ERROR) {
                log_verbose("Success: %s returned %s.\n", what, u_errorName(subStatus));
            } else {
                log_err("FAIL: didn't crash on %s, but got %s instead of U_ZERO_ERROR.\n", what, u_errorName(subStatus));
            }            
        }
        {
            UErrorCode subStatus = U_ZERO_ERROR;
            UChar symbolValue = 0x0041;
            what = "udat_setSymbols";
            log_verbose("Trying %s on a relative date..\n", what);
            udat_setSymbols(icudf, UDAT_ERAS,0,&symbolValue,1, &subStatus);  /* bogus values */
            if(subStatus == expectStatus) {
                log_verbose("Success: did not crash on %s, but got %s.\n", what, u_errorName(subStatus));
            } else {
                log_err("FAIL: didn't crash on %s, but got success %s instead of %s. \n", what, u_errorName(subStatus), u_errorName(expectStatus));
            }            
        }
        {
            UErrorCode subStatus = U_ZERO_ERROR;
            what = "udat_countSymbols";
            log_verbose("Trying %s on a relative date..\n", what);
            udat_countSymbols(icudf, UDAT_ERAS); 
            subStatus = U_ILLEGAL_ARGUMENT_ERROR; /* should have an errorcode. */
            if(subStatus == expectStatus) {
                log_verbose("Success: did not crash on %s, but got %s.\n", what, u_errorName(subStatus));
            } else {
                log_err("FAIL: didn't crash on %s, but got success %s instead of %s. \n", what, u_errorName(subStatus), u_errorName(expectStatus));
            }            
        }
        
        udat_close(icudf);
    } else {
         log_data_err("FAIL: err calling udat_open() ->%s (Are you missing data?)\n", u_errorName(status));
    }
}