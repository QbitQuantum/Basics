void U_CALLCONV DayPeriodRules::load(UErrorCode &errorCode) {
    if (U_FAILURE(errorCode)) {
        return;
    }

    data = new DayPeriodRulesData();
    data->localeToRuleSetNumMap = uhash_open(uhash_hashChars, uhash_compareChars, NULL, &errorCode);
    LocalUResourceBundlePointer rb_dayPeriods(ures_openDirect(NULL, "dayPeriods", &errorCode));

    // Get the largest rule set number (so we allocate enough objects).
    DayPeriodRulesCountSink countSink;
    ures_getAllItemsWithFallback(rb_dayPeriods.getAlias(), "rules", countSink, errorCode);

    // Populate rules.
    DayPeriodRulesDataSink sink;
    ures_getAllItemsWithFallback(rb_dayPeriods.getAlias(), "", sink, errorCode);

    ucln_i18n_registerCleanup(UCLN_I18N_DAYPERIODRULES, dayPeriodRulesCleanup);
}