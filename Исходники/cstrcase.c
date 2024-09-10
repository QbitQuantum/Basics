/* Try titlecasing with options. */
static void
TestUCaseMapToTitle(void) {
    /* "a 'CaT. A 'dOg! 'eTc." where '=U+02BB */
    /*
     * Note: The sentence BreakIterator does not recognize a '.'
     * as a sentence terminator if it is followed by lowercase.
     * That is why the example has the '!'.
     */
    static const UChar

    beforeTitle[]=      { 0x61, 0x20, 0x2bb, 0x43, 0x61, 0x54, 0x2e, 0x20, 0x41, 0x20, 0x2bb, 0x64, 0x4f, 0x67, 0x21, 0x20, 0x2bb, 0x65, 0x54, 0x63, 0x2e },
    titleWord[]=        { 0x41, 0x20, 0x2bb, 0x43, 0x61, 0x74, 0x2e, 0x20, 0x41, 0x20, 0x2bb, 0x44, 0x6f, 0x67, 0x21, 0x20, 0x2bb, 0x45, 0x74, 0x63, 0x2e },
    titleWordNoAdjust[]={ 0x41, 0x20, 0x2bb, 0x63, 0x61, 0x74, 0x2e, 0x20, 0x41, 0x20, 0x2bb, 0x64, 0x6f, 0x67, 0x21, 0x20, 0x2bb, 0x65, 0x74, 0x63, 0x2e },
    titleSentNoLower[]= { 0x41, 0x20, 0x2bb, 0x43, 0x61, 0x54, 0x2e, 0x20, 0x41, 0x20, 0x2bb, 0x64, 0x4f, 0x67, 0x21, 0x20, 0x2bb, 0x45, 0x54, 0x63, 0x2e };

    UChar buffer[32];
    UCaseMap *csm;
    UBreakIterator *sentenceIter;
    const UBreakIterator *iter;
    int32_t length;
    UErrorCode errorCode;

    errorCode=U_ZERO_ERROR;
    csm=ucasemap_open("", 0, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("ucasemap_open(\"\") failed - %s\n", u_errorName(errorCode));
        return;
    }

    iter=ucasemap_getBreakIterator(csm);
    if(iter!=NULL) {
        log_err("ucasemap_getBreakIterator() returns %p!=NULL before setting any iterator or titlecasing\n", iter);
    }

    /* Use default UBreakIterator: Word breaks. */
    length=ucasemap_toTitle(csm, buffer, UPRV_LENGTHOF(buffer), beforeTitle, UPRV_LENGTHOF(beforeTitle), &errorCode);
    if( U_FAILURE(errorCode) ||
        length!=UPRV_LENGTHOF(titleWord) ||
        0!=u_memcmp(buffer, titleWord, length) ||
        buffer[length]!=0
    ) {
        log_err_status(errorCode, "ucasemap_toTitle(default iterator)=%ld failed - %s\n", (long)length, u_errorName(errorCode));
    }
    if (U_SUCCESS(errorCode)) {
        iter=ucasemap_getBreakIterator(csm);
        if(iter==NULL) {
            log_err("ucasemap_getBreakIterator() returns NULL after titlecasing\n");
        }
    }

    /* Try U_TITLECASE_NO_BREAK_ADJUSTMENT. */
    ucasemap_setOptions(csm, U_TITLECASE_NO_BREAK_ADJUSTMENT, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err_status(errorCode, "error: ucasemap_setOptions(U_TITLECASE_NO_BREAK_ADJUSTMENT) failed - %s\n", u_errorName(errorCode));
        return;
    }

    length=ucasemap_toTitle(csm, buffer, UPRV_LENGTHOF(buffer), beforeTitle, UPRV_LENGTHOF(beforeTitle), &errorCode);
    if( U_FAILURE(errorCode) ||
        length!=UPRV_LENGTHOF(titleWordNoAdjust) ||
        0!=u_memcmp(buffer, titleWordNoAdjust, length) ||
        buffer[length]!=0
    ) {
        log_err("ucasemap_toTitle(default iterator, no break adjustment)=%ld failed - %s\n", (long)length, u_errorName(errorCode));
    }

    /* Set a sentence break iterator. */
    errorCode=U_ZERO_ERROR;
    sentenceIter=ubrk_open(UBRK_SENTENCE, "", NULL, 0, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("error: ubrk_open(UBRK_SENTENCE) failed - %s\n", u_errorName(errorCode));
        ucasemap_close(csm);
        return;
    }
    ucasemap_setBreakIterator(csm, sentenceIter, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("error: ucasemap_setBreakIterator(sentence iterator) failed - %s\n", u_errorName(errorCode));
        ubrk_close(sentenceIter);
        ucasemap_close(csm);
        return;
    }
    iter=ucasemap_getBreakIterator(csm);
    if(iter!=sentenceIter) {
        log_err("ucasemap_getBreakIterator() returns %p!=%p after setting the iterator\n", iter, sentenceIter);
    }

    ucasemap_setOptions(csm, U_TITLECASE_NO_LOWERCASE, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("error: ucasemap_setOptions(U_TITLECASE_NO_LOWERCASE) failed - %s\n", u_errorName(errorCode));
        return;
    }

    /* Use the sentence break iterator with the option. Preflight first. */
    length=ucasemap_toTitle(csm, NULL, 0, beforeTitle, UPRV_LENGTHOF(beforeTitle), &errorCode);
    if( errorCode!=U_BUFFER_OVERFLOW_ERROR ||
        length!=UPRV_LENGTHOF(titleSentNoLower)
    ) {
        log_err("ucasemap_toTitle(preflight sentence break iterator, no lowercasing)=%ld failed - %s\n", (long)length, u_errorName(errorCode));
    }

    errorCode=U_ZERO_ERROR;
    buffer[0]=0;
    length=ucasemap_toTitle(csm, buffer, UPRV_LENGTHOF(buffer), beforeTitle, UPRV_LENGTHOF(beforeTitle), &errorCode);
    if( U_FAILURE(errorCode) ||
        length!=UPRV_LENGTHOF(titleSentNoLower) ||
        0!=u_memcmp(buffer, titleSentNoLower, length) ||
        buffer[length]!=0
    ) {
        log_err("ucasemap_toTitle(sentence break iterator, no lowercasing)=%ld failed - %s\n", (long)length, u_errorName(errorCode));
    }

    /* UTF-8 C API coverage. More thorough test via C++ intltest's StringCaseTest::TestCasing(). */
    {
        char utf8BeforeTitle[64], utf8TitleSentNoLower[64], utf8[64];
        int32_t utf8BeforeTitleLength, utf8TitleSentNoLowerLength;

        errorCode=U_ZERO_ERROR;
        u_strToUTF8(utf8BeforeTitle, (int32_t)sizeof(utf8BeforeTitle), &utf8BeforeTitleLength, beforeTitle, UPRV_LENGTHOF(beforeTitle), &errorCode);
        u_strToUTF8(utf8TitleSentNoLower, (int32_t)sizeof(utf8TitleSentNoLower), &utf8TitleSentNoLowerLength, titleSentNoLower, UPRV_LENGTHOF(titleSentNoLower), &errorCode);

        length=ucasemap_utf8ToTitle(csm, utf8, (int32_t)sizeof(utf8), utf8BeforeTitle, utf8BeforeTitleLength, &errorCode);
        if( U_FAILURE(errorCode) ||
            length!=utf8TitleSentNoLowerLength ||
            0!=uprv_memcmp(utf8, utf8TitleSentNoLower, length) ||
            utf8[length]!=0
        ) {
            log_err("ucasemap_utf8ToTitle(sentence break iterator, no lowercasing)=%ld failed - %s\n", (long)length, u_errorName(errorCode));
        }
    }

    ucasemap_close(csm);
}