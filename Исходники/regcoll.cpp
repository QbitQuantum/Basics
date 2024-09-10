// Ticket 7189
//
// nextSortKeyPart incorrect for EO_S1 collation
static int32_t calcKeyIncremental(UCollator *coll, const UChar* text, int32_t len, uint8_t *keyBuf, int32_t /*keyBufLen*/, UErrorCode& status) {
    UCharIterator uiter;
    uint32_t state[2] = { 0, 0 };
    int32_t keyLen;
    int32_t count = 8;

    uiter_setString(&uiter, text, len);
    keyLen = 0;
    while (TRUE) {
        int32_t keyPartLen = ucol_nextSortKeyPart(coll, &uiter, state, &keyBuf[keyLen], count, &status);
        if (U_FAILURE(status)) {
            return -1;
        }
        if (keyPartLen == 0) {
            break;
        }
        keyLen += keyPartLen;
    }
    return keyLen;
}