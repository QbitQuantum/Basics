static void TestTertiary( )
{
    
    int32_t i;
    UErrorCode status = U_ZERO_ERROR;
    myCollation = ucol_open("es_ES", &status);
    if(U_FAILURE(status)){
        log_err_status(status, "ERROR: %s: in creation of rule based collator: %s\n", __FILE__, myErrorName(status));
        return;
    }
    log_verbose("Testing Spanish Collation with Tertiary strength\n");
    ucol_setStrength(myCollation, UCOL_TERTIARY);
    for (i = 0; i < 5 ; i++)
    {
        doTest(myCollation, testSourceCases[i], testTargetCases[i], results[i]);
    }
    ucol_close(myCollation);
}