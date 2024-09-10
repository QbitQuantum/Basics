void TestConstruction1()
{
    UResourceBundle *test1 = 0, *test2 = 0;
    const UChar *result1, *result2;
    int32_t resultLen;
    UChar temp[7];

    UErrorCode   err = U_ZERO_ERROR;
    const char* testdatapath ;
    const char*      locale="te_IN";

    log_verbose("Testing ures_open()......\n");


    testdatapath=loadTestData(&err);
    if(U_FAILURE(err))
    {
        log_data_err("Could not load testdata.dat %s \n",myErrorName(err));
        return;
    }

    test1=ures_open(testdatapath, NULL, &err);
    if(U_FAILURE(err))
    {
        log_err("construction of %s did not succeed :  %s \n",NULL, myErrorName(err));
        return;
    }


    test2=ures_open(testdatapath, locale, &err);
    if(U_FAILURE(err))
    {
        log_err("construction of %s did not succeed :  %s \n",locale, myErrorName(err));
        return;
    }
    result1= ures_getStringByKey(test1, "string_in_Root_te_te_IN", &resultLen, &err);
    result2= ures_getStringByKey(test2, "string_in_Root_te_te_IN", &resultLen, &err);


    if (U_FAILURE(err)) {
        log_err("Something threw an error in TestConstruction(): %s\n", myErrorName(err));
        return;
    }

    u_uastrcpy(temp, "TE_IN");

    if(u_strcmp(result2, temp)!=0)
    {
        int n;

        log_err("Construction test failed for ures_open();\n");
        if(!getTestOption(VERBOSITY_OPTION))
            log_info("(run verbose for more information)\n");

        log_verbose("\nGot->");
        for(n=0;result2[n];n++)
        {
            log_verbose("%04X ",result2[n]);
        }
        log_verbose("<\n");

        log_verbose("\nWant>");
        for(n=0;temp[n];n++)
        {
            log_verbose("%04X ",temp[n]);
        }
        log_verbose("<\n");

    }

    log_verbose("for string_in_Root_te_te_IN, default.txt had  %s\n", austrdup(result1));
    log_verbose("for string_in_Root_te_te_IN, te_IN.txt had %s\n", austrdup(result2));

    /* Test getVersionNumber*/
    log_verbose("Testing version number\n");
    log_verbose("for getVersionNumber :  %s\n", ures_getVersionNumber(test1));

    ures_close(test1);
    ures_close(test2);
}