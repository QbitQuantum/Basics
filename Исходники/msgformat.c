/* {{{ */
static void msgfmt_ctor(INTERNAL_FUNCTION_PARAMETERS) 
{
	char*       locale;
	char*       pattern;
	int         locale_len = 0, pattern_len = 0;
	UChar*      spattern     = NULL;
	int         spattern_len = 0;
	zval*       object;
	MessageFormatter_object* mfo;
	intl_error_reset( NULL TSRMLS_CC );

	object = return_value;
	/* Parse parameters. */
	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "ss",
		&locale, &locale_len, &pattern, &pattern_len ) == FAILURE )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"msgfmt_create: unable to parse input parameters", 0 TSRMLS_CC );
		zval_dtor(return_value);
		RETURN_NULL();
	}

	INTL_CHECK_LOCALE_LEN_OBJ(locale_len, return_value);
	MSG_FORMAT_METHOD_FETCH_OBJECT;

	/* Convert pattern (if specified) to UTF-16. */
	if(pattern && pattern_len) {
		intl_convert_utf8_to_utf16(&spattern, &spattern_len, pattern, pattern_len, &INTL_DATA_ERROR_CODE(mfo));
		INTL_CTOR_CHECK_STATUS(mfo, "msgfmt_create: error converting pattern to UTF-16");
	} else {
		spattern_len = 0;
		spattern = NULL;
	}

	if(locale_len == 0) {
		locale = INTL_G(default_locale);
	}

#ifdef MSG_FORMAT_QUOTE_APOS
	if(msgformat_fix_quotes(&spattern, &spattern_len, &INTL_DATA_ERROR_CODE(mfo)) != SUCCESS) {
		INTL_CTOR_CHECK_STATUS(mfo, "msgfmt_create: error converting pattern to quote-friendly format");
	}
#endif

	if ((mfo)->mf_data.orig_format) {
		msgformat_data_free(&mfo->mf_data TSRMLS_CC);
	}

	(mfo)->mf_data.orig_format = estrndup(pattern, pattern_len);
	(mfo)->mf_data.orig_format_len = pattern_len;
	
	/* Create an ICU message formatter. */
	MSG_FORMAT_OBJECT(mfo) = umsg_open(spattern, spattern_len, locale, NULL, &INTL_DATA_ERROR_CODE(mfo));

	if(spattern) {
		efree(spattern);
	}

	INTL_CTOR_CHECK_STATUS(mfo, "msgfmt_create: message formatter creation failed");
}