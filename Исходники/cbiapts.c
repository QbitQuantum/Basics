static void TestBreakIteratorRefresh(void) {
    /*
     *  RefreshInput changes out the input of a Break Iterator without
     *    changing anything else in the iterator's state.  Used with Java JNI,
     *    when Java moves the underlying string storage.   This test
     *    runs a ubrk_next() repeatedly, moving the text in the middle of the sequence.
     *    The right set of boundaries should still be found.
     */
    UChar testStr[]  = {0x20, 0x41, 0x20, 0x42, 0x20, 0x43, 0x20, 0x44, 0x0};  /* = " A B C D"  */
    UChar movedStr[] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,  0};
    UErrorCode status = U_ZERO_ERROR;
    UBreakIterator *bi;
    UText ut1 = UTEXT_INITIALIZER;
    UText ut2 = UTEXT_INITIALIZER;
    
    bi = ubrk_open(UBRK_LINE, "en_US", NULL, 0, &status);
    TEST_ASSERT_SUCCESS(status);
    if (U_FAILURE(status)) {
        return;
    }

    utext_openUChars(&ut1, testStr, -1, &status);
    TEST_ASSERT_SUCCESS(status);
    ubrk_setUText(bi, &ut1, &status);
    TEST_ASSERT_SUCCESS(status);

    if (U_SUCCESS(status)) {
        /* Line boundaries will occur before each letter in the original string */
        TEST_ASSERT(1 == ubrk_next(bi));
        TEST_ASSERT(3 == ubrk_next(bi));

        /* Move the string, kill the original string.  */
        u_strcpy(movedStr, testStr);
        u_memset(testStr, 0x20, u_strlen(testStr));
        utext_openUChars(&ut2, movedStr, -1, &status);
        TEST_ASSERT_SUCCESS(status);
        ubrk_refreshUText(bi, &ut2, &status);
        TEST_ASSERT_SUCCESS(status);
    
        /* Find the following matches, now working in the moved string. */
        TEST_ASSERT(5 == ubrk_next(bi));
        TEST_ASSERT(7 == ubrk_next(bi));
        TEST_ASSERT(8 == ubrk_next(bi));
        TEST_ASSERT(UBRK_DONE == ubrk_next(bi));
        TEST_ASSERT_SUCCESS(status);

        utext_close(&ut1);
        utext_close(&ut2);
    }
    ubrk_close(bi);
}