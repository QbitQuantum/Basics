U_CAPI UEnumeration* U_EXPORT2
ucal_getKeywordValuesForLocale(const char * /* key */, const char* locale, UBool commonlyUsed, UErrorCode *status) {
    // Resolve region
    char prefRegion[ULOC_FULLNAME_CAPACITY] = "";
    int32_t prefRegionLength = 0;
    prefRegionLength = uloc_getCountry(locale, prefRegion, sizeof(prefRegion), status);
    if (prefRegionLength == 0) {
        char loc[ULOC_FULLNAME_CAPACITY] = "";
        int32_t locLength = 0;
        locLength = uloc_addLikelySubtags(locale, loc, sizeof(loc), status);
        
        prefRegionLength = uloc_getCountry(loc, prefRegion, sizeof(prefRegion), status);
    }
    
    // Read preferred calendar values from supplementalData calendarPreference
    UResourceBundle *rb = ures_openDirect(NULL, "supplementalData", status);
    ures_getByKey(rb, "calendarPreferenceData", rb, status);
    UResourceBundle *order = ures_getByKey(rb, prefRegion, NULL, status);
    if (*status == U_MISSING_RESOURCE_ERROR && rb != NULL) {
        *status = U_ZERO_ERROR;
        order = ures_getByKey(rb, "001", NULL, status);
    }

    // Create a list of calendar type strings
    UList *values = NULL;
    if (U_SUCCESS(*status)) {
        values = ulist_createEmptyList(status);
        if (U_SUCCESS(*status)) {
            for (int i = 0; i < ures_getSize(order); i++) {
                int32_t len;
                const UChar *type = ures_getStringByIndex(order, i, &len, status);
                char *caltype = (char*)uprv_malloc(len + 1);
                if (caltype == NULL) {
                    *status = U_MEMORY_ALLOCATION_ERROR;
                    break;
                }
                u_UCharsToChars(type, caltype, len);
                *(caltype + len) = 0;

                ulist_addItemEndList(values, caltype, TRUE, status);
                if (U_FAILURE(*status)) {
                    break;
                }
            }

            if (U_SUCCESS(*status) && !commonlyUsed) {
                // If not commonlyUsed, add other available values
                for (int32_t i = 0; CAL_TYPES[i] != NULL; i++) {
                    if (!ulist_containsString(values, CAL_TYPES[i], (int32_t)uprv_strlen(CAL_TYPES[i]))) {
                        ulist_addItemEndList(values, CAL_TYPES[i], FALSE, status);
                        if (U_FAILURE(*status)) {
                            break;
                        }
                    }
                }
            }
            if (U_FAILURE(*status)) {
                ulist_deleteList(values);
                values = NULL;
            }
        }
    }

    ures_close(order);
    ures_close(rb);

    if (U_FAILURE(*status) || values == NULL) {
        return NULL;
    }

    // Create string enumeration
    UEnumeration *en = (UEnumeration*)uprv_malloc(sizeof(UEnumeration));
    if (en == NULL) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        ulist_deleteList(values);
        return NULL;
    }
    ulist_resetList(values);
    memcpy(en, &defaultKeywordValues, sizeof(UEnumeration));
    en->context = values;
    return en;
}