static void U_CALLCONV
bidiClassLineFn(void *context,
                char *fields[][2], int32_t fieldCount,
                UErrorCode *pErrorCode) {
    char *s;
    uint32_t start, end, value;

    /* get the code point range */
    u_parseCodePointRange(fields[0][0], &start, &end, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        fprintf(stderr, "genbidi: syntax error in DerivedBidiClass.txt field 0 at %s\n", fields[0][0]);
        exit(*pErrorCode);
    }

    /* parse bidi class */
    s=trimTerminateField(fields[1][0], fields[1][1]);
    value=u_getPropertyValueEnum(UCHAR_BIDI_CLASS, s);
    if((int32_t)value<0) {
        fprintf(stderr, "genbidi error: unknown bidi class in DerivedBidiClass.txt field 1 at %s\n", s);
        exit(U_PARSE_ERROR);
    }

    upvec_setValue(pv, start, end, 0, value, UBIDI_CLASS_MASK, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        fprintf(stderr, "genbidi error: unable to set derived bidi class for U+%04x..U+%04x - %s\n",
                (int)start, (int)end, u_errorName(*pErrorCode));
        exit(*pErrorCode);
    }
}