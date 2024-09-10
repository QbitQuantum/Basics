U_NAMESPACE_BEGIN

// -------------------------------------

BreakIterator*
BreakIterator::buildInstance(const Locale& loc, const char *type, int32_t kind, UErrorCode &status)
{
    char fnbuff[256];
    char ext[4]={'\0'};
    char actualLocale[ULOC_FULLNAME_CAPACITY];
    int32_t size;
    const UChar* brkfname = NULL;
    UResourceBundle brkRulesStack;
    UResourceBundle brkNameStack;
    UResourceBundle *brkRules = &brkRulesStack;
    UResourceBundle *brkName  = &brkNameStack;
    RuleBasedBreakIterator *result = NULL;

    if (U_FAILURE(status))
        return NULL;

    ures_initStackObject(brkRules);
    ures_initStackObject(brkName);

    // Get the locale
    UResourceBundle *b = ures_open(U_ICUDATA_BRKITR, loc.getName(), &status);
    /* this is a hack for now. Should be fixed when the data is fetched from
        brk_index.txt */
    if(status==U_USING_DEFAULT_WARNING){
        status=U_ZERO_ERROR;
        ures_openFillIn(b, U_ICUDATA_BRKITR, "", &status);
    }

    // Get the "boundaries" array.
    if (U_SUCCESS(status)) {
        brkRules = ures_getByKeyWithFallback(b, "boundaries", brkRules, &status);
        // Get the string object naming the rules file
        brkName = ures_getByKeyWithFallback(brkRules, type, brkName, &status);
        // Get the actual string
        brkfname = ures_getString(brkName, &size, &status);
        U_ASSERT((size_t)size<sizeof(fnbuff));
        if ((size_t)size>=sizeof(fnbuff)) {
            size=0;
            if (U_SUCCESS(status)) {
                status = U_BUFFER_OVERFLOW_ERROR;
            }
        }

        // Use the string if we found it
        if (U_SUCCESS(status) && brkfname) {
            uprv_strncpy(actualLocale,
                ures_getLocale(brkName, &status),
                sizeof(actualLocale)/sizeof(actualLocale[0]));

            UChar* extStart=u_strchr(brkfname, 0x002e);
            int len = 0;
            if(extStart!=NULL){
                len = (int)(extStart-brkfname);
                u_UCharsToChars(extStart+1, ext, sizeof(ext)); // nul terminates the buff
                u_UCharsToChars(brkfname, fnbuff, len);
            }
            fnbuff[len]=0; // nul terminate
        }
    }

    ures_close(brkRules);
    ures_close(brkName);

    UDataMemory* file = udata_open(U_ICUDATA_BRKITR, ext, fnbuff, &status);
    if (U_FAILURE(status)) {
        ures_close(b);
        return NULL;
    }

    // Create a RuleBasedBreakIterator
    result = new RuleBasedBreakIterator(file, status);

    // If there is a result, set the valid locale and actual locale, and the kind
    if (U_SUCCESS(status) && result != NULL) {
        U_LOCALE_BASED(locBased, *(BreakIterator*)result);
        locBased.setLocaleIDs(ures_getLocaleByType(b, ULOC_VALID_LOCALE, &status), actualLocale);
        result->setBreakType(kind);
    }

    ures_close(b);

    if (U_FAILURE(status) && result != NULL) {  // Sometimes redundant check, but simple
        delete result;
        return NULL;
    }

    if (result == NULL) {
        udata_close(file);
        if (U_SUCCESS(status)) {
            status = U_MEMORY_ALLOCATION_ERROR;
        }
    }

    return result;
}