/*
* Test Small, Large letters
*/
static void TestSmallLarge(void)
{
    int32_t i;
    UErrorCode status = U_ZERO_ERROR;
    myCollation = ucol_open("ja_JP", &status);
    if (U_FAILURE(status))
    {
        log_err_status(status, "ERROR: in creation of rule based collator: %s\n",
            myErrorName(status));
        return;
    }

    log_verbose("Testing Japanese Small and Large Characters Collation\n");
    ucol_setStrength(myCollation, UCOL_TERTIARY);
    ucol_setAttribute(myCollation, UCOL_CASE_LEVEL, UCOL_ON, &status);
    for (i = 0; i < 3 ; i++)
        doTest(myCollation, testSmallLargeCases[i], testSmallLargeCases[i + 1],
        UCOL_LESS);

    ucol_close(myCollation);
}