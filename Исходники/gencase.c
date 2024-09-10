static void
parseDB(const char *filename, UErrorCode *pErrorCode) {
    char *fields[15][2];
    UChar32 start, end;
    int32_t i;

    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return;
    }

    u_parseDelimitedFile(filename, ';', fields, 15, unicodeDataLineFn, NULL, pErrorCode);

    /* are all sub-properties consumed? */
    if(specialCasingIndex<specialCasingCount) {
        fprintf(stderr, "gencase: error - some code points in SpecialCasing.txt are missing from UnicodeData.txt\n");
        *pErrorCode=U_PARSE_ERROR;
        exit(U_PARSE_ERROR);
    }
    if(caseFoldingIndex<caseFoldingCount) {
        fprintf(stderr, "gencase: error - some code points in CaseFolding.txt are missing from UnicodeData.txt\n");
        *pErrorCode=U_PARSE_ERROR;
        exit(U_PARSE_ERROR);
    }

    if(U_FAILURE(*pErrorCode)) {
        return;
    }

    for(i=0;
        0==uset_getItem(caseSensitive, i, &start, &end, NULL, 0, pErrorCode) && U_SUCCESS(*pErrorCode);
        ++i
    ) {
        addCaseSensitive(start, end);
    }
    if(*pErrorCode==U_INDEX_OUTOFBOUNDS_ERROR) {
        *pErrorCode=U_ZERO_ERROR;
    }
}