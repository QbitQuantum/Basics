void tryPat994(UDateFormat* format, const char* pattern, const char* s, UDate expected)
{
    UChar *f;
    UChar *str, *pat;
    UDate date;
    UDate null=0;
    int32_t pos;
    UErrorCode status = U_ZERO_ERROR;
    str=(UChar*)malloc(sizeof(UChar) * (strlen(s) + 1) );
    u_uastrcpy(str, s);
    pat=(UChar*)malloc(sizeof(UChar) * (strlen(pattern) + 1) );
    u_uastrcpy(pat, pattern);
    log_verbose("Pattern : %s ;  String : %s\n", austrdup(pat), austrdup(str));
    udat_applyPattern(format, FALSE, pat, u_strlen(pat));
    pos=0;
    date = udat_parse(format, str, u_strlen(str), &pos, &status);
    if(U_FAILURE(status) || date == null) {
        log_verbose("ParseException: : %s\n", myErrorName(status) );
         if (expected != null) 
             log_err("FAIL: Expected: %s\n", austrdup(myDateFormat(format, expected)) );
        }
    else {
        f=myDateFormat(format, date);
        log_verbose(" parse( %s ) -> %s\n", austrdup(str), austrdup(f));
        if (expected == null || date != expected) 
            log_err("FAIL: Expected null for \"%s\"\n", s);
        if (u_strcmp(f, str) !=0)
            log_err("FAIL: Expected : %s\n", austrdup(str) );
    }
    
    free(str);
    free(pat);
}