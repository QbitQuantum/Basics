void
NewResourceBundleTest::TestOtherAPI(){
    UErrorCode   err = U_ZERO_ERROR;
    const char* testdatapath=loadTestData(err);
    UnicodeString tDataPathUS = UnicodeString(testdatapath, "");

    if(U_FAILURE(err))
    {
        dataerrln("Could not load testdata.dat %s " + UnicodeString(u_errorName(err)));
        return;
    }

    /* Make sure that users using te_IN for the default locale don't get test failures. */
    Locale originalDefault;
    if (Locale::getDefault() == Locale("te_IN")) {
        Locale::setDefault(Locale("en_US"), err);
    }

    Locale       *locale=new Locale("te_IN");

    ResourceBundle test0(tDataPathUS, *locale, err);
    if(U_FAILURE(err)){
        errln("Construction failed");
        return;
    }

    ResourceBundle  test1(testdatapath, *locale, err);
    if(U_FAILURE(err)){
        errln("Construction failed");
        return;
    }

    logln("Testing getLocale()\n");
    if(strcmp(test1.getLocale().getName(), locale->getName()) !=0 ){
        errln("FAIL: ResourceBundle::getLocale() failed\n");
    }

    delete locale;

    logln("Testing ResourceBundle(UErrorCode)\n");
    ResourceBundle defaultresource(err);
    ResourceBundle explicitdefaultresource(NULL, Locale::getDefault(), err);
    if(U_FAILURE(err)){
        errcheckln(err, "Construction of default resourcebundle failed - %s", u_errorName(err));
        return;
    }
    // You can't compare the default locale to the resolved locale in the
    // resource bundle due to aliasing, keywords in the default locale
    // or the chance that the machine running these tests is using a locale
    // that isn't available in ICU.
    if(strcmp(defaultresource.getLocale().getName(), explicitdefaultresource.getLocale().getName()) != 0){
        errln("Construction of default resourcebundle didn't take the defaultlocale. Expected %s Got %s err=%s\n",
            explicitdefaultresource.getLocale().getName(), defaultresource.getLocale().getName(), u_errorName(err));
    }
    

    ResourceBundle copyRes(defaultresource);
    if(strcmp(copyRes.getName(), defaultresource.getName() ) !=0  ||
        strcmp(test1.getName(), defaultresource.getName() ) ==0 ||
        strcmp(copyRes.getLocale().getName(), defaultresource.getLocale().getName() ) !=0  ||
        strcmp(test1.getLocale().getName(), defaultresource.getLocale().getName() ) ==0 )
    {
        errln("copy construction failed\n");
    }

    ResourceBundle defaultSub = defaultresource.get((int32_t)0, err);
    ResourceBundle defSubCopy(defaultSub);
    if(strcmp(defSubCopy.getName(), defaultSub.getName() ) !=0  ||
        strcmp(defSubCopy.getLocale().getName(), defaultSub.getLocale().getName() ) !=0  ){
        errln("copy construction for subresource failed\n");
    }

    ResourceBundle *p;

    p = defaultresource.clone();
    if(p == &defaultresource || !equalRB(*p, defaultresource)) {
        errln("ResourceBundle.clone() failed");
    }
    delete p;

    p = defaultSub.clone();
    if(p == &defaultSub || !equalRB(*p, defaultSub)) {
        errln("2nd ResourceBundle.clone() failed");
    }
    delete p;

    UVersionInfo ver;
    copyRes.getVersion(ver);

    logln("Version returned: [%d.%d.%d.%d]\n", ver[0], ver[1], ver[2], ver[3]);

    logln("Testing C like UnicodeString APIs\n");

    UResourceBundle *testCAPI = NULL, *bundle = NULL, *rowbundle = NULL, *temp = NULL;
    err = U_ZERO_ERROR;
    const char* data[]={
        "string_in_Root_te_te_IN",   "1",
        "array_in_Root_te_te_IN",    "5",
        "array_2d_in_Root_te_te_IN", "4",
    };


    testCAPI = ures_open(testdatapath, "te_IN", &err);

    if(U_SUCCESS(err)) {
        // Do the testing
        // first iteration

        uint32_t i;
        int32_t count, row=0, col=0;
        char buf[5];
        UnicodeString expected;
        UnicodeString element("TE_IN");
        UnicodeString action;


        for(i=0; i<UPRV_LENGTHOF(data); i=i+2){
            action = "te_IN";
            action +=".get(";
            action += data[i];
            action +=", err)";
            err=U_ZERO_ERROR;
            bundle = ures_getByKey(testCAPI, data[i], bundle, &err); 
            if(!U_FAILURE(err)){
                const char* key = NULL;
                action = "te_IN";
                action +=".getKey()";

                CONFIRM_EQ((UnicodeString)ures_getKey(bundle), (UnicodeString)data[i]);

                count=0;
                row=0;
                while(ures_hasNext(bundle)){
                    action = data[i];
                    action +=".getNextString(err)";
                    row=count;   
                    UnicodeString got=ures_getNextUnicodeString(bundle, &key, &err);
                    if(U_SUCCESS(err)){
                        expected=element;
                        if(ures_getSize(bundle) > 1){
                            CONFIRM_EQ(ures_getType(bundle), URES_ARRAY);
                            expected+=itoa(row, buf);
                            rowbundle=ures_getByIndex(bundle, row, rowbundle, &err);
                            if(!U_FAILURE(err) && ures_getSize(rowbundle)>1){
                                col=0;
                                while(ures_hasNext(rowbundle)){
                                    expected=element;
                                    got=ures_getNextUnicodeString(rowbundle, &key, &err);
                                    temp = ures_getByIndex(rowbundle, col, temp, &err);
                                    UnicodeString bla = ures_getUnicodeString(temp, &err);
                                    UnicodeString bla2 = ures_getUnicodeStringByIndex(rowbundle, col, &err);
                                    if(!U_FAILURE(err)){
                                        expected+=itoa(row, buf);
                                        expected+=itoa(col, buf);
                                        col++;
                                        CONFIRM_EQ(got, expected);
                                        CONFIRM_EQ(bla, expected);
                                        CONFIRM_EQ(bla2, expected);
                                    }
                                }
                                CONFIRM_EQ(col, ures_getSize(rowbundle));
                            }
                        }
                        else{
                            CONFIRM_EQ(ures_getType(bundle), (int32_t)URES_STRING);
                        }
                    }
                    CONFIRM_EQ(got, expected);
                    count++;
                }
            }
        }

        // Check that ures_getUnicodeString() & variants return a bogus string if failure.
        // Same relevant code path whether the failure code is passed in
        // or comes from a lookup error.
        UErrorCode failure = U_INTERNAL_PROGRAM_ERROR;
        assertTrue("ures_getUnicodeString(failure).isBogus()",
                   ures_getUnicodeString(testCAPI, &failure).isBogus());
        assertTrue("ures_getNextUnicodeString(failure).isBogus()",
                   ures_getNextUnicodeString(testCAPI, NULL, &failure).isBogus());
        assertTrue("ures_getUnicodeStringByIndex(failure).isBogus()",
                   ures_getUnicodeStringByIndex(testCAPI, 999, &failure).isBogus());
        assertTrue("ures_getUnicodeStringByKey(failure).isBogus()",
                   ures_getUnicodeStringByKey(testCAPI, "bogus key", &failure).isBogus());

        ures_close(temp);
        ures_close(rowbundle);
        ures_close(bundle);
        ures_close(testCAPI);
    } else {
        errln("failed to open a resource bundle\n");
    }

    /* Restore the default locale for the other tests. */
    Locale::setDefault(originalDefault, err);
}