/* Don't call this directly. Only uenum_next should be calling this. */
U_CAPI const char* U_EXPORT2
uenum_nextDefault(UEnumeration* en,
            int32_t* resultLength,
            UErrorCode* status)
{
    if (en->uNext != NULL) {
        char *tempCharVal;
        const UChar *tempUCharVal = en->uNext(en, resultLength, status);
        if (tempUCharVal == NULL) {
            return NULL;
        }
        tempCharVal = (char*)
            _getBuffer(en, (*resultLength+1) * sizeof(char));
        if (!tempCharVal) {
            *status = U_MEMORY_ALLOCATION_ERROR;
            return NULL;
        }
        u_UCharsToChars(tempUCharVal, tempCharVal, *resultLength + 1);
        return tempCharVal;
    } else {
        *status = U_UNSUPPORTED_ERROR;
        return NULL;
    }
}