static void TestTertiary( )
{

    int32_t i;
    UErrorCode status = U_ZERO_ERROR;
    myCollation = ucol_open("fr_CA", &status);
    if(U_FAILURE(status) || !myCollation) {
        log_err_status(status, "ERROR: in creation of rule based collator: %s\n", myErrorName(status));
        return;
    }

    ucol_setAttribute(myCollation, UCOL_ALTERNATE_HANDLING, UCOL_SHIFTED, &status);
    if(U_FAILURE(status)) {
        log_err("ERROR: in creation of rule based collator: %s\n", myErrorName(status));
        return;
    }
    log_verbose("Testing fr_CA Collation with Tertiary strength\n");
    ucol_setStrength(myCollation, UCOL_QUATERNARY);
    for (i = 0; i < 12 ; i++)
    {
        doTest(myCollation, testSourceCases[i], testTargetCases[i], results[i]);
    }
    ucol_close(myCollation);
}