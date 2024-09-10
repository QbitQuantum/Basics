static void TestJB5273(){
    static const char INVALID_DOMAIN_NAME[] = "xn--m\\u00FCller.de";
    UChar invalid_idn[25] = {'\0'};
    int32_t len = u_unescape(INVALID_DOMAIN_NAME, invalid_idn, strlen(INVALID_DOMAIN_NAME));
    UChar output[50] = {'\0'};
    UErrorCode status = U_ZERO_ERROR;
    UParseError prsError;
    int32_t outLen = uidna_toUnicode(invalid_idn, len, output, 50, UIDNA_DEFAULT, &prsError, &status);
    if(U_FAILURE(status)){
        log_err_status(status, "uidna_toUnicode failed with error: %s\n", u_errorName(status));
    }
    status = U_ZERO_ERROR;
    outLen = uidna_toUnicode(invalid_idn, len, output, 50, UIDNA_USE_STD3_RULES, &prsError, &status);
    if(U_FAILURE(status)){
        log_err_status(status, "uidna_toUnicode failed with error: %s\n", u_errorName(status));
    }

    status = U_ZERO_ERROR;
    outLen = uidna_IDNToUnicode(invalid_idn, len, output, 50, UIDNA_DEFAULT, &prsError, &status);
    if(U_FAILURE(status)){
        log_err_status(status, "uidna_toUnicode failed with error: %s\n", u_errorName(status));
    }
    status = U_ZERO_ERROR;
    outLen = uidna_IDNToUnicode(invalid_idn, len, output, 50, UIDNA_USE_STD3_RULES, &prsError, &status);
    if(U_FAILURE(status)){
        log_err_status(status, "uidna_toUnicode failed with error: %s\n", u_errorName(status));
    }
}