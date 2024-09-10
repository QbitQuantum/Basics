UBool Transliterator::initializeRegistry(UErrorCode &status) {
    if (registry != 0) {
        return TRUE;
    }

    registry = new TransliteratorRegistry(status);
    if (registry == 0 || U_FAILURE(status)) {
        delete registry;
        registry = 0;
        return FALSE; // can't create registry, no recovery
    }

    /* The following code parses the index table located in
     * icu/data/translit/root.txt.  The index is an n x 4 table
     * that follows this format:
     *  <id>{
     *      file{
     *          resource{"<resource>"}
     *          direction{"<direction>"}
     *      }
     *  }
     *  <id>{
     *      internal{
     *          resource{"<resource>"}
     *          direction{"<direction"}
     *       }
     *  }
     *  <id>{
     *      alias{"<getInstanceArg"}
     *  }
     * <id> is the ID of the system transliterator being defined.  These
     * are public IDs enumerated by Transliterator.getAvailableIDs(),
     * unless the second field is "internal".
     * 
     * <resource> is a ResourceReader resource name.  Currently these refer
     * to file names under com/ibm/text/resources.  This string is passed
     * directly to ResourceReader, together with <encoding>.
     * 
     * <direction> is either "FORWARD" or "REVERSE".
     * 
     * <getInstanceArg> is a string to be passed directly to
     * Transliterator.getInstance().  The returned Transliterator object
     * then has its ID changed to <id> and is returned.
     *
     * The extra blank field on "alias" lines is to make the array square.
     */
    //static const char translit_index[] = "translit_index";

    UResourceBundle *bundle, *transIDs, *colBund;
    bundle = ures_open(U_ICUDATA_TRANSLIT, NULL/*open default locale*/, &status);
    transIDs = ures_getByKey(bundle, RB_RULE_BASED_IDS, 0, &status);

    int32_t row, maxRows;
    if (U_SUCCESS(status)) {
        maxRows = ures_getSize(transIDs);
        for (row = 0; row < maxRows; row++) {
            colBund = ures_getByIndex(transIDs, row, 0, &status);
            if (U_SUCCESS(status)) {
                UnicodeString id(ures_getKey(colBund), -1, US_INV);
                UResourceBundle* res = ures_getNextResource(colBund, NULL, &status);
                const char* typeStr = ures_getKey(res);
                UChar type;
                u_charsToUChars(typeStr, &type, 1);

                if (U_SUCCESS(status)) {
                    int32_t len = 0;
                    const UChar *resString;
                    switch (type) {
                    case 0x66: // 'f'
                    case 0x69: // 'i'
                        // 'file' or 'internal';
                        // row[2]=resource, row[3]=direction
                        {
                            
                            resString = ures_getStringByKey(res, "resource", &len, &status);
                            UBool visible = (type == 0x0066 /*f*/);
                            UTransDirection dir = 
                                (ures_getUnicodeStringByKey(res, "direction", &status).charAt(0) ==
                                 0x0046 /*F*/) ?
                                UTRANS_FORWARD : UTRANS_REVERSE;
                            registry->put(id, UnicodeString(TRUE, resString, len), dir, TRUE, visible, status);
                        }
                        break;
                    case 0x61: // 'a'
                        // 'alias'; row[2]=createInstance argument
                        resString = ures_getString(res, &len, &status);
                        registry->put(id, UnicodeString(TRUE, resString, len), TRUE, TRUE, status);
                        break;
                    }
                }
                ures_close(res);
            }
            ures_close(colBund);
        }
    }

    ures_close(transIDs);
    ures_close(bundle);

    // Manually add prototypes that the system knows about to the
    // cache.  This is how new non-rule-based transliterators are
    // added to the system.
    
    // This is to allow for null pointer check
    NullTransliterator* tempNullTranslit = new NullTransliterator();
    LowercaseTransliterator* tempLowercaseTranslit = new LowercaseTransliterator();
    UppercaseTransliterator* tempUppercaseTranslit = new UppercaseTransliterator();
    TitlecaseTransliterator* tempTitlecaseTranslit = new TitlecaseTransliterator();
    UnicodeNameTransliterator* tempUnicodeTranslit = new UnicodeNameTransliterator();
    NameUnicodeTransliterator* tempNameUnicodeTranslit = new NameUnicodeTransliterator();
#if !UCONFIG_NO_BREAK_ITERATION
     // TODO: could or should these transliterators be referenced polymorphically once constructed?
     BreakTransliterator* tempBreakTranslit         = new BreakTransliterator();
#endif
    // Check for null pointers
    if (tempNullTranslit == NULL || tempLowercaseTranslit == NULL || tempUppercaseTranslit == NULL ||
        tempTitlecaseTranslit == NULL || tempUnicodeTranslit == NULL || 
#if !UCONFIG_NO_BREAK_ITERATION
        tempBreakTranslit == NULL ||
#endif
        tempNameUnicodeTranslit == NULL )
    {
        delete tempNullTranslit;
        delete tempLowercaseTranslit;
        delete tempUppercaseTranslit;
        delete tempTitlecaseTranslit;
        delete tempUnicodeTranslit;
        delete tempNameUnicodeTranslit;
#if !UCONFIG_NO_BREAK_ITERATION
        delete tempBreakTranslit;
#endif
        // Since there was an error, remove registry
        delete registry;
        registry = NULL;

        status = U_MEMORY_ALLOCATION_ERROR;
        return 0;
    }

    registry->put(tempNullTranslit, TRUE, status);
    registry->put(tempLowercaseTranslit, TRUE, status);
    registry->put(tempUppercaseTranslit, TRUE, status);
    registry->put(tempTitlecaseTranslit, TRUE, status);
    registry->put(tempUnicodeTranslit, TRUE, status);
    registry->put(tempNameUnicodeTranslit, TRUE, status);
#if !UCONFIG_NO_BREAK_ITERATION
    registry->put(tempBreakTranslit, FALSE, status);   // FALSE means invisible.
#endif

    RemoveTransliterator::registerIDs(); // Must be within mutex
    EscapeTransliterator::registerIDs();
    UnescapeTransliterator::registerIDs();
    NormalizationTransliterator::registerIDs();
    AnyTransliterator::registerIDs();

    _registerSpecialInverse(UNICODE_STRING_SIMPLE("Null"),
                            UNICODE_STRING_SIMPLE("Null"), FALSE);
    _registerSpecialInverse(UNICODE_STRING_SIMPLE("Upper"),
                            UNICODE_STRING_SIMPLE("Lower"), TRUE);
    _registerSpecialInverse(UNICODE_STRING_SIMPLE("Title"),
                            UNICODE_STRING_SIMPLE("Lower"), FALSE);

    ucln_i18n_registerCleanup(UCLN_I18N_TRANSLITERATOR, utrans_transliterator_cleanup);

    return TRUE;
}