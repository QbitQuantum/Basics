/**
 * This function looks for the localeID in the likelySubtags resource.
 *
 * @param localeID The tag to find.
 * @param buffer A buffer to hold the matching entry
 * @param bufferLength The length of the output buffer
 * @return A pointer to "buffer" if found, or a null pointer if not.
 */
static const char*  U_CALLCONV
findLikelySubtags(const char* localeID,
                  char* buffer,
                  int32_t bufferLength,
                  UErrorCode* err) {
    const char* result = NULL;

    if (!U_FAILURE(*err)) {
        int32_t resLen = 0;
        const UChar* s = NULL;
        UErrorCode tmpErr = U_ZERO_ERROR;
        UResourceBundle* subtags = ures_openDirect(NULL, "likelySubtags", &tmpErr);
        if (U_SUCCESS(tmpErr)) {
            s = ures_getStringByKey(subtags, localeID, &resLen, &tmpErr);

            if (U_FAILURE(tmpErr)) {
                /*
                 * If a resource is missing, it's not really an error, it's
                 * just that we don't have any data for that particular locale ID.
                 */
                if (tmpErr != U_MISSING_RESOURCE_ERROR) {
                    *err = tmpErr;
                }
            }
            else if (resLen >= bufferLength) {
                /* The buffer should never overflow. */
                *err = U_INTERNAL_PROGRAM_ERROR;
            }
            else {
                u_UCharsToChars(s, buffer, resLen + 1);
                result = buffer;
            }

            ures_close(subtags);
        } else {
            *err = tmpErr;
        }
    }

    return result;
}