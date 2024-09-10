RuleBasedNumberFormat::RuleBasedNumberFormat(URBNFRuleSetTag tag, const Locale& alocale, UErrorCode& status)
  : ruleSets(NULL)
  , defaultRuleSet(NULL)
  , locale(alocale)
  , collator(NULL)
  , decimalFormatSymbols(NULL)
  , lenient(FALSE)
  , lenientParseRules(NULL)
  , localizations(NULL)
{
    if (U_FAILURE(status)) {
        return;
    }

    const char* rules_tag = "RBNFRules";
    const char* fmt_tag = "";
    switch (tag) {
    case URBNF_SPELLOUT: fmt_tag = "SpelloutRules"; break;
    case URBNF_ORDINAL: fmt_tag = "OrdinalRules"; break;
    case URBNF_DURATION: fmt_tag = "DurationRules"; break;
    case URBNF_NUMBERING_SYSTEM: fmt_tag = "NumberingSystemRules"; break;
    default: status = U_ILLEGAL_ARGUMENT_ERROR; return;
    }

    // TODO: read localization info from resource
    LocalizationInfo* locinfo = NULL;

    int32_t len = 0;
    UResourceBundle* nfrb = ures_open(U_ICUDATA_RBNF, locale.getName(), &status);
    if (U_SUCCESS(status)) {
        setLocaleIDs(ures_getLocaleByType(nfrb, ULOC_VALID_LOCALE, &status),
                     ures_getLocaleByType(nfrb, ULOC_ACTUAL_LOCALE, &status));

        UResourceBundle* rbnfRules = ures_getByKeyWithFallback(nfrb, rules_tag, NULL, &status);
        if (U_FAILURE(status)) {
            ures_close(nfrb);
        }
        UResourceBundle* ruleSets = ures_getByKeyWithFallback(rbnfRules, fmt_tag, NULL, &status);
        if (U_FAILURE(status)) {
            ures_close(rbnfRules);
            ures_close(nfrb);
            return;
        }
        
        UnicodeString desc;
        while (ures_hasNext(ruleSets)) {
           const UChar* currentString = ures_getNextString(ruleSets,&len,NULL,&status);
           desc.append(currentString);
        }
        UParseError perror;
        

        init (desc, locinfo, perror, status);

        //TODO: we need a real fix - see #6895 / #6896
        noParse = FALSE;
        if (tag == URBNF_SPELLOUT) {
            const char *lang = alocale.getLanguage();
            for (int32_t i = 0; NO_SPELLOUT_PARSE_LANGUAGES[i] != NULL; i++) {
                if (uprv_strcmp(lang, NO_SPELLOUT_PARSE_LANGUAGES[i]) == 0) {
                    noParse = TRUE;
                    break;
                }
            }
        }
        //TODO: end

        ures_close(ruleSets);
        ures_close(rbnfRules);
    }
    ures_close(nfrb);
}