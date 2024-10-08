static void TestUSpoofCAPI(void) {

    /*
     *  basic uspoof_open().
     */
    {
        USpoofChecker *sc;
        UErrorCode  status = U_ZERO_ERROR;
        sc = uspoof_open(&status);
        TEST_ASSERT_SUCCESS(status);
        if (U_FAILURE(status)) {
            /* If things are so broken that we can't even open a default spoof checker,  */
            /*   don't even try the rest of the tests.  They would all fail.             */
            return;
        }
        uspoof_close(sc);
    }

    
        
    /*
     *  Test Open from source rules.
    */
    TEST_SETUP
    const char *dataSrcDir;
    char       *fileName;
    char       *confusables;
    int         confusablesLength;
    char       *confusablesWholeScript;
    int         confusablesWholeScriptLength;
    FILE       *f;
    UParseError pe;
    int32_t     errType;
    USpoofChecker *rsc;
    
    dataSrcDir = ctest_dataSrcDir();
    fileName = malloc(strlen(dataSrcDir) + 100);
    strcpy(fileName, dataSrcDir);
    strcat(fileName, U_FILE_SEP_STRING "unidata" U_FILE_SEP_STRING "confusables.txt");
    f = fopen(fileName, "r");
    TEST_ASSERT_NE(f, NULL);
    confusables = malloc(3000000);
    confusablesLength = fread(confusables, 1, 3000000, f);
    fclose(f);

    
    strcpy(fileName, dataSrcDir);
    strcat(fileName, U_FILE_SEP_STRING "unidata" U_FILE_SEP_STRING "confusablesWholeScript.txt");
    f = fopen(fileName, "r");
    TEST_ASSERT_NE(f, NULL);
    confusablesWholeScript = malloc(1000000);
    confusablesWholeScriptLength = fread(confusablesWholeScript, 1, 1000000, f);
    fclose(f);

    rsc = uspoof_openFromSource(confusables, confusablesLength,
                                              confusablesWholeScript, confusablesWholeScriptLength,
                                              &errType, &pe, &status);
    TEST_ASSERT_SUCCESS(status);

    free(confusablesWholeScript);
    free(confusables);
    free(fileName);
    uspoof_close(rsc);
    /*  printf("ParseError Line is %d\n", pe.line);  */
    TEST_TEARDOWN;


    /*
     * openFromSerialized and serialize
    */
    TEST_SETUP
        int32_t        serializedSize = 0;
        int32_t        actualLength = 0;
        char           *buf;
        USpoofChecker  *sc2;
        int32_t         checkResults;

        
        serializedSize = uspoof_serialize(sc, NULL, 0, &status);
        TEST_ASSERT_EQ(status, U_BUFFER_OVERFLOW_ERROR);
        TEST_ASSERT(serializedSize > 0);

        /* Serialize the default spoof checker */
        status = U_ZERO_ERROR;
        buf = (char *)malloc(serializedSize + 10);
        TEST_ASSERT(buf != NULL);
        buf[serializedSize] = 42;
        uspoof_serialize(sc, buf, serializedSize, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(42, buf[serializedSize]);

        /* Create a new spoof checker from the freshly serialized data */
        sc2 = uspoof_openFromSerialized(buf, serializedSize+10, &actualLength, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_NE(NULL, sc2);
        TEST_ASSERT_EQ(serializedSize, actualLength);

        /* Verify that the new spoof checker at least wiggles */
        checkResults = uspoof_check(sc2, goodLatin, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);

        checkResults = uspoof_check(sc2, scMixed, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_SINGLE_SCRIPT | USPOOF_MIXED_SCRIPT_CONFUSABLE, checkResults);

        uspoof_close(sc2);
        free(buf);
    TEST_TEARDOWN;
        
        
        
    /*
     * Set & Get Check Flags
    */
    TEST_SETUP
        int32_t t;
        uspoof_setChecks(sc, USPOOF_ALL_CHECKS, &status);
        TEST_ASSERT_SUCCESS(status);
        t = uspoof_getChecks(sc, &status);
        TEST_ASSERT_EQ(t, USPOOF_ALL_CHECKS);
    
        uspoof_setChecks(sc, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        t = uspoof_getChecks(sc, &status);
        TEST_ASSERT_EQ(0, t);
        
        uspoof_setChecks(sc,
                        USPOOF_WHOLE_SCRIPT_CONFUSABLE | USPOOF_MIXED_SCRIPT_CONFUSABLE | USPOOF_ANY_CASE,
                        &status);
        TEST_ASSERT_SUCCESS(status);
        t = uspoof_getChecks(sc, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_WHOLE_SCRIPT_CONFUSABLE | USPOOF_MIXED_SCRIPT_CONFUSABLE | USPOOF_ANY_CASE, t);
    TEST_TEARDOWN;

    /*
    * get & setAllowedChars
    */
    TEST_SETUP
        USet *us;
        const USet *uset;

        uset = uspoof_getAllowedChars(sc, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(uset_isFrozen(uset));
        us = uset_open((UChar32)0x41, (UChar32)0x5A);   /*  [A-Z]  */
        uspoof_setAllowedChars(sc, us, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_NE(us, uspoof_getAllowedChars(sc, &status));
        TEST_ASSERT(uset_equals(us, uspoof_getAllowedChars(sc, &status)));
        TEST_ASSERT_SUCCESS(status);
        uset_close(us);
    TEST_TEARDOWN;

    /*
    *  clone()
    */

    TEST_SETUP
        USpoofChecker *clone1 = NULL;
        USpoofChecker *clone2 = NULL;
        int32_t        checkResults = 0;
        
        clone1 = uspoof_clone(sc, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_NE(clone1, sc);

        clone2 = uspoof_clone(clone1, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_NE(clone2, clone1);

        uspoof_close(clone1);
        
        /* Verify that the cloned spoof checker is alive */
        checkResults = uspoof_check(clone2, goodLatin, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);

        checkResults = uspoof_check(clone2, scMixed, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_SINGLE_SCRIPT | USPOOF_MIXED_SCRIPT_CONFUSABLE, checkResults);
        uspoof_close(clone2);
    TEST_TEARDOWN;

    /*
     *  get & set Checks
    */
    TEST_SETUP
        int32_t   checks;
        int32_t   checks2;
        int32_t   checkResults;

        checks = uspoof_getChecks(sc, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_ALL_CHECKS, checks);

        checks &= ~(USPOOF_SINGLE_SCRIPT | USPOOF_MIXED_SCRIPT_CONFUSABLE);
        uspoof_setChecks(sc, checks, &status);
        TEST_ASSERT_SUCCESS(status);
        checks2 = uspoof_getChecks(sc, &status);
        TEST_ASSERT_EQ(checks, checks2);

        /* The checks that were disabled just above are the same ones that the "scMixed" test fails.
            So with those tests gone checking that Identifier should now succeed */
        checkResults = uspoof_check(sc, scMixed, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);
    TEST_TEARDOWN;
        
    /*
     *  AllowedLoacles
     */

    TEST_SETUP
        const char  *allowedLocales;
        int32_t  checkResults;

        /* Default allowed locales list should be empty */
        allowedLocales = uspoof_getAllowedLocales(sc, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(strcmp("", allowedLocales) == 0)

        /* Allow en and ru, which should enable Latin and Cyrillic only to pass */
        uspoof_setAllowedLocales(sc, "en, ru_RU", &status);
        TEST_ASSERT_SUCCESS(status);
        allowedLocales = uspoof_getAllowedLocales(sc, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(strstr(allowedLocales, "en") != NULL);
        TEST_ASSERT(strstr(allowedLocales, "ru") != NULL);

        /* Limit checks to USPOOF_CHAR_LIMIT.  Some of the test data has whole script confusables also,
         * which we don't want to see in this test. */
        uspoof_setChecks(sc, USPOOF_CHAR_LIMIT, &status);
        TEST_ASSERT_SUCCESS(status);

        checkResults = uspoof_check(sc, goodLatin, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);
        
        checkResults = uspoof_check(sc, goodGreek, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_CHAR_LIMIT, checkResults);

        checkResults = uspoof_check(sc, goodCyrl, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);

        /* Reset with an empty locale list, which should allow all characters to pass */
        uspoof_setAllowedLocales(sc, " ", &status);
        TEST_ASSERT_SUCCESS(status);

        checkResults = uspoof_check(sc, goodGreek, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);
    TEST_TEARDOWN;

    /*
     * AllowedChars   set/get the USet of allowed characters.
     */
    TEST_SETUP
        const USet  *set;
        USet        *tmpSet;
        int32_t      checkResults;
        
        /* By default, we should see no restriction; the USet should allow all characters. */
        set = uspoof_getAllowedChars(sc, &status);
        TEST_ASSERT_SUCCESS(status);
        tmpSet = uset_open(0, 0x10ffff);
        TEST_ASSERT(uset_equals(tmpSet, set));

        /* Setting the allowed chars should enable the check. */
        uspoof_setChecks(sc, USPOOF_ALL_CHECKS & ~USPOOF_CHAR_LIMIT, &status);
        TEST_ASSERT_SUCCESS(status);

        /* Remove a character that is in our good Latin test identifier from the allowed chars set. */
        uset_remove(tmpSet, goodLatin[1]);
        uspoof_setAllowedChars(sc, tmpSet, &status);
        TEST_ASSERT_SUCCESS(status);
        uset_close(tmpSet);

        /* Latin Identifier should now fail; other non-latin test cases should still be OK */
        checkResults = uspoof_check(sc, goodLatin, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_CHAR_LIMIT, checkResults);

        checkResults = uspoof_check(sc, goodGreek, -1, NULL, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_WHOLE_SCRIPT_CONFUSABLE, checkResults);
    TEST_TEARDOWN;

    /*
     * check UTF-8
     */
    TEST_SETUP
        char    utf8buf[200];
        int32_t checkResults;
        int32_t position;

        u_strToUTF8(utf8buf, sizeof(utf8buf), NULL, goodLatin, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        position = 666;
        checkResults = uspoof_checkUTF8(sc, utf8buf, -1, &position, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);
        TEST_ASSERT_EQ(666, position);

        u_strToUTF8(utf8buf, sizeof(utf8buf), NULL, goodCyrl, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        checkResults = uspoof_checkUTF8(sc, utf8buf, -1, &position, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);

        u_strToUTF8(utf8buf, sizeof(utf8buf), NULL, scMixed, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        position = 666;
        checkResults = uspoof_checkUTF8(sc, utf8buf, -1, &position, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_MIXED_SCRIPT_CONFUSABLE | USPOOF_SINGLE_SCRIPT , checkResults);
        TEST_ASSERT_EQ(2, position);

    TEST_TEARDOWN;

    /*
     * uspoof_areConfusable()
     */
    TEST_SETUP
        int32_t  checkResults;
        
        checkResults = uspoof_areConfusable(sc, scLatin, -1, scMixed, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_MIXED_SCRIPT_CONFUSABLE, checkResults);

        checkResults = uspoof_areConfusable(sc, goodGreek, -1, scLatin, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);

        checkResults = uspoof_areConfusable(sc, lll_Latin_a, -1, lll_Latin_b, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_SINGLE_SCRIPT_CONFUSABLE, checkResults);

    TEST_TEARDOWN;

    /*
     * areConfusableUTF8
     */
    TEST_SETUP
        int32_t checkResults;
        char s1[200];
        char s2[200];


        u_strToUTF8(s1, sizeof(s1), NULL, scLatin, -1, &status);
        u_strToUTF8(s2, sizeof(s2), NULL, scMixed, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        checkResults = uspoof_areConfusableUTF8(sc, s1, -1, s2, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_MIXED_SCRIPT_CONFUSABLE, checkResults);

        u_strToUTF8(s1, sizeof(s1), NULL, goodGreek, -1, &status);
        u_strToUTF8(s2, sizeof(s2), NULL, scLatin, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        checkResults = uspoof_areConfusableUTF8(sc, s1, -1, s2, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, checkResults);
        
        u_strToUTF8(s1, sizeof(s1), NULL, lll_Latin_a, -1, &status);
        u_strToUTF8(s2, sizeof(s2), NULL, lll_Latin_b, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        checkResults = uspoof_areConfusableUTF8(sc, s1, -1, s2, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(USPOOF_SINGLE_SCRIPT_CONFUSABLE, checkResults);

    TEST_TEARDOWN;


  /*
   * getSkeleton
   */

    TEST_SETUP
        UChar dest[100];
        int32_t   skelLength;

        skelLength = uspoof_getSkeleton(sc, USPOOF_ANY_CASE, lll_Latin_a, -1, dest, sizeof(dest)/sizeof(UChar), &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_EQ(0, u_strcmp(lll_Skel, dest));
        TEST_ASSERT_EQ(u_strlen(lll_Skel), skelLength);

        skelLength = uspoof_getSkeletonUTF8(sc, USPOOF_ANY_CASE, goodLatinUTF8, -1, dest, sizeof(dest)/sizeof(UChar), &status);
        TEST_ASSERT_SUCCESS(status);

        skelLength = uspoof_getSkeleton(sc, USPOOF_ANY_CASE, lll_Latin_a, -1, NULL, 0, &status);
        TEST_ASSERT_EQ(U_BUFFER_OVERFLOW_ERROR, status);
        TEST_ASSERT_EQ(3, skelLength);
        status = U_ZERO_ERROR;

    TEST_TEARDOWN;
}