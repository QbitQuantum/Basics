/**
 * Main Windows time zone detection function.  Returns the Windows
 * time zone, translated to an ICU time zone, or NULL upon failure.
 */
U_CFUNC const char* U_EXPORT2
uprv_detectWindowsTimeZone() {
    UErrorCode status = U_ZERO_ERROR;
    UResourceBundle* bundle = NULL;
    char* icuid = NULL;
    UChar apiStd[MAX_LENGTH_ID];
    char apiStdName[MAX_LENGTH_ID];
    char regStdName[MAX_LENGTH_ID];
    char tmpid[MAX_LENGTH_ID];
    int32_t len;
    int id;
    int errorCode;
    char ISOcode[3]; /* 2 letter iso code */

    LONG result;
    TZI tziKey;
    TZI tziReg;
    TIME_ZONE_INFORMATION apiTZI;

    /* Obtain TIME_ZONE_INFORMATION from the API, and then convert it
       to TZI.  We could also interrogate the registry directly; we do
       this below if needed. */
    uprv_memset(&apiTZI, 0, sizeof(apiTZI));
    uprv_memset(&tziKey, 0, sizeof(tziKey));
    uprv_memset(&tziReg, 0, sizeof(tziReg));
    GetTimeZoneInformation(&apiTZI);
    tziKey.bias = apiTZI.Bias;
    uprv_memcpy((char *)&tziKey.standardDate, (char*)&apiTZI.StandardDate,
           sizeof(apiTZI.StandardDate));
    uprv_memcpy((char *)&tziKey.daylightDate, (char*)&apiTZI.DaylightDate,
           sizeof(apiTZI.DaylightDate));

    /* Convert the wchar_t* standard name to char* */
    uprv_memset(apiStdName, 0, sizeof(apiStdName));
    u_strFromWCS(apiStd, MAX_LENGTH_ID, NULL, apiTZI.StandardName, -1, &status);
    u_austrncpy(apiStdName, apiStd, sizeof(apiStdName) - 1);

    tmpid[0] = 0;

    id = GetUserGeoID(GEOCLASS_NATION);
    errorCode = GetGeoInfoA(id,GEO_ISO2,ISOcode,3,0);

    bundle = ures_openDirect(NULL, "windowsZones", &status);
    ures_getByKey(bundle, "mapTimezones", bundle, &status);

    /* Note: We get the winid not from static tables but from resource bundle. */
    while (U_SUCCESS(status) && ures_hasNext(bundle)) {
        UBool idFound = FALSE;
        const char* winid;
        UResourceBundle* winTZ = ures_getNextResource(bundle, NULL, &status);
        if (U_FAILURE(status)) {
            break;
        }
        winid = ures_getKey(winTZ);
        result = getTZI(winid, &tziReg);

        if (result == ERROR_SUCCESS) {
            /* Windows alters the DaylightBias in some situations.
               Using the bias and the rules suffices, so overwrite
               these unreliable fields. */
            tziKey.standardBias = tziReg.standardBias;
            tziKey.daylightBias = tziReg.daylightBias;

            if (uprv_memcmp((char *)&tziKey, (char*)&tziReg, sizeof(tziKey)) == 0) {
                const UChar* icuTZ = NULL;
                if (errorCode != 0) {
                    icuTZ = ures_getStringByKey(winTZ, ISOcode, &len, &status);
                }
                if (errorCode==0 || icuTZ==NULL) {
                    /* fallback to default "001" and reset status */
                    status = U_ZERO_ERROR;
                    icuTZ = ures_getStringByKey(winTZ, "001", &len, &status);
                }

                if (U_SUCCESS(status)) {
                    /* Get the standard name from the registry key to compare with
                       the one from Windows API call. */
                    uprv_memset(regStdName, 0, sizeof(regStdName));
                    result = getSTDName(winid, regStdName, sizeof(regStdName));
                    if (result == ERROR_SUCCESS) {
                        if (uprv_strcmp(apiStdName, regStdName) == 0) {
                            idFound = TRUE;
                        }
                    }

                    /* tmpid buffer holds the ICU timezone ID corresponding to the timezone ID from Windows.
                     * If none is found, tmpid buffer will contain a fallback ID (i.e. the time zone ID matching
                     * the current time zone information)
                     */
                    if (idFound || tmpid[0] == 0) {
                        /* if icuTZ has more than one city, take only the first (i.e. terminate icuTZ at first space) */
                        int index=0;
                        while (! (*icuTZ == '\0' || *icuTZ ==' ')) {
                            tmpid[index++]=(char)(*icuTZ++);  /* safe to assume 'char' is ASCII compatible on windows */
                        }
                        tmpid[index]='\0';
                    }
                }
            }
        }
        ures_close(winTZ);
        if (idFound) {
            break;
        }
    }

    /*
     * Copy the timezone ID to icuid to be returned.
     */
    if (tmpid[0] != 0) {
        len = uprv_strlen(tmpid);
        icuid = (char*)uprv_calloc(len + 1, sizeof(char));
        if (icuid != NULL) {
            uprv_strcpy(icuid, tmpid);
        }
    }

    ures_close(bundle);
    
    return icuid;
}