RegexStaticSets::RegexStaticSets(UErrorCode *status)
:
fUnescapeCharSet(UnicodeString(TRUE, gUnescapeCharPattern, -1), *status),
fRuleDigitsAlias(NULL),
fEmptyText(NULL)
{
    // First zero out everything
    int i;
    for (i=0; i<URX_LAST_SET; i++) {
        fPropSets[i] = NULL;
    }
    // Then init the sets to their correct values.
    fPropSets[URX_ISWORD_SET]  = new UnicodeSet(UnicodeString(TRUE, gIsWordPattern, -1),     *status);
    fPropSets[URX_ISSPACE_SET] = new UnicodeSet(UnicodeString(TRUE, gIsSpacePattern, -1),    *status);
    fPropSets[URX_GC_EXTEND]   = new UnicodeSet(UnicodeString(TRUE, gGC_ExtendPattern, -1),  *status);
    fPropSets[URX_GC_CONTROL]  = new UnicodeSet(UnicodeString(TRUE, gGC_ControlPattern, -1), *status);
    fPropSets[URX_GC_L]        = new UnicodeSet(UnicodeString(TRUE, gGC_LPattern, -1),       *status);
    fPropSets[URX_GC_V]        = new UnicodeSet(UnicodeString(TRUE, gGC_VPattern, -1),       *status);
    fPropSets[URX_GC_T]        = new UnicodeSet(UnicodeString(TRUE, gGC_TPattern, -1),       *status);
    fPropSets[URX_GC_LV]       = new UnicodeSet(UnicodeString(TRUE, gGC_LVPattern, -1),      *status);
    fPropSets[URX_GC_LVT]      = new UnicodeSet(UnicodeString(TRUE, gGC_LVTPattern, -1),     *status);
    
    // Check for null pointers
    if (fPropSets[URX_ISWORD_SET] == NULL || fPropSets[URX_ISSPACE_SET] == NULL || fPropSets[URX_GC_EXTEND] == NULL || 
        fPropSets[URX_GC_CONTROL] == NULL || fPropSets[URX_GC_L] == NULL || fPropSets[URX_GC_V] == NULL || 
        fPropSets[URX_GC_T] == NULL || fPropSets[URX_GC_LV] == NULL || fPropSets[URX_GC_LVT] == NULL) {
        goto ExitConstrDeleteAll;
    }
    if (U_FAILURE(*status)) {
        // Bail out if we were unable to create the above sets.
        // The rest of the initialization needs them, so we cannot proceed.
        return;
    }


    //
    // The following sets  are dynamically constructed, because their
    //   initialization strings would be unreasonable.
    //


    //
    //  "Normal" is the set of characters that don't need special handling
    //            when finding grapheme cluster boundaries.
    //
    fPropSets[URX_GC_NORMAL] = new UnicodeSet(0, UnicodeSet::MAX_VALUE);
    // Null pointer check
    if (fPropSets[URX_GC_NORMAL] == NULL) {
    	goto ExitConstrDeleteAll;
    }
    fPropSets[URX_GC_NORMAL]->remove(0xac00, 0xd7a4);
    fPropSets[URX_GC_NORMAL]->removeAll(*fPropSets[URX_GC_CONTROL]);
    fPropSets[URX_GC_NORMAL]->removeAll(*fPropSets[URX_GC_L]);
    fPropSets[URX_GC_NORMAL]->removeAll(*fPropSets[URX_GC_V]);
    fPropSets[URX_GC_NORMAL]->removeAll(*fPropSets[URX_GC_T]);

    // Initialize the 8-bit fast bit sets from the parallel full
    //   UnicodeSets.
    for (i=0; i<URX_LAST_SET; i++) {
        if (fPropSets[i]) {
            fPropSets[i]->compact();
            fPropSets8[i].init(fPropSets[i]);
        }
    }

    // Sets used while parsing rules, but not referenced from the parse state table
    fRuleSets[kRuleSet_rule_char-128]   = UnicodeSet(UnicodeString(TRUE, gRuleSet_rule_char_pattern, -1),   *status);
    fRuleSets[kRuleSet_digit_char-128].add((UChar)0x30, (UChar)0x39);    // [0-9]
    fRuleSets[kRuleSet_ascii_letter-128].add((UChar)0x41, (UChar)0x5A);  // [A-Z]
    fRuleSets[kRuleSet_ascii_letter-128].add((UChar)0x61, (UChar)0x7A);  // [a-z]
    fRuleDigitsAlias = &fRuleSets[kRuleSet_digit_char-128];
    for (i=0; i<UPRV_LENGTHOF(fRuleSets); i++) {
        fRuleSets[i].compact();
    }
    
    // Finally, initialize an empty string for utility purposes
    fEmptyText = utext_openUChars(NULL, NULL, 0, status);
    
    if (U_SUCCESS(*status)) {
        return;
    }

ExitConstrDeleteAll: // Remove fPropSets and fRuleSets and return error
    for (i=0; i<URX_LAST_SET; i++) {
        delete fPropSets[i];
        fPropSets[i] = NULL;
    }
    if (U_SUCCESS(*status)) {
        *status = U_MEMORY_ALLOCATION_ERROR;
    }
}