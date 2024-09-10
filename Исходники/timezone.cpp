    TZEnumeration(const char* country) : map(NULL), len(0), pos(0) {
        if (!getOlsonMeta()) {
            return;
        }

        UErrorCode ec = U_ZERO_ERROR;
        UResourceBundle *res = ures_openDirect(0, kZONEINFO, &ec);
        ures_getByKey(res, kREGIONS, res, &ec);
        if (U_SUCCESS(ec) && ures_getType(res) == URES_ARRAY) {
            UChar uCountry[] = {0, 0, 0, 0};
            if (country) {
                u_charsToUChars(country, uCountry, 2);
            } else {
                u_strcpy(uCountry, WORLD);
            }

            // count matches
            int32_t count = 0;
            int32_t i;
            const UChar *region;
            for (i = 0; i < ures_getSize(res); i++) {
                region = ures_getStringByIndex(res, i, NULL, &ec);
                if (U_FAILURE(ec)) {
                    break;
                }
                if (u_strcmp(uCountry, region) == 0) {
                    count++;
                }
            }

            if (count > 0) {
                map = (int32_t*)uprv_malloc(sizeof(int32_t) * count);
                if (map != NULL) {
                    int32_t idx = 0;
                    for (i = 0; i < ures_getSize(res); i++) {
                        region = ures_getStringByIndex(res, i, NULL, &ec);
                        if (U_FAILURE(ec)) {
                            break;
                        }
                        if (u_strcmp(uCountry, region) == 0) {
                            map[idx++] = i;
                        }
                    }
                    if (U_SUCCESS(ec)) {
                        len = count;
                    } else {
                        uprv_free(map);
                        map = NULL;
                    }
                } else {
                    U_DEBUG_TZ_MSG(("Failed to load tz for region %s: %s\n", country, u_errorName(ec)));
                }
            }
        }
        ures_close(res);
    }