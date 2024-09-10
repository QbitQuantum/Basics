UnicodeString& U_EXPORT2
ZoneMeta::getSingleCountry(const UnicodeString &tzid, UnicodeString &country) {
    // Get canonical country for the zone
    const UChar *region = TimeZone::getRegion(tzid);
    if (u_strcmp(gWorld, region) == 0) {
        // special case - "001"
        country.remove();
        return country;
    }

    // Checking the cached results
    UErrorCode status = U_ZERO_ERROR;
    UBool initialized;
    UMTX_CHECK(&gZoneMetaLock, gCountryInfoVectorsInitialized, initialized);
    if (!initialized) {
        // Create empty vectors
        umtx_lock(&gZoneMetaLock);
        {
            if (!gCountryInfoVectorsInitialized) {
                // No deleters for these UVectors, it's a reference to a resource bundle string.
                gSingleZoneCountries = new UVector(NULL, uhash_compareUChars, status);
                if (gSingleZoneCountries == NULL) {
                    status = U_MEMORY_ALLOCATION_ERROR;
                }
                gMultiZonesCountries = new UVector(NULL, uhash_compareUChars, status);
                if (gMultiZonesCountries == NULL) {
                    status = U_MEMORY_ALLOCATION_ERROR;
                }

                if (U_SUCCESS(status)) {
                    gCountryInfoVectorsInitialized = TRUE;
                } else {
                    delete gSingleZoneCountries;
                    delete gMultiZonesCountries;
                }
            }
        }
        umtx_unlock(&gZoneMetaLock);

        if (U_FAILURE(status)) {
            country.remove();
            return country;
        }
    }

    // Check if it was already cached
    UBool cached = FALSE;
    UBool multiZones = FALSE;
    umtx_lock(&gZoneMetaLock);
    {
        multiZones = cached = gMultiZonesCountries->contains((void*)region);
        if (!multiZones) {
            cached = gSingleZoneCountries->contains((void*)region);
        }
    }
    umtx_unlock(&gZoneMetaLock);

    if (!cached) {
        // We need to go through all zones associated with the region.
        // This is relatively heavy operation.

        U_ASSERT(u_strlen(region) == 2);

        char buf[] = {0, 0, 0};
        u_UCharsToChars(region, buf, 2);

        StringEnumeration *ids = TimeZone::createEnumeration(buf);
        int32_t idsLen = ids->count(status);
        if (U_SUCCESS(status) && idsLen > 1) {
            // multiple zones are available for the region
            UnicodeString canonical, tmp;
            const UnicodeString *id = ids->snext(status);
            getCanonicalSystemID(*id, canonical, status);
            if (U_SUCCESS(status)) {
                // check if there are any other canonical zone in the group
                while ((id = ids->snext(status))!=NULL) {
                    getCanonicalSystemID(*id, tmp, status);
                    if (U_FAILURE(status)) {
                        break;
                    }
                    if (canonical != tmp) {
                        // another canonical zone was found
                        multiZones = TRUE;
                        break;
                    }
                }
            }
        }
        if (U_FAILURE(status)) {
            // no single country by default for any error cases
            multiZones = TRUE;
        }
        delete ids;

        // Cache the result
        umtx_lock(&gZoneMetaLock);
        {
            UErrorCode ec = U_ZERO_ERROR;
            if (multiZones) {
                if (!gMultiZonesCountries->contains((void*)region)) {
                    gMultiZonesCountries->addElement((void*)region, ec);
                }
            } else {
                if (!gSingleZoneCountries->contains((void*)region)) {
                    gSingleZoneCountries->addElement((void*)region, ec);
                }
            }
        }
        umtx_unlock(&gZoneMetaLock);
    }

    if (multiZones) {
        country.remove();
    } else {
        country.setTo(region, -1);
    }
    return country;
}