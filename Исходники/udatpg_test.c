static void TestBuilder() {
    UErrorCode errorCode=U_ZERO_ERROR;
    UDateTimePatternGenerator *dtpg;
    UDateTimePatternConflict conflict;
    UEnumeration *en;
    UChar result[20];
    int32_t length, pLength;  
    const UChar *s, *p;
    const UChar* ptrResult[2]; 
    int32_t count=0;
    UDateTimePatternGenerator *generator;
    int32_t formattedCapacity, resultLen,patternCapacity ;
    UChar   pattern[40], formatted[40];
    UDateFormat *formatter;
    UDate sampleDate = 837039928046.0;
    static const char locale[]= "fr";
    UErrorCode status=U_ZERO_ERROR;
    
    /* test create an empty DateTimePatternGenerator */
    dtpg=udatpg_openEmpty(&errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("udatpg_openEmpty() failed - %s\n", u_errorName(errorCode));
        return;
    }
    
    /* Add a pattern */
    conflict = udatpg_addPattern(dtpg, redundantPattern, 5, FALSE, result, 20, 
                                 &length, &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("udatpg_addPattern() failed - %s\n", u_errorName(errorCode));
        return;
    }
    /* Add a redundant pattern */
    conflict = udatpg_addPattern(dtpg, redundantPattern, 5, FALSE, result, 20,
                                 &length, &errorCode);
    if(conflict == UDATPG_NO_CONFLICT) {
        log_err("udatpg_addPattern() failed to find the duplicate pattern.\n");
        return;
    }
    /* Test pattern == NULL */
    s=NULL;
    length = udatpg_addPattern(dtpg, s, 0, FALSE, result, 20,
                               &length, &errorCode);
    if(!U_FAILURE(errorCode)&&(length!=0) ) {
        log_err("udatpg_addPattern failed in illegal argument - pattern is NULL.\n");
        return;
    }

    /* replace field type */
    errorCode=U_ZERO_ERROR;
    conflict = udatpg_addPattern(dtpg, testPattern2, 7, FALSE, result, 20,
                                 &length, &errorCode);
    if((conflict != UDATPG_NO_CONFLICT)||U_FAILURE(errorCode)) {
        log_err("udatpg_addPattern() failed to add HH:mm v. - %s\n", u_errorName(errorCode));
        return;
    }
    length = udatpg_replaceFieldTypes(dtpg, testPattern2, 7, replacedStr, 4,
                                      result, 20, &errorCode);
    if (U_FAILURE(errorCode) || (length==0) ) {
        log_err("udatpg_replaceFieldTypes failed!\n");
        return;
    }
    
    /* Get all skeletons and the crroespong pattern for each skeleton. */
    ptrResult[0] = testPattern2;
    ptrResult[1] = redundantPattern; 
    count=0;
    en = udatpg_openSkeletons(dtpg, &errorCode);  
    if (U_FAILURE(errorCode) || (length==0) ) {
        log_err("udatpg_openSkeletons failed!\n");
        return;
    }
    while ( (s=uenum_unext(en, &length, &errorCode))!= NULL) {
        p = udatpg_getPatternForSkeleton(dtpg, s, length, &pLength);
        if (U_FAILURE(errorCode) || p==NULL || u_memcmp(p, ptrResult[count], pLength)!=0 ) {
            log_err("udatpg_getPatternForSkeleton failed!\n");
            return;
        }
        count++;
    }
    uenum_close(en);
    
    /* Get all baseSkeletons */
    en = udatpg_openBaseSkeletons(dtpg, &errorCode);
    count=0;
    while ( (s=uenum_unext(en, &length, &errorCode))!= NULL) {
        p = udatpg_getPatternForSkeleton(dtpg, s, length, &pLength);
        if (U_FAILURE(errorCode) || p==NULL || u_memcmp(p, resultBaseSkeletons[count], pLength)!=0 ) {
            log_err("udatpg_getPatternForSkeleton failed!\n");
            return;
        }
        count++;
    }
    if (U_FAILURE(errorCode) || (length==0) ) {
        log_err("udatpg_openSkeletons failed!\n");
        return;
    }
    uenum_close(en);
    
    udatpg_close(dtpg);
    
    /* sample code in Userguide */
    patternCapacity = (int32_t)(sizeof(pattern)/sizeof((pattern)[0]));
    status=U_ZERO_ERROR;
    generator=udatpg_open(locale, &status);
    if(U_FAILURE(status)) {
        return;
    }

    /* get a pattern for an abbreviated month and day */
    length = udatpg_getBestPattern(generator, skeleton, 4,
                                   pattern, patternCapacity, &status);
    formatter = udat_open(UDAT_IGNORE, UDAT_DEFAULT, locale, timeZoneGMT, -1,
                          pattern, length, &status);
    if (formatter==NULL) {
        log_err("Failed to initialize the UDateFormat of the sample code in Userguide.\n");
        udatpg_close(generator);
        return;
    }

    /* use it to format (or parse) */
    formattedCapacity = (int32_t)(sizeof(formatted)/sizeof((formatted)[0]));
    resultLen=udat_format(formatter, ucal_getNow(), formatted, formattedCapacity,
                          NULL, &status);
    /* for French, the result is "13 sept." */

    /* cannot use the result from ucal_getNow() because the value change evreyday. */
    resultLen=udat_format(formatter, sampleDate, formatted, formattedCapacity,
                          NULL, &status);
    if ( u_memcmp(sampleFormatted, formatted, resultLen) != 0 ) {
        log_err("Failed udat_format() of sample code in Userguide.\n");
    }
    udatpg_close(generator);
    udat_close(formatter);
}