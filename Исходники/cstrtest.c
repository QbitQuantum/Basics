/* test invariant-character handling */
static void
TestInvariant() {
    /* all invariant graphic chars and some control codes (not \n!) */
    const char invariantChars[]=
        "\t\r \"%&'()*+,-./"
        "0123456789:;<=>?"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ_"
        "abcdefghijklmnopqrstuvwxyz";

    const UChar invariantUChars[]={
        9, 0xd, 0x20, 0x22, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5f,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0
    };

    const char variantChars[]="\n!#$@[\\]^`{|}~";

    const UChar variantUChars[]={
        0x0a, 0x21, 0x23, 0x24, 0x40, 0x5b, 0x5c, 0x5d, 0x5e, 0x60, 0x7b, 0x7c, 0x7d, 0x7e, 0
    };

    const UChar nonASCIIUChars[]={ 0x80, 0xa0, 0x900, 0xff51 };

    UChar us[120];
    char cs[120];

    int32_t i, length;

    /* make sure that all invariant characters convert both ways */
    length=sizeof(invariantChars);
    u_charsToUChars(invariantChars, us, length);
    if(u_strcmp(us, invariantUChars)!=0) {
        log_err("u_charsToUChars(invariantChars) failed\n");
    }

    u_UCharsToChars(invariantUChars, cs, length);
    if(strcmp(cs, invariantChars)!=0) {
        log_err("u_UCharsToChars(invariantUChars) failed\n");
    }


    /*
     * make sure that variant characters convert from source code literals to Unicode
     * but not back to char *
     */
    length=sizeof(variantChars);
    u_charsToUChars(variantChars, us, length);
    if(u_strcmp(us, variantUChars)!=0) {
        log_err("u_charsToUChars(variantChars) failed\n");
    }

#ifdef NDEBUG
    /*
     * Test u_UCharsToChars(variantUChars) only in release mode because it will
     * cause an assertion failure in debug builds.
     */
    u_UCharsToChars(variantUChars, cs, length);
    for(i=0; i<length; ++i) {
        if(cs[i]!=0) {
            log_err("u_UCharsToChars(variantUChars) converted the %d-th character to %02x instead of 00\n", i, cs[i]);
        }
    }
#endif

    /*
     * Verify that invariant characters roundtrip from Unicode to the
     * default converter and back.
     */
    {
        UConverter *cnv;
        UErrorCode errorCode;

        errorCode=U_ZERO_ERROR;
        cnv=ucnv_open(NULL, &errorCode);
        if(U_FAILURE(errorCode)) {
            log_err("unable to open the default converter\n");
        } else {
            length=ucnv_fromUChars(cnv, cs, sizeof(cs), invariantUChars, -1, &errorCode);
            if(U_FAILURE(errorCode)) {
                log_err("ucnv_fromUChars(invariantUChars) failed - %s\n", u_errorName(errorCode));
            } else if(length!=sizeof(invariantChars)-1 || strcmp(cs, invariantChars)!=0) {
                log_err("ucnv_fromUChars(invariantUChars) failed\n");
            }

            errorCode=U_ZERO_ERROR;
            length=ucnv_toUChars(cnv, us, LENGTHOF(us), invariantChars, -1, &errorCode);
            if(U_FAILURE(errorCode)) {
                log_err("ucnv_toUChars(invariantChars) failed - %s\n", u_errorName(errorCode));
            } else if(length!=LENGTHOF(invariantUChars)-1 || u_strcmp(us, invariantUChars)!=0) {
                log_err("ucnv_toUChars(invariantChars) failed\n");
            }

            ucnv_close(cnv);
        }
    }

    /* API tests */
    if(!uprv_isInvariantString(invariantChars, -1)) {
        log_err("uprv_isInvariantString(invariantChars) failed\n");
    }
    if(!uprv_isInvariantUString(invariantUChars, -1)) {
        log_err("uprv_isInvariantUString(invariantUChars) failed\n");
    }
    if(!uprv_isInvariantString(invariantChars+strlen(invariantChars), 1)) {
        log_err("uprv_isInvariantString(\"\\0\") failed\n");
    }

    for(i=0; i<(sizeof(variantChars)-1); ++i) {
        if(uprv_isInvariantString(variantChars+i, 1)) {
            log_err("uprv_isInvariantString(variantChars[%d]) failed\n", i);
        }
        if(uprv_isInvariantUString(variantUChars+i, 1)) {
            log_err("uprv_isInvariantUString(variantUChars[%d]) failed\n", i);
        }
    }

    for(i=0; i<LENGTHOF(nonASCIIUChars); ++i) {
        if(uprv_isInvariantUString(nonASCIIUChars+i, 1)) {
            log_err("uprv_isInvariantUString(nonASCIIUChars[%d]) failed\n", i);
        }
    }
}