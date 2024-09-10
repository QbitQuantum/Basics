void
StringCaseTest::TestCasing() {
    UErrorCode status = U_ZERO_ERROR;
    void *iter;
    char cLocaleID[100];
    UnicodeString locale, input, output, optionsString, result;
    uint32_t options;
    int32_t whichCase, type;
    TestDataModule *driver = TestDataModule::getTestDataModule("casing", *this, status);
    if(U_SUCCESS(status)) {
        for(whichCase=0; whichCase<TEST_COUNT; ++whichCase) {
#if UCONFIG_NO_BREAK_ITERATION
            if(whichCase==TEST_TITLE) {
                continue;
            }
#endif
            TestData *casingTest = driver->createTestData(dataNames[whichCase], status);
            if(U_FAILURE(status)) {
                errln("TestCasing failed to createTestData(%s) - %s", dataNames[whichCase], u_errorName(status));
                break;
            }
            const DataMap *myCase = NULL;
            while(casingTest->nextCase(myCase, status)) {
                input = myCase->getString("Input", status);
                output = myCase->getString("Output", status);

                if(whichCase!=TEST_FOLD) {
                    locale = myCase->getString("Locale", status);
                }
                locale.extract(0, 0x7fffffff, cLocaleID, sizeof(cLocaleID), "");

                iter=NULL;
#if !UCONFIG_NO_BREAK_ITERATION
                if(whichCase==TEST_TITLE) {
                    type = myCase->getInt("Type", status);
                    if(type>=0) {
                        iter=ubrk_open((UBreakIteratorType)type, cLocaleID, NULL, 0, &status);
                    } else if(type==-2) {
                        // Open a trivial break iterator that only delivers { 0, length }
                        // or even just { 0 } as boundaries.
                        static const UChar rules[] = { 0x2e, 0x2a, 0x3b };  // ".*;"
                        UParseError parseError;
                        iter=ubrk_openRules(rules, LENGTHOF(rules), NULL, 0, &parseError, &status);
                    }
                }
#endif
                options = 0;
                if(whichCase==TEST_TITLE || whichCase==TEST_FOLD) {
                    optionsString = myCase->getString("Options", status);
                    if(optionsString.indexOf((UChar)0x54)>=0) {  // T
                        options|=U_FOLD_CASE_EXCLUDE_SPECIAL_I;
                    }
                    if(optionsString.indexOf((UChar)0x4c)>=0) {  // L
                        options|=U_TITLECASE_NO_LOWERCASE;
                    }
                    if(optionsString.indexOf((UChar)0x41)>=0) {  // A
                        options|=U_TITLECASE_NO_BREAK_ADJUSTMENT;
                    }
                }

                if(U_FAILURE(status)) {
                    errln("error: TestCasing() setup failed for %s test case from casing.res: %s", dataNames[whichCase],  u_errorName(status));
                    status = U_ZERO_ERROR;
                } else {
                    TestCasingImpl(input, output, whichCase, iter, cLocaleID, options);
                }

#if !UCONFIG_NO_BREAK_ITERATION
                if(iter!=NULL) {
                    ubrk_close(iter);
                }
#endif
            }
            delete casingTest;
        }
    }
    delete driver;

#if !UCONFIG_NO_BREAK_ITERATION
    // more tests for API coverage
    status=U_ZERO_ERROR;
    input=UNICODE_STRING_SIMPLE("sTrA\\u00dfE").unescape();
    (result=input).toTitle(NULL);
    if(result!=UNICODE_STRING_SIMPLE("Stra\\u00dfe").unescape()) {
        errln("UnicodeString::toTitle(NULL) failed");
    }
#endif
}