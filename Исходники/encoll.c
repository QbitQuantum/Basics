static void TestTertiary( )
{
    int32_t testMoreSize;
    UCollationResult expected=UCOL_EQUAL;
    int32_t i,j;
    UErrorCode status = U_ZERO_ERROR;
    myCollation = ucol_open("en_US", &status);
    if(U_FAILURE(status)){
        log_err_status(status, "ERROR: in creation of rule based collator: %s\n", myErrorName(status));
        return;
    }
    log_verbose("Testing English Collation with Tertiary strength\n");

    ucol_setStrength(myCollation, UCOL_TERTIARY);
    for (i = 0; i < 38 ; i++)
    {
        doTest(myCollation, testSourceCases[i], testTargetCases[i], results[i]);
    }
  

    j = 0;
   for (i = 0; i < 10; i++)
    {
        for (j = i+1; j < 10; j++)
        {
            doTest(myCollation, testBugs[i], testBugs[j], UCOL_LESS);
        }
   }
    /*test more interesting cases */
    testMoreSize = UPRV_LENGTHOF(testMore);
    for (i = 0; i < testMoreSize; i++)
    {
        for (j = 0; j < testMoreSize; j++)
        {
            if (i <  j) expected = UCOL_LESS;
            if (i == j) expected = UCOL_EQUAL;
            if (i >  j) expected = UCOL_GREATER;
            doTest(myCollation, testMore[i], testMore[j], expected );
        }
    }
    ucol_close(myCollation);
}