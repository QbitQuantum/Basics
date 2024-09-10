U_CAPI int32_t U_EXPORT2
ualoc_getLanguagesForRegion(const char *regionID, double minimumFraction,
                            UALanguageEntry *entries, int32_t entriesCapacity,
                            UErrorCode *err)
{
    if (U_FAILURE(*err)) {
        return 0;
    }
    if ( regionID == NULL || minimumFraction < 0.0 || minimumFraction > 1.0 ||
        ((entries==NULL)? entriesCapacity!=0: entriesCapacity<0) ) {
        *err = U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }
    UResourceBundle *rb = ures_openDirect(NULL, "supplementalData", err);
    rb = ures_getByKey(rb, "territoryInfo", rb, err);
    rb = ures_getByKey(rb, regionID, rb, err);
    if (U_FAILURE(*err)) {
        ures_close(rb);
        return 0;
    }

    int32_t entryCount = 0;
    UResourceBundle *langBund = NULL;
    int32_t lbIdx, lbCount = ures_getSize(rb);
    UALanguageEntry localLangEntries[kLocalLangEntriesMax];
    UALanguageEntry * langEntries = localLangEntries;
    int32_t langEntriesMax = kLocalLangEntriesMax;

    for (lbIdx = 0; lbIdx < lbCount; lbIdx++) {
        langBund = ures_getByIndex(rb, lbIdx, langBund, err);
        if (U_FAILURE(*err)) {
            break;
        }
        const char * langCode = ures_getKey(langBund);
        if (uprv_strcmp(langCode,"territoryF") == 0) {
            continue;
        }
        if (strnlen(langCode, UALANGDATA_CODELEN+1) > UALANGDATA_CODELEN) { // no uprv_strnlen
            continue; // a code we cannot handle
        }

        UErrorCode localErr = U_ZERO_ERROR;
        double userFraction = 0.0;
        UResourceBundle *itemBund = ures_getByKey(langBund, "populationShareF", NULL, &localErr);
        if (U_SUCCESS(localErr)) {
            int32_t intF = ures_getInt(itemBund, &localErr);
            if (U_SUCCESS(localErr)) {
                userFraction = doubleFromIntF(intF);
            }
            ures_close(itemBund);
        }
        if (userFraction < minimumFraction) {
            continue;
        }
        if (entries != NULL) {
            localErr = U_ZERO_ERROR;
            UALanguageStatus langStatus = UALANGSTATUS_UNSPECIFIED;
            int32_t ulen;
            const UChar * ustrLangStatus = ures_getStringByKey(langBund, "officialStatus", &ulen, &localErr);
            if (U_SUCCESS(localErr)) {
                int32_t cmp = u_strcmp(ustrLangStatus, ustrLangStatusOfficial);
                if (cmp == 0) {
                    langStatus = UALANGSTATUS_OFFICIAL;
                } else if (cmp < 0 && u_strcmp(ustrLangStatus, ustrLangStatusDefacto) == 0) {
                    langStatus = UALANGSTATUS_DEFACTO_OFFICIAL;
                } else if (u_strcmp(ustrLangStatus, ustrLangStatusRegional) == 0) {
                    langStatus = UALANGSTATUS_REGIONAL_OFFICIAL;
                }
            }
            // Now we have all of the info for our next entry
            if (entryCount >= langEntriesMax) {
                int32_t newMax = langEntriesMax * kLangEntriesFactor;
                if (langEntries == localLangEntries) {
                    // first allocation, copy from local buf
                    langEntries = (UALanguageEntry*)uprv_malloc(newMax*sizeof(UALanguageEntry));
                    if (langEntries == NULL) {
                        *err = U_MEMORY_ALLOCATION_ERROR;
                        break;
                    }
                    uprv_memcpy(langEntries, localLangEntries, entryCount*sizeof(UALanguageEntry));
                } else {
                    langEntries = (UALanguageEntry*)uprv_realloc(langEntries, newMax*sizeof(UALanguageEntry));
                    if (langEntries == NULL) {
                        *err = U_MEMORY_ALLOCATION_ERROR;
                        break;
                    }
                }
                langEntriesMax = newMax;
            }
            uprv_strcpy(langEntries[entryCount].languageCode, langCode);
            langEntries[entryCount].userFraction = userFraction;
            langEntries[entryCount].status = langStatus;
        }
        entryCount++;
    }
    ures_close(langBund);
    ures_close(rb);
    if (U_FAILURE(*err)) {
        if (langEntries != localLangEntries) {
            free(langEntries);
        }
        return 0;
    }
    if (entries != NULL) {
        // sort langEntries, copy entries that fit to provided array
        qsort(langEntries, entryCount, sizeof(UALanguageEntry), compareLangEntries);
        if (entryCount > entriesCapacity) {
            entryCount = entriesCapacity;
        }
        uprv_memcpy(entries, langEntries, entryCount*sizeof(UALanguageEntry));
        if (langEntries != localLangEntries) {
            free(langEntries);
        }
    }
    return entryCount;
}