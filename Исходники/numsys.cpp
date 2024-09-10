NumberingSystem* U_EXPORT2
NumberingSystem::createInstance(const Locale & inLocale, UErrorCode& status) {

    if (U_FAILURE(status)) {
        return NULL;
    }

    UBool nsResolved = TRUE;
    UBool usingFallback = FALSE;
    char buffer[ULOC_KEYWORDS_CAPACITY];
    int32_t count = inLocale.getKeywordValue("numbers",buffer, sizeof(buffer),status);
    if ( count > 0 ) { // @numbers keyword was specified in the locale
        buffer[count] = '\0'; // Make sure it is null terminated.
        if ( !uprv_strcmp(buffer,gDefault) || !uprv_strcmp(buffer,gNative) ||
             !uprv_strcmp(buffer,gTraditional) || !uprv_strcmp(buffer,gFinance)) {
            nsResolved = FALSE;
        }
    } else {
        uprv_strcpy(buffer,gDefault);
        nsResolved = FALSE;
    }

    if (!nsResolved) { // Resolve the numbering system ( default, native, traditional or finance ) into a "real" numbering system
        UErrorCode localStatus = U_ZERO_ERROR;
        UResourceBundle *resource = ures_open(NULL, inLocale.getName(), &localStatus);
        UResourceBundle *numberElementsRes = ures_getByKey(resource,gNumberElements,NULL,&localStatus);
        while (!nsResolved) {
            localStatus = U_ZERO_ERROR;
            count = 0;
            const UChar *nsName = ures_getStringByKeyWithFallback(numberElementsRes, buffer, &count, &localStatus);
            if ( count > 0 && count < ULOC_KEYWORDS_CAPACITY ) { // numbering system found
                u_UCharsToChars(nsName,buffer,count);
                buffer[count] = '\0'; // Make sure it is null terminated.
                nsResolved = TRUE;
            }

            if (!nsResolved) { // Fallback behavior per TR35 - traditional falls back to native, finance and native fall back to default
                if (!uprv_strcmp(buffer,gNative) || !uprv_strcmp(buffer,gFinance)) {
                    uprv_strcpy(buffer,gDefault);
                } else if (!uprv_strcmp(buffer,gTraditional)) {
                    uprv_strcpy(buffer,gNative);
                } else { // If we get here we couldn't find even the default numbering system
                    usingFallback = TRUE;
                    nsResolved = TRUE;
                }
            }
        }
        ures_close(numberElementsRes);
        ures_close(resource);
    }

    if (usingFallback) {
        status = U_USING_FALLBACK_WARNING;
        NumberingSystem *ns = new NumberingSystem();
        return ns;
    } else {
        return NumberingSystem::createInstanceByName(buffer,status);
    }
 }