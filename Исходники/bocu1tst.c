/* test one string with the ICU and the reference BOCU-1 implementations */
static void
roundtripBOCU1(UConverter *bocu1, int32_t number, const UChar *text, int32_t length) {
    UChar *roundtripRef, *roundtripICU;
    char *bocu1Ref, *bocu1ICU;

    int32_t bocu1RefLength, bocu1ICULength, roundtripRefLength, roundtripICULength;
    UErrorCode errorCode;

    roundtripRef = malloc(DEFAULT_BUFFER_SIZE * sizeof(UChar));
    roundtripICU = malloc(DEFAULT_BUFFER_SIZE * sizeof(UChar));
    bocu1Ref = malloc(DEFAULT_BUFFER_SIZE);
    bocu1ICU = malloc(DEFAULT_BUFFER_SIZE);

    /* Unicode -> BOCU-1 */
    bocu1RefLength=writeString(text, length, (uint8_t *)bocu1Ref);

    errorCode=U_ZERO_ERROR;
    bocu1ICULength=ucnv_fromUChars(bocu1, bocu1ICU, DEFAULT_BUFFER_SIZE, text, length, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("ucnv_fromUChars(BOCU-1, text(%d)[%d]) failed: %s\n", number, length, u_errorName(errorCode));
        goto cleanup; 
    }

    if(bocu1RefLength!=bocu1ICULength || 0!=uprv_memcmp(bocu1Ref, bocu1ICU, bocu1RefLength)) {
        log_err("Unicode(%d)[%d] -> BOCU-1: reference[%d]!=ICU[%d]\n", number, length, bocu1RefLength, bocu1ICULength);
        goto cleanup;
    }

    /* BOCU-1 -> Unicode */
    roundtripRefLength=readString((uint8_t *)bocu1Ref, bocu1RefLength, roundtripRef);
    if(roundtripRefLength<0) {
        goto cleanup; /* readString() found an error and reported it */
    }

    roundtripICULength=ucnv_toUChars(bocu1, roundtripICU, DEFAULT_BUFFER_SIZE, bocu1ICU, bocu1ICULength, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("ucnv_toUChars(BOCU-1, text(%d)[%d]) failed: %s\n", number, length, u_errorName(errorCode));
        goto cleanup;
    }

    if(length!=roundtripRefLength || 0!=u_memcmp(text, roundtripRef, length)) {
        log_err("BOCU-1 -> Unicode: original(%d)[%d]!=reference[%d]\n", number, length, roundtripRefLength);
        goto cleanup;
    }
    if(roundtripRefLength!=roundtripICULength || 0!=u_memcmp(roundtripRef, roundtripICU, roundtripRefLength)) {
        log_err("BOCU-1 -> Unicode: reference(%d)[%d]!=ICU[%d]\n", number, roundtripRefLength, roundtripICULength);
        goto cleanup;
    }
cleanup:
    free(roundtripRef);
    free(roundtripICU);
    free(bocu1Ref);
    free(bocu1ICU);
}