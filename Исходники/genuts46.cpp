static int
toIDNA2003(const UStringPrepProfile *prep, UChar32 c, icu::UnicodeString &destString) {
    UChar src[2];
    int32_t srcLength=0;
    U16_APPEND_UNSAFE(src, srcLength, c);
    UChar *dest;
    int32_t destLength;
    dest=destString.getBuffer(32);
    if(dest==NULL) {
        return FALSE;
    }
    UErrorCode errorCode=U_ZERO_ERROR;
    destLength=usprep_prepare(prep, src, srcLength,
                              dest, destString.getCapacity(),
                              USPREP_DEFAULT, NULL, &errorCode);
    destString.releaseBuffer(destLength);
    if(errorCode==U_STRINGPREP_PROHIBITED_ERROR) {
        return -1;
    } else {
        // Returns FALSE=0 for U_STRINGPREP_UNASSIGNED_ERROR and processing errors,
        // TRUE=1 if c is valid or mapped.
        return U_SUCCESS(errorCode);
    }
}