void RelativeDateFormat::loadDates(UErrorCode &status) {
    CalendarData calData(fLocale, "gregorian", status);
    
    UErrorCode tempStatus = status;
    UResourceBundle *dateTimePatterns = calData.getByKey(DT_DateTimePatternsTag, tempStatus);
    if(U_SUCCESS(tempStatus)) {
        int32_t patternsSize = ures_getSize(dateTimePatterns);
        if (patternsSize > kDateTime) {
            int32_t resStrLen = 0;

            int32_t glueIndex = kDateTime;
            if (patternsSize >= (DateFormat::kDateTimeOffset + DateFormat::kShort + 1)) {
                // Get proper date time format
                switch (fDateStyle) { 
                case kFullRelative: 
                case kFull: 
                    glueIndex = kDateTimeOffset + kFull; 
                    break; 
                case kLongRelative: 
                case kLong: 
                    glueIndex = kDateTimeOffset + kLong; 
                    break; 
                case kMediumRelative: 
                case kMedium: 
                    glueIndex = kDateTimeOffset + kMedium; 
                    break;         
                case kShortRelative: 
                case kShort: 
                    glueIndex = kDateTimeOffset + kShort; 
                    break; 
                default: 
                    break; 
                } 
            }

            const UChar *resStr = ures_getStringByIndex(dateTimePatterns, glueIndex, &resStrLen, &tempStatus);
            if (U_SUCCESS(tempStatus) && resStrLen >= patItem1Len && u_strncmp(resStr,patItem1,patItem1Len)==0) {
                fCombinedHasDateAtStart = TRUE;
            }
            fCombinedFormat = new SimpleFormatter(UnicodeString(TRUE, resStr, resStrLen), 2, 2, tempStatus);
        }
    }

    UResourceBundle *rb = ures_open(NULL, fLocale.getBaseName(), &status);
    rb = ures_getByKeyWithFallback(rb, "fields", rb, &status);
    rb = ures_getByKeyWithFallback(rb, "day", rb, &status);
    rb = ures_getByKeyWithFallback(rb, "relative", rb, &status);
    // set up min/max 
    fDayMin=-1;
    fDayMax=1;

    if(U_FAILURE(status)) {
        fDatesLen=0;
        ures_close(rb);
        return;
    }

    fDatesLen = ures_getSize(rb);
    fDates = (URelativeString*) uprv_malloc(sizeof(fDates[0])*fDatesLen);

    // Load in each item into the array...
    int n = 0;

    UResourceBundle *subString = NULL;
    
    while(ures_hasNext(rb) && U_SUCCESS(status)) {  // iterate over items
        subString = ures_getNextResource(rb, subString, &status);
        
        if(U_FAILURE(status) || (subString==NULL)) break;
        
        // key = offset #
        const char *key = ures_getKey(subString);
        
        // load the string and length
        int32_t aLen;
        const UChar* aString = ures_getString(subString, &aLen, &status);
        
        if(U_FAILURE(status) || aString == NULL) break;

        // calculate the offset
        int32_t offset = atoi(key);
        
        // set min/max
        if(offset < fDayMin) {
            fDayMin = offset;
        }
        if(offset > fDayMax) {
            fDayMax = offset;
        }
        
        // copy the string pointer
        fDates[n].offset = offset;
        fDates[n].string = aString;
        fDates[n].len = aLen; 

        n++;
    }
    ures_close(subString);
    ures_close(rb);
    
    // the fDates[] array could be sorted here, for direct access.
}