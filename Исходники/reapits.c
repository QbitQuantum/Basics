static void TestRegexCAPI(void) {
    UErrorCode           status = U_ZERO_ERROR;
    URegularExpression  *re;
    UChar                pat[200];
    UChar               *minus1;

    memset(&minus1, -1, sizeof(minus1));

    /* Mimimalist open/close */
    u_uastrncpy(pat, "abc*", sizeof(pat)/2);
    re = uregex_open(pat, -1, 0, 0, &status);
    TEST_ASSERT_SUCCESS(status);
    uregex_close(re);

    /* Open with all flag values set */
    status = U_ZERO_ERROR;
    re = uregex_open(pat, -1, 
        UREGEX_CASE_INSENSITIVE | UREGEX_COMMENTS | UREGEX_DOTALL | UREGEX_MULTILINE | UREGEX_UWORD,
        0, &status);
    TEST_ASSERT_SUCCESS(status);
    uregex_close(re);

    /* Open with an invalid flag */
    status = U_ZERO_ERROR;
    re = uregex_open(pat, -1, 0x40000000, 0, &status);
    TEST_ASSERT(status == U_REGEX_INVALID_FLAG);
    uregex_close(re);

    /* openC with an invalid parameter */
    status = U_ZERO_ERROR;
    re = uregex_openC(NULL,
        UREGEX_CASE_INSENSITIVE | UREGEX_COMMENTS | UREGEX_DOTALL | UREGEX_MULTILINE | UREGEX_UWORD, 0, &status);
    TEST_ASSERT(status == U_ILLEGAL_ARGUMENT_ERROR && re == NULL);

    /* openC with an invalid parameter */
    status = U_USELESS_COLLATOR_ERROR;
    re = uregex_openC(NULL,
        UREGEX_CASE_INSENSITIVE | UREGEX_COMMENTS | UREGEX_DOTALL | UREGEX_MULTILINE | UREGEX_UWORD, 0, &status);
    TEST_ASSERT(status == U_USELESS_COLLATOR_ERROR && re == NULL);

    /* openC   open from a C string */
    {
        const UChar   *p;
        int32_t  len;
        status = U_ZERO_ERROR;
        re = uregex_openC("abc*", 0, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        p = uregex_pattern(re, &len, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS above should change too... */
        if(U_SUCCESS(status)) {
            u_uastrncpy(pat, "abc*", sizeof(pat)/2);
            TEST_ASSERT(u_strcmp(pat, p) == 0);
            TEST_ASSERT(len==(int32_t)strlen("abc*"));
        }

        uregex_close(re);

        /*  TODO:  Open with ParseError parameter */
    }

    /*
     *  clone
     */
    {
        URegularExpression *clone1;
        URegularExpression *clone2;
        URegularExpression *clone3;
        UChar  testString1[30];
        UChar  testString2[30];
        UBool  result;


        status = U_ZERO_ERROR;
        re = uregex_openC("abc*", 0, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        clone1 = uregex_clone(re, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(clone1 != NULL);

        status = U_ZERO_ERROR;
        clone2 = uregex_clone(re, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(clone2 != NULL);
        uregex_close(re);

        status = U_ZERO_ERROR;
        clone3 = uregex_clone(clone2, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(clone3 != NULL);

        u_uastrncpy(testString1, "abcccd", sizeof(pat)/2);
        u_uastrncpy(testString2, "xxxabcccd", sizeof(pat)/2);

        status = U_ZERO_ERROR;
        uregex_setText(clone1, testString1, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        result = uregex_lookingAt(clone1, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(result==TRUE);
        
        status = U_ZERO_ERROR;
        uregex_setText(clone2, testString2, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        result = uregex_lookingAt(clone2, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(result==FALSE);
        result = uregex_find(clone2, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(result==TRUE);

        uregex_close(clone1);
        uregex_close(clone2);
        uregex_close(clone3);

    }

    /*
     *  pattern()
    */
    {
        const UChar  *resultPat;
        int32_t       resultLen;
        u_uastrncpy(pat, "hello", sizeof(pat)/2);
        status = U_ZERO_ERROR;
        re = uregex_open(pat, -1, 0, NULL, &status);
        resultPat = uregex_pattern(re, &resultLen, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS above should change too... */
        if (U_SUCCESS(status)) {
            TEST_ASSERT(resultLen == -1);
            TEST_ASSERT(u_strcmp(resultPat, pat) == 0);
        }

        uregex_close(re);

        status = U_ZERO_ERROR;
        re = uregex_open(pat, 3, 0, NULL, &status);
        resultPat = uregex_pattern(re, &resultLen, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS above should change too... */
        if (U_SUCCESS(status)) {
            TEST_ASSERT(resultLen == 3);
            TEST_ASSERT(u_strncmp(resultPat, pat, 3) == 0);
            TEST_ASSERT(u_strlen(resultPat) == 3);
        }

        uregex_close(re);
    }

    /*
     *  flags()
     */
    {
        int32_t  t;

        status = U_ZERO_ERROR;
        re = uregex_open(pat, -1, 0, NULL, &status);
        t  = uregex_flags(re, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(t == 0);
        uregex_close(re);

        status = U_ZERO_ERROR;
        re = uregex_open(pat, -1, 0, NULL, &status);
        t  = uregex_flags(re, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(t == 0);
        uregex_close(re);

        status = U_ZERO_ERROR;
        re = uregex_open(pat, -1, UREGEX_CASE_INSENSITIVE | UREGEX_DOTALL, NULL, &status);
        t  = uregex_flags(re, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(t == (UREGEX_CASE_INSENSITIVE | UREGEX_DOTALL));
        uregex_close(re);
    }

    /*
     *  setText() and lookingAt()
     */
    {
        UChar  text1[50];
        UChar  text2[50];
        UBool  result;

        u_uastrncpy(text1, "abcccd",  sizeof(text1)/2);
        u_uastrncpy(text2, "abcccxd", sizeof(text2)/2);
        status = U_ZERO_ERROR;
        u_uastrncpy(pat, "abc*d", sizeof(pat)/2);
        re = uregex_open(pat, -1, 0, NULL, &status);
        TEST_ASSERT_SUCCESS(status);

        /* Operation before doing a setText should fail... */
        status = U_ZERO_ERROR;
        uregex_lookingAt(re, 0, &status);
        TEST_ASSERT( status== U_REGEX_INVALID_STATE);

        status = U_ZERO_ERROR;
        uregex_setText(re, text1, -1, &status);
        result = uregex_lookingAt(re, 0, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text2, -1, &status);
        result = uregex_lookingAt(re, 0, &status);
        TEST_ASSERT(result == FALSE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text1, -1, &status);
        result = uregex_lookingAt(re, 0, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text1, 5, &status);
        result = uregex_lookingAt(re, 0, &status);
        TEST_ASSERT(result == FALSE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text1, 6, &status);
        result = uregex_lookingAt(re, 0, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT_SUCCESS(status);

        uregex_close(re);
    }


    /*
     *  getText() 
     */
    {
        UChar    text1[50];
        UChar    text2[50];
        const UChar   *result;
        int32_t  textLength;

        u_uastrncpy(text1, "abcccd",  sizeof(text1)/2);
        u_uastrncpy(text2, "abcccxd", sizeof(text2)/2);
        status = U_ZERO_ERROR;
        u_uastrncpy(pat, "abc*d", sizeof(pat)/2);
        re = uregex_open(pat, -1, 0, NULL, &status);

        uregex_setText(re, text1, -1, &status);
        result = uregex_getText(re, &textLength, &status);
        TEST_ASSERT(result == text1);
        TEST_ASSERT(textLength == -1);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text2, 7, &status);
        result = uregex_getText(re, &textLength, &status);
        TEST_ASSERT(result == text2);
        TEST_ASSERT(textLength == 7);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text2, 4, &status);
        result = uregex_getText(re, &textLength, &status);
        TEST_ASSERT(result == text2);
        TEST_ASSERT(textLength == 4);
        TEST_ASSERT_SUCCESS(status);
        uregex_close(re);
    }

    /*
     *  matches()
     */
    {
        UChar   text1[50];
        UBool   result;
        int     len;
        UChar   nullString[] = {0,0,0};

        u_uastrncpy(text1, "abcccde",  sizeof(text1)/2);
        status = U_ZERO_ERROR;
        u_uastrncpy(pat, "abc*d", sizeof(pat)/2);
        re = uregex_open(pat, -1, 0, NULL, &status);

        uregex_setText(re, text1, -1, &status);
        result = uregex_matches(re, 0, &status);
        TEST_ASSERT(result == FALSE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text1, 6, &status);
        result = uregex_matches(re, 0, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, text1, 6, &status);
        result = uregex_matches(re, 1, &status);
        TEST_ASSERT(result == FALSE);
        TEST_ASSERT_SUCCESS(status);
        uregex_close(re);

        status = U_ZERO_ERROR;
        re = uregex_openC(".?", 0, NULL, &status);
        uregex_setText(re, text1, -1, &status);
        len = u_strlen(text1);
        result = uregex_matches(re, len, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_setText(re, nullString, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        result = uregex_matches(re, 0, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT_SUCCESS(status);
        uregex_close(re);
    }


    /*
     *  lookingAt()    Used in setText test.
     */


    /*
     *  find(), findNext, start, end, reset
     */
    {
        UChar    text1[50];
        UBool    result;
        u_uastrncpy(text1, "012rx5rx890rxrx...",  sizeof(text1)/2);
        status = U_ZERO_ERROR;
        re = uregex_openC("rx", 0, NULL, &status);

        uregex_setText(re, text1, -1, &status);
        result = uregex_find(re, 0, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 3);
        TEST_ASSERT(uregex_end(re, 0, &status) == 5);
        TEST_ASSERT_SUCCESS(status);

        result = uregex_find(re, 9, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 11);
        TEST_ASSERT(uregex_end(re, 0, &status) == 13);
        TEST_ASSERT_SUCCESS(status);

        result = uregex_find(re, 14, &status);
        TEST_ASSERT(result == FALSE);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_reset(re, 0, &status);

        result = uregex_findNext(re, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 3);
        TEST_ASSERT(uregex_end(re, 0, &status) == 5);
        TEST_ASSERT_SUCCESS(status);

        result = uregex_findNext(re, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 6);
        TEST_ASSERT(uregex_end(re, 0, &status) == 8);
        TEST_ASSERT_SUCCESS(status);

        status = U_ZERO_ERROR;
        uregex_reset(re, 12, &status);

        result = uregex_findNext(re, &status);
        TEST_ASSERT(result == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 13);
        TEST_ASSERT(uregex_end(re, 0, &status) == 15);
        TEST_ASSERT_SUCCESS(status);

        result = uregex_findNext(re, &status);
        TEST_ASSERT(result == FALSE);
        TEST_ASSERT_SUCCESS(status);

        uregex_close(re);
    }

    /*
     *  groupCount
     */
    {
        int32_t result;

        status = U_ZERO_ERROR;
        re = uregex_openC("abc", 0, NULL, &status);
        result = uregex_groupCount(re, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(result == 0);
        uregex_close(re);

        status = U_ZERO_ERROR;
        re = uregex_openC("abc(def)(ghi(j))", 0, NULL, &status);
        result = uregex_groupCount(re, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(result == 3);
        uregex_close(re);

    }


    /*
     *  group()
     */
    {
        UChar    text1[80];
        UChar    buf[80];
        UBool    result;
        int32_t  resultSz;
        u_uastrncpy(text1, "noise abc interior def, and this is off the end",  sizeof(text1)/2);

        status = U_ZERO_ERROR;
        re = uregex_openC("abc(.*?)def", 0, NULL, &status);
        TEST_ASSERT_SUCCESS(status);


        uregex_setText(re, text1, -1, &status);
        result = uregex_find(re, 0, &status);
        TEST_ASSERT(result==TRUE);

        /*  Capture Group 0, the full match.  Should succeed.  */
        status = U_ZERO_ERROR;
        resultSz = uregex_group(re, 0, buf, sizeof(buf)/2, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING("abc interior def", buf, TRUE);
        TEST_ASSERT(resultSz == (int32_t)strlen("abc interior def"));

        /*  Capture group #1.  Should succeed. */
        status = U_ZERO_ERROR;
        resultSz = uregex_group(re, 1, buf, sizeof(buf)/2, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING(" interior ", buf, TRUE);
        TEST_ASSERT(resultSz == (int32_t)strlen(" interior "));

        /*  Capture group out of range.  Error. */
        status = U_ZERO_ERROR;
        uregex_group(re, 2, buf, sizeof(buf)/2, &status);
        TEST_ASSERT(status == U_INDEX_OUTOFBOUNDS_ERROR);

        /* NULL buffer, pure pre-flight */
        status = U_ZERO_ERROR;
        resultSz = uregex_group(re, 0, NULL, 0, &status);
        TEST_ASSERT(status == U_BUFFER_OVERFLOW_ERROR);
        TEST_ASSERT(resultSz == (int32_t)strlen("abc interior def"));

        /* Too small buffer, truncated string */
        status = U_ZERO_ERROR;
        memset(buf, -1, sizeof(buf));
        resultSz = uregex_group(re, 0, buf, 5, &status);
        TEST_ASSERT(status == U_BUFFER_OVERFLOW_ERROR);
        TEST_ASSERT_STRING("abc i", buf, FALSE);
        TEST_ASSERT(buf[5] == (UChar)0xffff);
        TEST_ASSERT(resultSz == (int32_t)strlen("abc interior def"));

        /* Output string just fits buffer, no NUL term. */
        status = U_ZERO_ERROR;
        resultSz = uregex_group(re, 0, buf, (int32_t)strlen("abc interior def"), &status);
        TEST_ASSERT(status == U_STRING_NOT_TERMINATED_WARNING);
        TEST_ASSERT_STRING("abc interior def", buf, FALSE);
        TEST_ASSERT(resultSz == (int32_t)strlen("abc interior def"));
        TEST_ASSERT(buf[strlen("abc interior def")] == (UChar)0xffff);
        
        uregex_close(re);

    }
    
    /*
     *  Regions
     */
        
        
        /* SetRegion(), getRegion() do something  */
        TEST_SETUP(".*", "0123456789ABCDEF", 0)
        UChar resultString[40];
        TEST_ASSERT(uregex_regionStart(re, &status) == 0);
        TEST_ASSERT(uregex_regionEnd(re, &status) == 16);
        uregex_setRegion(re, 3, 6, &status);
        TEST_ASSERT(uregex_regionStart(re, &status) == 3);
        TEST_ASSERT(uregex_regionEnd(re, &status) == 6);
        TEST_ASSERT(uregex_findNext(re, &status));
        TEST_ASSERT(uregex_group(re, 0, resultString, sizeof(resultString)/2, &status) == 3)
        TEST_ASSERT_STRING("345", resultString, TRUE);
        TEST_TEARDOWN;
        
        /* find(start=-1) uses regions   */
        TEST_SETUP(".*", "0123456789ABCDEF", 0);
        uregex_setRegion(re, 4, 6, &status);
        TEST_ASSERT(uregex_find(re, -1, &status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 4);
        TEST_ASSERT(uregex_end(re, 0, &status) == 6);
        TEST_TEARDOWN;
        
        /* find (start >=0) does not use regions   */
        TEST_SETUP(".*", "0123456789ABCDEF", 0);
        uregex_setRegion(re, 4, 6, &status);
        TEST_ASSERT(uregex_find(re, 0, &status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 0);
        TEST_ASSERT(uregex_end(re, 0, &status) == 16);
        TEST_TEARDOWN;
         
        /* findNext() obeys regions    */
        TEST_SETUP(".", "0123456789ABCDEF", 0);
        uregex_setRegion(re, 4, 6, &status);
        TEST_ASSERT(uregex_findNext(re,&status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 4);
        TEST_ASSERT(uregex_findNext(re, &status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 5);
        TEST_ASSERT(uregex_findNext(re, &status) == FALSE);
        TEST_TEARDOWN;

        /* matches(start=-1) uses regions                                           */
        /*    Also, verify that non-greedy *? succeeds in finding the full match.   */
        TEST_SETUP(".*?", "0123456789ABCDEF", 0);
        uregex_setRegion(re, 4, 6, &status);
        TEST_ASSERT(uregex_matches(re, -1, &status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 4);
        TEST_ASSERT(uregex_end(re, 0, &status) == 6);
        TEST_TEARDOWN;
        
        /* matches (start >=0) does not use regions       */
        TEST_SETUP(".*?", "0123456789ABCDEF", 0);
        uregex_setRegion(re, 4, 6, &status);
        TEST_ASSERT(uregex_matches(re, 0, &status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 0);
        TEST_ASSERT(uregex_end(re, 0, &status) == 16);
        TEST_TEARDOWN;
        
        /* lookingAt(start=-1) uses regions                                         */
        /*    Also, verify that non-greedy *? finds the first (shortest) match.     */
        TEST_SETUP(".*?", "0123456789ABCDEF", 0);
        uregex_setRegion(re, 4, 6, &status);
        TEST_ASSERT(uregex_lookingAt(re, -1, &status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 4);
        TEST_ASSERT(uregex_end(re, 0, &status) == 4);
        TEST_TEARDOWN;
        
        /* lookingAt (start >=0) does not use regions  */
        TEST_SETUP(".*?", "0123456789ABCDEF", 0);
        uregex_setRegion(re, 4, 6, &status);
        TEST_ASSERT(uregex_lookingAt(re, 0, &status) == TRUE);
        TEST_ASSERT(uregex_start(re, 0, &status) == 0);
        TEST_ASSERT(uregex_end(re, 0, &status) == 0);
        TEST_TEARDOWN;

        /* hitEnd()       */
        TEST_SETUP("[a-f]*", "abcdefghij", 0);
        TEST_ASSERT(uregex_find(re, 0, &status) == TRUE);
        TEST_ASSERT(uregex_hitEnd(re, &status) == FALSE);
        TEST_TEARDOWN;

        TEST_SETUP("[a-f]*", "abcdef", 0);
        TEST_ASSERT(uregex_find(re, 0, &status) == TRUE);
        TEST_ASSERT(uregex_hitEnd(re, &status) == TRUE);
        TEST_TEARDOWN;

        /* requireEnd   */
        TEST_SETUP("abcd", "abcd", 0);
        TEST_ASSERT(uregex_find(re, 0, &status) == TRUE);
        TEST_ASSERT(uregex_requireEnd(re, &status) == FALSE);
        TEST_TEARDOWN;

        TEST_SETUP("abcd$", "abcd", 0);
        TEST_ASSERT(uregex_find(re, 0, &status) == TRUE);
        TEST_ASSERT(uregex_requireEnd(re, &status) == TRUE);
        TEST_TEARDOWN;
        
        /* anchoringBounds        */
        TEST_SETUP("abc$", "abcdef", 0);
        TEST_ASSERT(uregex_hasAnchoringBounds(re, &status) == TRUE);
        uregex_useAnchoringBounds(re, FALSE, &status);
        TEST_ASSERT(uregex_hasAnchoringBounds(re, &status) == FALSE);
        
        TEST_ASSERT(uregex_find(re, -1, &status) == FALSE);
        uregex_useAnchoringBounds(re, TRUE, &status);
        uregex_setRegion(re, 0, 3, &status);
        TEST_ASSERT(uregex_find(re, -1, &status) == TRUE);
        TEST_ASSERT(uregex_end(re, 0, &status) == 3);
        TEST_TEARDOWN;
        
        /* Transparent Bounds      */
        TEST_SETUP("abc(?=def)", "abcdef", 0);
        TEST_ASSERT(uregex_hasTransparentBounds(re, &status) == FALSE);
        uregex_useTransparentBounds(re, TRUE, &status);
        TEST_ASSERT(uregex_hasTransparentBounds(re, &status) == TRUE);
        
        uregex_useTransparentBounds(re, FALSE, &status);
        TEST_ASSERT(uregex_find(re, -1, &status) == TRUE);    /* No Region */
        uregex_setRegion(re, 0, 3, &status);
        TEST_ASSERT(uregex_find(re, -1, &status) == FALSE);   /* with region, opaque bounds */
        uregex_useTransparentBounds(re, TRUE, &status);
        TEST_ASSERT(uregex_find(re, -1, &status) == TRUE);    /* with region, transparent bounds */
        TEST_ASSERT(uregex_end(re, 0, &status) == 3);
        TEST_TEARDOWN;
        

    /*
     *  replaceFirst()
     */
    {
        UChar    text1[80];
        UChar    text2[80];
        UChar    replText[80];
        UChar    buf[80];
        int32_t  resultSz;
        u_uastrncpy(text1, "Replace xaax x1x x...x.",  sizeof(text1)/2);
        u_uastrncpy(text2, "No match here.",  sizeof(text2)/2);
        u_uastrncpy(replText, "<$1>", sizeof(replText)/2);

        status = U_ZERO_ERROR;
        re = uregex_openC("x(.*?)x", 0, NULL, &status);
        TEST_ASSERT_SUCCESS(status);

        /*  Normal case, with match */
        uregex_setText(re, text1, -1, &status);
        resultSz = uregex_replaceFirst(re, replText, -1, buf, sizeof(buf)/2, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING("Replace <aa> x1x x...x.", buf, TRUE);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace xaax x1x x...x."));

        /* No match.  Text should copy to output with no changes.  */
        status = U_ZERO_ERROR;
        uregex_setText(re, text2, -1, &status);
        resultSz = uregex_replaceFirst(re, replText, -1, buf, sizeof(buf)/2, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING("No match here.", buf, TRUE);
        TEST_ASSERT(resultSz == (int32_t)strlen("No match here."));

        /*  Match, output just fills buffer, no termination warning. */
        status = U_ZERO_ERROR;
        uregex_setText(re, text1, -1, &status);
        memset(buf, -1, sizeof(buf));
        resultSz = uregex_replaceFirst(re, replText, -1, buf, strlen("Replace <aa> x1x x...x."), &status);
        TEST_ASSERT(status == U_STRING_NOT_TERMINATED_WARNING);
        TEST_ASSERT_STRING("Replace <aa> x1x x...x.", buf, FALSE);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace xaax x1x x...x."));
        TEST_ASSERT(buf[resultSz] == (UChar)0xffff);

        /* Do the replaceFirst again, without first resetting anything.
         *  Should give the same results.
         */
        status = U_ZERO_ERROR;
        memset(buf, -1, sizeof(buf));
        resultSz = uregex_replaceFirst(re, replText, -1, buf, strlen("Replace <aa> x1x x...x."), &status);
        TEST_ASSERT(status == U_STRING_NOT_TERMINATED_WARNING);
        TEST_ASSERT_STRING("Replace <aa> x1x x...x.", buf, FALSE);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace xaax x1x x...x."));
        TEST_ASSERT(buf[resultSz] == (UChar)0xffff);

        /* NULL buffer, zero buffer length */
        status = U_ZERO_ERROR;
        resultSz = uregex_replaceFirst(re, replText, -1, NULL, 0, &status);
        TEST_ASSERT(status == U_BUFFER_OVERFLOW_ERROR);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace xaax x1x x...x."));

        /* Buffer too small by one */
        status = U_ZERO_ERROR;
        memset(buf, -1, sizeof(buf));
        resultSz = uregex_replaceFirst(re, replText, -1, buf, strlen("Replace <aa> x1x x...x.")-1, &status);
        TEST_ASSERT(status == U_BUFFER_OVERFLOW_ERROR);
        TEST_ASSERT_STRING("Replace <aa> x1x x...x", buf, FALSE);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace xaax x1x x...x."));
        TEST_ASSERT(buf[resultSz] == (UChar)0xffff);

        uregex_close(re);
    }


    /*
     *  replaceAll()
     */
    {
        UChar    text1[80];
        UChar    text2[80];
        UChar    replText[80];
        UChar    buf[80];
        int32_t  resultSz;
        int32_t  expectedResultSize;
        int32_t  i;

        u_uastrncpy(text1, "Replace xaax x1x x...x.",  sizeof(text1)/2);
        u_uastrncpy(text2, "No match here.",  sizeof(text2)/2);
        u_uastrncpy(replText, "<$1>", sizeof(replText)/2);
        expectedResultSize = u_strlen(text1);

        status = U_ZERO_ERROR;
        re = uregex_openC("x(.*?)x", 0, NULL, &status);
        TEST_ASSERT_SUCCESS(status);

        /*  Normal case, with match */
        uregex_setText(re, text1, -1, &status);
        resultSz = uregex_replaceAll(re, replText, -1, buf, sizeof(buf)/2, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING("Replace <aa> <1> <...>.", buf, TRUE);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace xaax x1x x...x."));

        /* No match.  Text should copy to output with no changes.  */
        status = U_ZERO_ERROR;
        uregex_setText(re, text2, -1, &status);
        resultSz = uregex_replaceAll(re, replText, -1, buf, sizeof(buf)/2, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING("No match here.", buf, TRUE);
        TEST_ASSERT(resultSz == (int32_t)strlen("No match here."));

        /*  Match, output just fills buffer, no termination warning. */
        status = U_ZERO_ERROR;
        uregex_setText(re, text1, -1, &status);
        memset(buf, -1, sizeof(buf));
        resultSz = uregex_replaceAll(re, replText, -1, buf, strlen("Replace xaax x1x x...x."), &status);
        TEST_ASSERT(status == U_STRING_NOT_TERMINATED_WARNING);
        TEST_ASSERT_STRING("Replace <aa> <1> <...>.", buf, FALSE);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace <aa> <1> <...>."));
        TEST_ASSERT(buf[resultSz] == (UChar)0xffff);

        /* Do the replaceFirst again, without first resetting anything.
         *  Should give the same results.
         */
        status = U_ZERO_ERROR;
        memset(buf, -1, sizeof(buf));
        resultSz = uregex_replaceAll(re, replText, -1, buf, strlen("Replace xaax x1x x...x."), &status);
        TEST_ASSERT(status == U_STRING_NOT_TERMINATED_WARNING);
        TEST_ASSERT_STRING("Replace <aa> <1> <...>.", buf, FALSE);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace <aa> <1> <...>."));
        TEST_ASSERT(buf[resultSz] == (UChar)0xffff);

        /* NULL buffer, zero buffer length */
        status = U_ZERO_ERROR;
        resultSz = uregex_replaceAll(re, replText, -1, NULL, 0, &status);
        TEST_ASSERT(status == U_BUFFER_OVERFLOW_ERROR);
        TEST_ASSERT(resultSz == (int32_t)strlen("Replace <aa> <1> <...>."));

        /* Buffer too small.  Try every size, which will tickle edge cases
         * in uregex_appendReplacement (used by replaceAll)   */
        for (i=0; i<expectedResultSize; i++) {
            char  expected[80];
            status = U_ZERO_ERROR;
            memset(buf, -1, sizeof(buf));
            resultSz = uregex_replaceAll(re, replText, -1, buf, i, &status);
            TEST_ASSERT(status == U_BUFFER_OVERFLOW_ERROR);
            strcpy(expected, "Replace <aa> <1> <...>.");
            expected[i] = 0;
            TEST_ASSERT_STRING(expected, buf, FALSE);
            TEST_ASSERT(resultSz == expectedResultSize);
            TEST_ASSERT(buf[i] == (UChar)0xffff);
        }

        uregex_close(re);
    }


    /*
     *  appendReplacement()
     */
    {
        UChar    text[100];
        UChar    repl[100];
        UChar    buf[100];
        UChar   *bufPtr;
        int32_t  bufCap;


        status = U_ZERO_ERROR;
        re = uregex_openC(".*", 0, 0, &status);
        TEST_ASSERT_SUCCESS(status);

        u_uastrncpy(text, "whatever",  sizeof(text)/2);
        u_uastrncpy(repl, "some other", sizeof(repl)/2);
        uregex_setText(re, text, -1, &status);

        /* match covers whole target string */
        uregex_find(re, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        bufPtr = buf;
        bufCap = sizeof(buf) / 2;
        uregex_appendReplacement(re, repl, -1, &bufPtr, &bufCap, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING("some other", buf, TRUE);

        /* Match has \u \U escapes */
        uregex_find(re, 0, &status);
        TEST_ASSERT_SUCCESS(status);
        bufPtr = buf;
        bufCap = sizeof(buf) / 2;
        u_uastrncpy(repl, "abc\\u0041\\U00000042 \\\\ $ \\abc", sizeof(repl)/2);
        uregex_appendReplacement(re, repl, -1, &bufPtr, &bufCap, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT_STRING("abcAB \\ $ abc", buf, TRUE); 

        uregex_close(re);
    }


    /*
     *  appendTail().   Checked in ReplaceFirst(), replaceAll().
     */

    /*
     *  split()
     */
    {
        UChar    textToSplit[80];
        UChar    text2[80];
        UChar    buf[200];
        UChar    *fields[10];
        int32_t  numFields;
        int32_t  requiredCapacity;
        int32_t  spaceNeeded;
        int32_t  sz;

        u_uastrncpy(textToSplit, "first : second:  third",  sizeof(textToSplit)/2);
        u_uastrncpy(text2, "No match here.",  sizeof(text2)/2);

        status = U_ZERO_ERROR;
        re = uregex_openC(":", 0, NULL, &status);


        /*  Simple split */ 

        uregex_setText(re, textToSplit, -1, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS call above should change too... */
        if (U_SUCCESS(status)) {
            memset(fields, -1, sizeof(fields));
            numFields = 
                uregex_split(re, buf, sizeof(buf)/2, &requiredCapacity, fields, 10, &status);
            TEST_ASSERT_SUCCESS(status);

            /* The TEST_ASSERT_SUCCESS call above should change too... */
            if(U_SUCCESS(status)) {
                TEST_ASSERT(numFields == 3);
                TEST_ASSERT_STRING("first ",  fields[0], TRUE);
                TEST_ASSERT_STRING(" second", fields[1], TRUE);
                TEST_ASSERT_STRING("  third", fields[2], TRUE);
                TEST_ASSERT(fields[3] == NULL);

                spaceNeeded = u_strlen(textToSplit) -
                            (numFields - 1)  +  /* Field delimiters do not appear in output */
                            numFields;          /* Each field gets a NUL terminator */ 

                TEST_ASSERT(spaceNeeded == requiredCapacity);
            }
        }

        uregex_close(re);

    
        /*  Split with too few output strings available */
        status = U_ZERO_ERROR;
        re = uregex_openC(":", 0, NULL, &status);
        uregex_setText(re, textToSplit, -1, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS call above should change too... */
        if(U_SUCCESS(status)) {
            memset(fields, -1, sizeof(fields));
            numFields = 
                uregex_split(re, buf, sizeof(buf)/2, &requiredCapacity, fields, 2, &status);
            TEST_ASSERT_SUCCESS(status);

            /* The TEST_ASSERT_SUCCESS call above should change too... */
            if(U_SUCCESS(status)) {
                TEST_ASSERT(numFields == 2);
                TEST_ASSERT_STRING("first ",  fields[0], TRUE);
                TEST_ASSERT_STRING(" second:  third", fields[1], TRUE);
                TEST_ASSERT(!memcmp(&fields[2],&minus1,sizeof(UChar*)));

                spaceNeeded = u_strlen(textToSplit) -
                            (numFields - 1)  +  /* Field delimiters do not appear in output */
                            numFields;          /* Each field gets a NUL terminator */ 

                TEST_ASSERT(spaceNeeded == requiredCapacity);

                /* Split with a range of output buffer sizes.  */
                spaceNeeded = u_strlen(textToSplit) -
                    (numFields - 1)  +  /* Field delimiters do not appear in output */
                    numFields;          /* Each field gets a NUL terminator */ 
                        
                for (sz=0; sz < spaceNeeded+1; sz++) {
                    memset(fields, -1, sizeof(fields));
                    status = U_ZERO_ERROR;
                    numFields = 
                        uregex_split(re, buf, sz, &requiredCapacity, fields, 10, &status);
                    if (sz >= spaceNeeded) {
                        TEST_ASSERT_SUCCESS(status);
                        TEST_ASSERT_STRING("first ",  fields[0], TRUE);
                        TEST_ASSERT_STRING(" second", fields[1], TRUE);
                        TEST_ASSERT_STRING("  third", fields[2], TRUE);
                    } else {
                        TEST_ASSERT(status == U_BUFFER_OVERFLOW_ERROR);
                    }
                    TEST_ASSERT(numFields == 3);
                    TEST_ASSERT(fields[3] == NULL);
                    TEST_ASSERT(spaceNeeded == requiredCapacity);
                }
            }
        }

        uregex_close(re);
    }




    /* Split(), part 2.  Patterns with capture groups.  The capture group text
     *                   comes out as additional fields.  */
    {
        UChar    textToSplit[80];
        UChar    buf[200];
        UChar    *fields[10];
        int32_t  numFields;
        int32_t  requiredCapacity;
        int32_t  spaceNeeded;
        int32_t  sz;

        u_uastrncpy(textToSplit, "first <tag-a> second<tag-b>  third",  sizeof(textToSplit)/2);

        status = U_ZERO_ERROR;
        re = uregex_openC("<(.*?)>", 0, NULL, &status);

        uregex_setText(re, textToSplit, -1, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS call above should change too... */
        if(U_SUCCESS(status)) {
            memset(fields, -1, sizeof(fields));
            numFields = 
                uregex_split(re, buf, sizeof(buf)/2, &requiredCapacity, fields, 10, &status);
            TEST_ASSERT_SUCCESS(status);

            /* The TEST_ASSERT_SUCCESS call above should change too... */
            if(U_SUCCESS(status)) {
                TEST_ASSERT(numFields == 5);
                TEST_ASSERT_STRING("first ",  fields[0], TRUE);
                TEST_ASSERT_STRING("tag-a",   fields[1], TRUE);
                TEST_ASSERT_STRING(" second", fields[2], TRUE);
                TEST_ASSERT_STRING("tag-b",   fields[3], TRUE);
                TEST_ASSERT_STRING("  third", fields[4], TRUE);
                TEST_ASSERT(fields[5] == NULL);
                spaceNeeded = strlen("first .tag-a. second.tag-b.  third.");  /* "." at NUL positions */
                TEST_ASSERT(spaceNeeded == requiredCapacity);
            }
        }
    
        /*  Split with too few output strings available (2) */
        status = U_ZERO_ERROR;
        memset(fields, -1, sizeof(fields));
        numFields = 
            uregex_split(re, buf, sizeof(buf)/2, &requiredCapacity, fields, 2, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS call above should change too... */
        if(U_SUCCESS(status)) {
            TEST_ASSERT(numFields == 2);
            TEST_ASSERT_STRING("first ",  fields[0], TRUE);
            TEST_ASSERT_STRING(" second<tag-b>  third", fields[1], TRUE);
            TEST_ASSERT(!memcmp(&fields[2],&minus1,sizeof(UChar*)));

            spaceNeeded = strlen("first . second<tag-b>  third.");  /* "." at NUL positions */
            TEST_ASSERT(spaceNeeded == requiredCapacity);
        }

        /*  Split with too few output strings available (3) */
        status = U_ZERO_ERROR;
        memset(fields, -1, sizeof(fields));
        numFields = 
            uregex_split(re, buf, sizeof(buf)/2, &requiredCapacity, fields, 3, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS call above should change too... */
        if(U_SUCCESS(status)) {
            TEST_ASSERT(numFields == 3);
            TEST_ASSERT_STRING("first ",  fields[0], TRUE);
            TEST_ASSERT_STRING("tag-a",   fields[1], TRUE);
            TEST_ASSERT_STRING(" second<tag-b>  third", fields[2], TRUE);
            TEST_ASSERT(!memcmp(&fields[3],&minus1,sizeof(UChar*)));

            spaceNeeded = strlen("first .tag-a. second<tag-b>  third.");  /* "." at NUL positions */
            TEST_ASSERT(spaceNeeded == requiredCapacity);
        }

        /*  Split with just enough output strings available (5) */
        status = U_ZERO_ERROR;
        memset(fields, -1, sizeof(fields));
        numFields = 
            uregex_split(re, buf, sizeof(buf)/2, &requiredCapacity, fields, 5, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS call above should change too... */
        if(U_SUCCESS(status)) {
            TEST_ASSERT(numFields == 5);
            TEST_ASSERT_STRING("first ",  fields[0], TRUE);
            TEST_ASSERT_STRING("tag-a",   fields[1], TRUE);
            TEST_ASSERT_STRING(" second", fields[2], TRUE);
            TEST_ASSERT_STRING("tag-b",   fields[3], TRUE);
            TEST_ASSERT_STRING("  third", fields[4], TRUE);
            TEST_ASSERT(!memcmp(&fields[5],&minus1,sizeof(UChar*)));

            spaceNeeded = strlen("first .tag-a. second.tag-b.  third.");  /* "." at NUL positions */
            TEST_ASSERT(spaceNeeded == requiredCapacity);
        }

        /* Split, end of text is a field delimiter.   */
        status = U_ZERO_ERROR;
        sz = strlen("first <tag-a> second<tag-b>");
        uregex_setText(re, textToSplit, sz, &status);
        TEST_ASSERT_SUCCESS(status);

        /* The TEST_ASSERT_SUCCESS call above should change too... */
        if(U_SUCCESS(status)) {
            memset(fields, -1, sizeof(fields));
            numFields = 
                uregex_split(re, buf, sizeof(buf)/2, &requiredCapacity, fields, 9, &status);
            TEST_ASSERT_SUCCESS(status);

            /* The TEST_ASSERT_SUCCESS call above should change too... */
            if(U_SUCCESS(status)) {
                TEST_ASSERT(numFields == 4);
                TEST_ASSERT_STRING("first ",  fields[0], TRUE);
                TEST_ASSERT_STRING("tag-a",   fields[1], TRUE);
                TEST_ASSERT_STRING(" second", fields[2], TRUE);
                TEST_ASSERT_STRING("tag-b",   fields[3], TRUE);
                TEST_ASSERT(fields[4] == NULL);
                TEST_ASSERT(fields[8] == NULL);
                TEST_ASSERT(!memcmp(&fields[9],&minus1,sizeof(UChar*)));
                spaceNeeded = strlen("first .tag-a. second.tag-b.");  /* "." at NUL positions */
                TEST_ASSERT(spaceNeeded == requiredCapacity);
            }
        }

        uregex_close(re);
    }

}