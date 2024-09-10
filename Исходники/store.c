static void
makeUnfoldData() {
    static const UChar
        iDot[2]=        { 0x69, 0x307 };

    UChar *p, *q;
    int32_t i, j, k;
    UErrorCode errorCode;

    /*
     * add a case folding that we missed because it's conditional:
     * 0130; F; 0069 0307; # LATIN CAPITAL LETTER I WITH DOT ABOVE
     */
    addUnfolding(0x130, iDot, 2);

    /* sort the data */
    errorCode=U_ZERO_ERROR;
    uprv_sortArray(unfold+UGENCASE_UNFOLD_WIDTH, unfoldRows, UGENCASE_UNFOLD_WIDTH*2,
                   compareUnfold, NULL, FALSE, &errorCode);

    /* make unique-string rows by merging adjacent ones' code point columns */

    /* make p point to row i-1 */
    p=(UChar *)unfold+UGENCASE_UNFOLD_WIDTH;

    for(i=1; i<unfoldRows;) {
        if(0==u_memcmp(p, p+UGENCASE_UNFOLD_WIDTH, UGENCASE_UNFOLD_STRING_WIDTH)) {
            /* concatenate code point columns */
            q=p+UGENCASE_UNFOLD_STRING_WIDTH;
            for(j=1; j<UGENCASE_UNFOLD_CP_WIDTH && q[j]!=0; ++j) {}
            for(k=0; k<UGENCASE_UNFOLD_CP_WIDTH && q[UGENCASE_UNFOLD_WIDTH+k]!=0; ++j, ++k) {
                q[j]=q[UGENCASE_UNFOLD_WIDTH+k];
            }
            if(j>UGENCASE_UNFOLD_CP_WIDTH) {
                fprintf(stderr, "gencase error: too many code points in unfold[]: %ld>%d=UGENCASE_UNFOLD_CP_WIDTH\n",
                        (long)j, UGENCASE_UNFOLD_CP_WIDTH);
                exit(U_BUFFER_OVERFLOW_ERROR);
            }

            /* move following rows up one */
            --unfoldRows;
            unfoldTop-=UGENCASE_UNFOLD_WIDTH;
            u_memmove(p+UGENCASE_UNFOLD_WIDTH, p+UGENCASE_UNFOLD_WIDTH*2, (unfoldRows-i)*UGENCASE_UNFOLD_WIDTH);
        } else {
            p+=UGENCASE_UNFOLD_WIDTH;
            ++i;
        }
    }

    unfold[UCASE_UNFOLD_ROWS]=(UChar)unfoldRows;

    if(beVerbose) {
        puts("unfold data:");

        p=(UChar *)unfold;
        for(i=0; i<unfoldRows; ++i) {
            p+=UGENCASE_UNFOLD_WIDTH;
            printf("[%2d] %04x %04x %04x <- %04x %04x\n",
                   (int)i, p[0], p[1], p[2], p[3], p[4]);
        }
    }
}