void
TZGNCore::initialize(const Locale& locale, UErrorCode& status) {
    if (U_FAILURE(status)) {
        return;
    }

    // TimeZoneNames
    fTimeZoneNames = TimeZoneNames::createInstance(locale, status);
    if (U_FAILURE(status)) {
        return;
    }

    // Initialize format patterns
    UnicodeString rpat(TRUE, gDefRegionPattern, -1);
    UnicodeString fpat(TRUE, gDefFallbackPattern, -1);

    UErrorCode tmpsts = U_ZERO_ERROR;   // OK with fallback warning..
    UResourceBundle *zoneStrings = ures_open(U_ICUDATA_ZONE, locale.getName(), &tmpsts);
    zoneStrings = ures_getByKeyWithFallback(zoneStrings, gZoneStrings, zoneStrings, &tmpsts);

    if (U_SUCCESS(tmpsts)) {
        const UChar *regionPattern = ures_getStringByKeyWithFallback(zoneStrings, gRegionFormatTag, NULL, &tmpsts);
        if (U_SUCCESS(tmpsts) && u_strlen(regionPattern) > 0) {
            rpat.setTo(regionPattern, -1);
        }
        tmpsts = U_ZERO_ERROR;
        const UChar *fallbackPattern = ures_getStringByKeyWithFallback(zoneStrings, gFallbackFormatTag, NULL, &tmpsts);
        if (U_SUCCESS(tmpsts) && u_strlen(fallbackPattern) > 0) {
            fpat.setTo(fallbackPattern, -1);
        }
    }
    ures_close(zoneStrings);

    fRegionFormat = new MessageFormat(rpat, status);
    if (fRegionFormat == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
    }
    fFallbackFormat = new MessageFormat(fpat, status);
    if (fFallbackFormat == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
    }
    if (U_FAILURE(status)) {
        cleanup();
        return;
    }

    // locale display names
    fLocaleDisplayNames = LocaleDisplayNames::createInstance(locale);

    // hash table for names - no key/value deleters
    fLocationNamesMap = uhash_open(uhash_hashUChars, uhash_compareUChars, NULL, &status);
    if (U_FAILURE(status)) {
        cleanup();
        return;
    }

    fPartialLocationNamesMap = uhash_open(hashPartialLocationKey, comparePartialLocationKey, NULL, &status);
    if (U_FAILURE(status)) {
        cleanup();
        return;
    }
    uhash_setKeyDeleter(fPartialLocationNamesMap, uprv_free);
    // no value deleter

    // target region
    const char* region = fLocale.getCountry();
    int32_t regionLen = uprv_strlen(region);
    if (regionLen == 0) {
        char loc[ULOC_FULLNAME_CAPACITY];
        uloc_addLikelySubtags(fLocale.getName(), loc, sizeof(loc), &status);

        regionLen = uloc_getCountry(loc, fTargetRegion, sizeof(fTargetRegion), &status);
        if (U_SUCCESS(status)) {
            fTargetRegion[regionLen] = 0;
        } else {
            cleanup();
            return;
        }
    } else if (regionLen < (int32_t)sizeof(fTargetRegion)) {
        uprv_strcpy(fTargetRegion, region);
    } else {
        fTargetRegion[0] = 0;
    }

    // preload generic names for the default zone
    TimeZone *tz = TimeZone::createDefault();
    const UChar *tzID = ZoneMeta::getCanonicalCLDRID(*tz);
    if (tzID != NULL) {
        loadStrings(UnicodeString(tzID));
    }
    delete tz;
}