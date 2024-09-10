/*
 * Generate a text file with spaces in it from a file without.
 */
int generateFile(const UChar *chars, int32_t length) {
    Locale root("");
    UCharCharacterIterator *noSpaceIter = new UCharCharacterIterator(chars, length);
    UErrorCode status = U_ZERO_ERROR;
    
    UnicodeSet complexContext(UNICODE_STRING_SIMPLE("[:LineBreak=SA:]"), status);
    BreakIterator *breakIter = BreakIterator::createWordInstance(root, status);
    breakIter->adoptText(noSpaceIter);
    char outbuf[1024];
    int32_t strlength;
    UChar bom = 0xFEFF;
    
    printf("%s", u_strToUTF8(outbuf, sizeof(outbuf), &strlength, &bom, 1, &status));
    int32_t prevbreak = 0;
    while (U_SUCCESS(status)) {
        int32_t nextbreak = breakIter->next();
        if (nextbreak == BreakIterator::DONE) {
            break;
        }
        printf("%s", u_strToUTF8(outbuf, sizeof(outbuf), &strlength, &chars[prevbreak],
                                    nextbreak-prevbreak, &status));
        if (nextbreak > 0 && complexContext.contains(chars[nextbreak-1])
            && complexContext.contains(chars[nextbreak])) {
            printf(" ");
        }
        prevbreak = nextbreak;
    }
    
    if (U_FAILURE(status)) {
        fprintf(stderr, "generate failed: %s\n", u_errorName(status));
        return status;
    }
    else {
        return 0;
    }
}