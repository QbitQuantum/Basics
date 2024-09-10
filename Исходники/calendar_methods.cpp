U_CFUNC PHP_FUNCTION(intlcal_get_keyword_values_for_locale)
{
	UErrorCode	status = U_ZERO_ERROR;
	char		*key,
				*locale;
	int			key_len,
				locale_len;
	zend_bool	commonly_used;
	intl_error_reset(NULL TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssb",
			&key, &key_len, &locale, &locale_len, &commonly_used) == FAILURE) {
		intl_error_set(NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"intlcal_get_keyword_values_for_locale: bad arguments", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	//does not work; see ICU bug 9194
#if 0
	StringEnumeration *se = Calendar::getKeywordValuesForLocale(key,
		Locale::createFromName(locale), (UBool)commonly_used,
		status);
	if (se == NULL) {
		intl_error_set(NULL, status, "intlcal_get_keyword_values_for_locale: "
			"error calling underlying method", 0 TSRMLS_CC);
		RETURN_FALSE;
	}
#else
    UEnumeration *uenum = ucal_getKeywordValuesForLocale(
		key, locale, !!commonly_used, &status);
    if (U_FAILURE(status)) {
        uenum_close(uenum);
		intl_error_set(NULL, status, "intlcal_get_keyword_values_for_locale: "
			"error calling underlying method", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    StringEnumeration *se = new BugStringCharEnumeration(uenum);
#endif

	IntlIterator_from_StringEnumeration(se, return_value TSRMLS_CC);
}