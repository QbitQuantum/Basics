static jobjectArray getContentImpl(JNIEnv* env, jclass clazz, 
        jstring locale, jboolean needsTZ) {
    
    UErrorCode status = U_ZERO_ERROR;

    const char *loc = env->GetStringUTFChars(locale, NULL);
    UResourceBundle *root = ures_openU(NULL, loc, &status);

    env->ReleaseStringUTFChars(locale, loc);
    if(U_FAILURE(status)) {
        LOGI("Error getting resources");
        status = U_ZERO_ERROR;
        return NULL;
    }



    jclass obj_class = env->FindClass("java/lang/Object");
    jclass integer_class = env->FindClass("java/lang/Integer");
    jmethodID integerInit = env->GetMethodID(integer_class, "<init>", "(I)V");
    jobjectArray result;

    jobject firstDayOfWeek = NULL;
    jobject minimalDaysInFirstWeek = NULL;
    jobjectArray amPmMarkers = NULL;
    jobjectArray eras = NULL;
    jstring localPatternChars = NULL;
    jobjectArray weekdays = NULL;
    jobjectArray shortWeekdays = NULL;
    jobjectArray months = NULL;
    jobjectArray shortMonths = NULL;
    jstring time_SHORT = NULL;
    jstring time_MEDIUM = NULL;
    jstring time_LONG = NULL;
    jstring time_FULL = NULL;
    jstring date_SHORT = NULL;
    jstring date_MEDIUM = NULL;
    jstring date_LONG = NULL;
    jstring date_FULL = NULL;
    jstring decimalPatternChars = NULL;
    jstring naN = NULL;
    jstring infinity = NULL;
    jstring currencySymbol = NULL;
    jstring intCurrencySymbol = NULL;
    jstring numberPattern = NULL;
    jstring integerPattern = NULL;
    jstring currencyPattern = NULL;
    jstring percentPattern = NULL;
    jobjectArray zones = NULL;

    int counter = 0;

    int firstDayVals[2] = {-1, -1};

    const jchar* nan = (const jchar *)NULL;
    const jchar* inf = (const jchar *)NULL;
    int nanL, infL;


    UResourceBundle *gregorian;
    UResourceBundle *gregorianElems;
    UResourceBundle *rootElems;




    // get the resources needed
    rootElems = ures_getByKey(root, "calendar", NULL, &status);
    if(U_FAILURE(status)) {
        return NULL;
    }

    gregorian = ures_getByKey(rootElems, "gregorian", NULL, &status);
    if(U_FAILURE(status)) {
        ures_close(rootElems);
        return NULL;
    }



    // adding the first day of week and minimal days in first week values
    getDayInitVector(env, gregorian, firstDayVals);
    if((firstDayVals[0] != -1) && (firstDayVals[1] != -1)) {
        firstDayOfWeek = env->NewObject(integer_class, integerInit, firstDayVals[0]);
        minimalDaysInFirstWeek = env->NewObject(integer_class, integerInit, firstDayVals[1]);
        // adding First_Day and Minimal_Days integer to the result
        counter += 2;
    }


    // adding ampm string array to the result");
    amPmMarkers = getAmPmMarkers(env, gregorian);
    if(amPmMarkers != NULL) {
        counter++;
    }


    // adding eras string array to the result
    eras = getEras(env, gregorian);
    if(eras != NULL) {
        counter++;
    }


    // local pattern chars are initially always the same
    localPatternChars = env->NewStringUTF("GyMdkHmsSEDFwWahKzZ");
    // adding local pattern chars string to the result
    counter++;


    // adding month names string array to the result
    months = getMonthNames(env, gregorian);
    if(months != NULL) {
        counter++;
    }


    // adding short month names string array to the result
    shortMonths = getShortMonthNames(env, gregorian);
    if(shortMonths != NULL) {
        counter++;
    }


    // adding day names string array to the result
    weekdays = getWeekdayNames(env, gregorian);
    if(weekdays != NULL) {
        counter++;
    }


    // adding short day names string array to the result
    shortWeekdays = getShortWeekdayNames(env, gregorian);
    if(shortWeekdays != NULL) {
        counter++;
    }

    const UChar *pattern;
    jchar check[2] = {0, 0};
    u_uastrcpy(check, "v");
    jchar replacement[2] = {0, 0};
    u_uastrcpy(replacement, "z");
    jchar *pos;
    jchar *patternCopy;
    int patternLength;

    // adding date and time format patterns to the result
    gregorianElems = ures_getByKey(gregorian, "DateTimePatterns", NULL, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }

    pattern = ures_getStringByIndex(gregorianElems, 0, &patternLength, &status);
    // there are some patterns in icu that use the pattern character 'v'
    // java doesn't accept this, so it gets replaced by 'z' which has
    // about the same result as 'v', the timezone name. 
    // 'v' -> "PT", 'z' -> "PST", v is the generic timezone and z the standard tz
    // "vvvv" -> "Pacific Time", "zzzz" -> "Pacific Standard Time"
    patternCopy = (jchar *) malloc((patternLength + 1) * sizeof(jchar));
    u_strcpy(patternCopy, pattern);
    if(U_FAILURE(status)) {
        free(patternCopy);
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    while((pos = u_strchr(patternCopy, check[0])) != NULL) {
        u_memset(pos, replacement[0], 1);
    }
    time_FULL = env->NewString(patternCopy, patternLength);
    free(patternCopy);
    counter++;

    pattern = ures_getStringByIndex(gregorianElems, 1, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    time_LONG = env->NewString(pattern, patternLength);
    counter++;

    pattern = ures_getStringByIndex(gregorianElems, 2, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    time_MEDIUM = env->NewString(pattern, patternLength);
    counter++;

    pattern = ures_getStringByIndex(gregorianElems, 3, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    time_SHORT = env->NewString(pattern, patternLength);
    counter++;

    pattern = ures_getStringByIndex(gregorianElems, 4, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    date_FULL = env->NewString(pattern, patternLength);
    counter++;

    pattern = ures_getStringByIndex(gregorianElems, 5, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    date_LONG = env->NewString(pattern, patternLength);
    counter++;

    pattern = ures_getStringByIndex(gregorianElems, 6, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    date_MEDIUM = env->NewString(pattern, patternLength);
    counter++;

    pattern = ures_getStringByIndex(gregorianElems, 7, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto endOfCalendar;
    }
    date_SHORT = env->NewString(pattern, patternLength);
    counter++;


endOfCalendar:

    if(gregorianElems != NULL) {
        ures_close(gregorianElems);
    }
    ures_close(gregorian);
    ures_close(rootElems);


    rootElems = ures_getByKey(root, "NumberElements", NULL, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
    }

    if(ures_getSize(rootElems) >= 11) {

        // adding decimal pattern chars to the result
        decimalPatternChars = getDecimalPatternChars(env, rootElems);
        if(decimalPatternChars != NULL) {
            counter++;
        }

        // adding NaN pattern char to the result
        nan = ures_getStringByIndex(rootElems, 10, &nanL, &status);
        if(U_SUCCESS(status)) {
            naN = env->NewString(nan, nanL);
            counter++;
        }
        status = U_ZERO_ERROR;

        // adding infinity pattern char to the result
        inf = ures_getStringByIndex(rootElems, 9, &infL, &status);
        if(U_SUCCESS(status)) {
            infinity = env->NewString(inf, infL);
            counter++;
        }
        status = U_ZERO_ERROR;
    }

    ures_close(rootElems);


    // adding intl currency code to result
    intCurrencySymbol = getIntCurrencyCode(env, clazz, locale);
    if(intCurrencySymbol != NULL) {
        // adding currency symbol to result
        currencySymbol = getCurrencySymbol(env, clazz, locale, intCurrencySymbol);
    } else {
        intCurrencySymbol = env->NewStringUTF("XXX");
    }
    if(currencySymbol == NULL) {
        currencySymbol = env->NewStringUTF("\u00a4");
    }
    counter += 2;


    // adding number format patterns to the result
    int numOfEntries;
    int decSepOffset;
    NumberFormat *nf;
    jchar *tmpPattern;

    rootElems = ures_getByKey(root, "NumberPatterns", NULL, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        goto zones;
    }

    numOfEntries = ures_getSize(rootElems);
    if(numOfEntries < 3) {
        ures_close(rootElems);
        goto zones;
    }

    // number pattern
    pattern = ures_getStringByIndex(rootElems, 0, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        ures_close(rootElems);
        goto zones;
    }
    numberPattern = env->NewString(pattern, patternLength);
    counter++;

    // integer pattern derived from number pattern
    decSepOffset = u_strcspn(pattern, (jchar *)".\0");
    tmpPattern =  (jchar *) malloc((decSepOffset + 1) * sizeof(jchar));
    u_strncpy(tmpPattern, pattern, decSepOffset);
    integerPattern = env->NewString(tmpPattern, decSepOffset);
    free(tmpPattern);
    counter++;

    // currency pattern
    pattern = ures_getStringByIndex(rootElems, 1, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        ures_close(rootElems);
        goto zones;
    }
    currencyPattern = env->NewString(pattern, patternLength);
    counter++;

    // percent pattern
    pattern = ures_getStringByIndex(rootElems, 2, &patternLength, &status);
    if(U_FAILURE(status)) {
        status = U_ZERO_ERROR;
        ures_close(rootElems);
        goto zones;
    }
    percentPattern = env->NewString(pattern, patternLength);
    counter++;

    ures_close(rootElems);

zones:

    ures_close(root);


    if(needsTZ == JNI_TRUE) {
        counter++; //add empty timezone
    }



    // collect all content and put it into an array
    result = env->NewObjectArray(counter, obj_class, NULL);

    int index = 0;
    
    if(needsTZ == JNI_TRUE) {
        addObject(env, result, "timezones", NULL, index++);
    }
    if(firstDayOfWeek != NULL && index < counter) {
        addObject(env, result, "First_Day", firstDayOfWeek, index++);
    }
    if(minimalDaysInFirstWeek != NULL && index < counter) {
        addObject(env, result, "Minimal_Days", minimalDaysInFirstWeek, index++);
    }
    if(amPmMarkers != NULL && index < counter) {
        addObject(env, result, "ampm", amPmMarkers, index++);
    }
    if(eras != NULL && index < counter) {
        addObject(env, result, "eras", eras, index++);
    }
    if(localPatternChars != NULL && index < counter) {
        addObject(env, result, "LocalPatternChars", localPatternChars, index++);
    }
    if(weekdays != NULL && index < counter) {
        addObject(env, result, "weekdays", weekdays, index++);
    }
    if(shortWeekdays != NULL && index < counter) {
        addObject(env, result, "shortWeekdays", shortWeekdays, index++);
    }
    if(months != NULL && index < counter) {
        addObject(env, result, "months", months, index++);
    }
    if(shortMonths != NULL && index < counter) {
        addObject(env, result, "shortMonths", shortMonths, index++);
    }
    if(time_SHORT != NULL && index < counter) {
        addObject(env, result, "Time_SHORT", time_SHORT, index++);
    }
    if(time_MEDIUM != NULL && index < counter) {
        addObject(env, result, "Time_MEDIUM", time_MEDIUM, index++);
    }
    if(time_LONG != NULL && index < counter) {
        addObject(env, result, "Time_LONG", time_LONG, index++);
    }
    if(time_FULL != NULL && index < counter) {
        addObject(env, result, "Time_FULL", time_FULL, index++);
    }
    if(date_SHORT != NULL && index < counter) {
        addObject(env, result, "Date_SHORT", date_SHORT, index++);
    }
    if(date_MEDIUM != NULL && index < counter) {
        addObject(env, result, "Date_MEDIUM", date_MEDIUM, index++);
    }
    if(date_LONG != NULL && index < counter) {
        addObject(env, result, "Date_LONG", date_LONG, index++);
    }
    if(date_FULL != NULL && index < counter) {
        addObject(env, result, "Date_FULL", date_FULL, index++);
    }
    if(decimalPatternChars != NULL && index < counter) {
        addObject(env, result, "DecimalPatternChars", decimalPatternChars, index++);
    }
    if(naN != NULL && index < counter) {
        addObject(env, result, "NaN", naN, index++);
    }
    if(infinity != NULL && index < counter) {
        addObject(env, result, "Infinity", infinity, index++);
    }
    if(currencySymbol != NULL && index < counter) {
        addObject(env, result, "CurrencySymbol", currencySymbol, index++);
    }
    if(intCurrencySymbol != NULL && index < counter) {
        addObject(env, result, "IntCurrencySymbol", intCurrencySymbol, index++);
    }
    if(numberPattern != NULL && index < counter) {
        addObject(env, result, "Number", numberPattern, index++);
    }
    if(integerPattern != NULL && index < counter) {
        addObject(env, result, "Integer", integerPattern, index++);
    }
    if(currencyPattern != NULL && index < counter) {
        addObject(env, result, "Currency", currencyPattern, index++);
    }
    if(percentPattern != NULL && index < counter) {
        addObject(env, result, "Percent", percentPattern, index++);
    }

    return result;

}