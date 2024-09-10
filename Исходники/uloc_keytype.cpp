U_CDECL_END


static void U_CALLCONV
initFromResourceBundle(UErrorCode& sts) {
    U_NAMESPACE_USE
    ucln_common_registerCleanup(UCLN_COMMON_LOCALE_KEY_TYPE, uloc_key_type_cleanup);

    gLocExtKeyMap = uhash_open(uhash_hashIChars, uhash_compareIChars, NULL, &sts);

    LocalUResourceBundlePointer keyTypeDataRes(ures_openDirect(NULL, "keyTypeData", &sts));
    LocalUResourceBundlePointer keyMapRes(ures_getByKey(keyTypeDataRes.getAlias(), "keyMap", NULL, &sts));
    LocalUResourceBundlePointer typeMapRes(ures_getByKey(keyTypeDataRes.getAlias(), "typeMap", NULL, &sts));

    if (U_FAILURE(sts)) {
        return;
    }

    UErrorCode tmpSts = U_ZERO_ERROR;
    LocalUResourceBundlePointer typeAliasRes(ures_getByKey(keyTypeDataRes.getAlias(), "typeAlias", NULL, &tmpSts));
    tmpSts = U_ZERO_ERROR;
    LocalUResourceBundlePointer bcpTypeAliasRes(ures_getByKey(keyTypeDataRes.getAlias(), "bcpTypeAlias", NULL, &tmpSts));

    // initialize vectors storing dynamically allocated objects
    gKeyTypeStringPool = new UVector(uloc_deleteKeyTypeStringPoolEntry, NULL, sts);
    if (gKeyTypeStringPool == NULL) {
        if (U_SUCCESS(sts)) {
            sts = U_MEMORY_ALLOCATION_ERROR;
        }
    }
    if (U_FAILURE(sts)) {
        return;
    }
    gLocExtKeyDataEntries = new UVector(uloc_deleteKeyDataEntry, NULL, sts);
    if (gLocExtKeyDataEntries == NULL) {
        if (U_SUCCESS(sts)) {
            sts = U_MEMORY_ALLOCATION_ERROR;
        }
    }
    if (U_FAILURE(sts)) {
        return;
    }
    gLocExtTypeEntries = new UVector(uloc_deleteTypeEntry, NULL, sts);
    if (gLocExtTypeEntries == NULL) {
        if (U_SUCCESS(sts)) {
            sts = U_MEMORY_ALLOCATION_ERROR;
        }
    }
    if (U_FAILURE(sts)) {
        return;
    }

    // iterate through keyMap resource
    LocalUResourceBundlePointer keyMapEntry;

    while (ures_hasNext(keyMapRes.getAlias())) {
        keyMapEntry.adoptInstead(ures_getNextResource(keyMapRes.getAlias(), keyMapEntry.orphan(), &sts));
        if (U_FAILURE(sts)) {
            break;
        }
        const char* legacyKeyId = ures_getKey(keyMapEntry.getAlias());
        int32_t bcpKeyIdLen = 0;
        const UChar* uBcpKeyId = ures_getString(keyMapEntry.getAlias(), &bcpKeyIdLen, &sts);
        if (U_FAILURE(sts)) {
            break;
        }

        // empty value indicates that BCP key is same with the legacy key.
        const char* bcpKeyId = legacyKeyId;
        if (bcpKeyIdLen > 0) {
            char* bcpKeyIdBuf = (char*)uprv_malloc(bcpKeyIdLen + 1);
            if (bcpKeyIdBuf == NULL) {
                sts = U_MEMORY_ALLOCATION_ERROR;
                break;
            }
            u_UCharsToChars(uBcpKeyId, bcpKeyIdBuf, bcpKeyIdLen);
            bcpKeyIdBuf[bcpKeyIdLen] = 0;
            gKeyTypeStringPool->addElement(bcpKeyIdBuf, sts);
            if (U_FAILURE(sts)) {
                break;
            }
            bcpKeyId = bcpKeyIdBuf;
        }

        UBool isTZ = uprv_strcmp(legacyKeyId, "timezone") == 0;

        UHashtable* typeDataMap = uhash_open(uhash_hashIChars, uhash_compareIChars, NULL, &sts);
        if (U_FAILURE(sts)) {
            break;
        }
        uint32_t specialTypes = SPECIALTYPE_NONE;

        LocalUResourceBundlePointer typeAliasResByKey;
        LocalUResourceBundlePointer bcpTypeAliasResByKey;

        if (typeAliasRes.isValid()) {
            tmpSts = U_ZERO_ERROR;
            typeAliasResByKey.adoptInstead(ures_getByKey(typeAliasRes.getAlias(), legacyKeyId, NULL, &tmpSts));
            if (U_FAILURE(tmpSts)) {
                typeAliasResByKey.orphan();
            }
        }
        if (bcpTypeAliasRes.isValid()) {
            tmpSts = U_ZERO_ERROR;
            bcpTypeAliasResByKey.adoptInstead(ures_getByKey(bcpTypeAliasRes.getAlias(), bcpKeyId, NULL, &tmpSts));
            if (U_FAILURE(tmpSts)) {
                bcpTypeAliasResByKey.orphan();
            }
        }

        // look up type map for the key, and walk through the mapping data
        tmpSts = U_ZERO_ERROR;
        LocalUResourceBundlePointer typeMapResByKey(ures_getByKey(typeMapRes.getAlias(), legacyKeyId, NULL, &tmpSts));
        if (U_FAILURE(tmpSts)) {
            // type map for each key must exist
            U_ASSERT(FALSE);
        } else {
            LocalUResourceBundlePointer typeMapEntry;

            while (ures_hasNext(typeMapResByKey.getAlias())) {
                typeMapEntry.adoptInstead(ures_getNextResource(typeMapResByKey.getAlias(), typeMapEntry.orphan(), &sts));
                if (U_FAILURE(sts)) {
                    break;
                }
                const char* legacyTypeId = ures_getKey(typeMapEntry.getAlias());

                // special types
                if (uprv_strcmp(legacyTypeId, "CODEPOINTS") == 0) {
                    specialTypes |= SPECIALTYPE_CODEPOINTS;
                    continue;
                }
                if (uprv_strcmp(legacyTypeId, "REORDER_CODE") == 0) {
                    specialTypes |= SPECIALTYPE_REORDER_CODE;
                    continue;
                }
                if (uprv_strcmp(legacyTypeId, "RG_KEY_VALUE") == 0) {
                    specialTypes |= SPECIALTYPE_RG_KEY_VALUE;
                    continue;
                }

                if (isTZ) {
                    // a timezone key uses a colon instead of a slash in the resource.
                    // e.g. America:Los_Angeles
                    if (uprv_strchr(legacyTypeId, ':') != NULL) {
                        int32_t legacyTypeIdLen = uprv_strlen(legacyTypeId);
                        char* legacyTypeIdBuf = (char*)uprv_malloc(legacyTypeIdLen + 1);
                        if (legacyTypeIdBuf == NULL) {
                            sts = U_MEMORY_ALLOCATION_ERROR;
                            break;
                        }
                        const char* p = legacyTypeId;
                        char* q = legacyTypeIdBuf;
                        while (*p) {
                            if (*p == ':') {
                                *q++ = '/';
                            } else {
                                *q++ = *p;
                            }
                            p++;
                        }
                        *q = 0;

                        gKeyTypeStringPool->addElement(legacyTypeIdBuf, sts);
                        if (U_FAILURE(sts)) {
                            break;
                        }
                        legacyTypeId = legacyTypeIdBuf;
                    }
                }

                int32_t bcpTypeIdLen = 0;
                const UChar* uBcpTypeId = ures_getString(typeMapEntry.getAlias(), &bcpTypeIdLen, &sts);
                if (U_FAILURE(sts)) {
                    break;
                }

                // empty value indicates that BCP type is same with the legacy type.
                const char* bcpTypeId = legacyTypeId;
                if (bcpTypeIdLen > 0) {
                    char* bcpTypeIdBuf = (char*)uprv_malloc(bcpTypeIdLen + 1);
                    if (bcpTypeIdBuf == NULL) {
                        sts = U_MEMORY_ALLOCATION_ERROR;
                        break;
                    }
                    u_UCharsToChars(uBcpTypeId, bcpTypeIdBuf, bcpTypeIdLen);
                    bcpTypeIdBuf[bcpTypeIdLen] = 0;
                    gKeyTypeStringPool->addElement(bcpTypeIdBuf, sts);
                    if (U_FAILURE(sts)) {
                        break;
                    }
                    bcpTypeId = bcpTypeIdBuf;
                }

                // Note: legacy type value should never be
                // equivalent to bcp type value of a different
                // type under the same key. So we use a single
                // map for lookup.
                LocExtType* t = (LocExtType*)uprv_malloc(sizeof(LocExtType));
                if (t == NULL) {
                    sts = U_MEMORY_ALLOCATION_ERROR;
                    break;
                }
                t->bcpId = bcpTypeId;
                t->legacyId = legacyTypeId;
                gLocExtTypeEntries->addElement((void*)t, sts);
                if (U_FAILURE(sts)) {
                    break;
                }

                uhash_put(typeDataMap, (void*)legacyTypeId, t, &sts);
                if (bcpTypeId != legacyTypeId) {
                    // different type value
                    uhash_put(typeDataMap, (void*)bcpTypeId, t, &sts);
                }
                if (U_FAILURE(sts)) {
                    break;
                }

                // also put aliases in the map
                if (typeAliasResByKey.isValid()) {
                    LocalUResourceBundlePointer typeAliasDataEntry;

                    ures_resetIterator(typeAliasResByKey.getAlias());
                    while (ures_hasNext(typeAliasResByKey.getAlias()) && U_SUCCESS(sts)) {
                        int32_t toLen;
                        typeAliasDataEntry.adoptInstead(ures_getNextResource(typeAliasResByKey.getAlias(), typeAliasDataEntry.orphan(), &sts));
                        const UChar* to = ures_getString(typeAliasDataEntry.getAlias(), &toLen, &sts);
                        if (U_FAILURE(sts)) {
                            break;
                        }
                        // check if this is an alias of canoncal legacy type
                        if (uprv_compareInvWithUChar(NULL, legacyTypeId, -1, to, toLen) == 0) {
                            const char* from = ures_getKey(typeAliasDataEntry.getAlias());
                            if (isTZ) {
                                // replace colon with slash if necessary
                                if (uprv_strchr(from, ':') != NULL) {
                                    int32_t fromLen = uprv_strlen(from);
                                    char* fromBuf = (char*)uprv_malloc(fromLen + 1);
                                    if (fromBuf == NULL) {
                                        sts = U_MEMORY_ALLOCATION_ERROR;
                                        break;
                                    }
                                    const char* p = from;
                                    char* q = fromBuf;
                                    while (*p) {
                                        if (*p == ':') {
                                            *q++ = '/';
                                        } else {
                                            *q++ = *p;
                                        }
                                        p++;
                                    }
                                    *q = 0;

                                    gKeyTypeStringPool->addElement(fromBuf, sts);
                                    if (U_FAILURE(sts)) {
                                        break;
                                    }
                                    from = fromBuf;
                                }
                            }
                            uhash_put(typeDataMap, (void*)from, t, &sts);
                        }
                    }
                    if (U_FAILURE(sts)) {
                        break;
                    }
                }

                if (bcpTypeAliasResByKey.isValid()) {
                    LocalUResourceBundlePointer bcpTypeAliasDataEntry;

                    ures_resetIterator(bcpTypeAliasResByKey.getAlias());
                    while (ures_hasNext(bcpTypeAliasResByKey.getAlias()) && U_SUCCESS(sts)) {
                        int32_t toLen;
                        bcpTypeAliasDataEntry.adoptInstead(ures_getNextResource(bcpTypeAliasResByKey.getAlias(), bcpTypeAliasDataEntry.orphan(), &sts));
                        const UChar* to = ures_getString(bcpTypeAliasDataEntry.getAlias(), &toLen, &sts);
                        if (U_FAILURE(sts)) {
                            break;
                        }
                        // check if this is an alias of bcp type
                        if (uprv_compareInvWithUChar(NULL, bcpTypeId, -1, to, toLen) == 0) {
                            const char* from = ures_getKey(bcpTypeAliasDataEntry.getAlias());
                            uhash_put(typeDataMap, (void*)from, t, &sts);
                        }
                    }
                    if (U_FAILURE(sts)) {
                        break;
                    }
                }
            }
        }
        if (U_FAILURE(sts)) {
            break;
        }

        LocExtKeyData* keyData = (LocExtKeyData*)uprv_malloc(sizeof(LocExtKeyData));
        if (keyData == NULL) {
            sts = U_MEMORY_ALLOCATION_ERROR;
            break;
        }
        keyData->bcpId = bcpKeyId;
        keyData->legacyId = legacyKeyId;
        keyData->specialTypes = specialTypes;
        keyData->typeMap = typeDataMap;

        gLocExtKeyDataEntries->addElement((void*)keyData, sts);
        if (U_FAILURE(sts)) {
            break;
        }

        uhash_put(gLocExtKeyMap, (void*)legacyKeyId, keyData, &sts);
        if (legacyKeyId != bcpKeyId) {
            // different key value
            uhash_put(gLocExtKeyMap, (void*)bcpKeyId, keyData, &sts);
        }
        if (U_FAILURE(sts)) {
            break;
        }
    }
}