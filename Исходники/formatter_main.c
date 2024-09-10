/* {{{ */
static void numfmt_ctor(INTERNAL_FUNCTION_PARAMETERS)
{
	char*       locale;
	char*       pattern = NULL;
	int         locale_len = 0, pattern_len = 0;
	long        style;
	UChar*      spattern     = NULL;
	int         spattern_len = 0;
	FORMATTER_METHOD_INIT_VARS;

	/* Parse parameters. */
	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "sl|s",
		&locale, &locale_len, &style, &pattern, &pattern_len ) == FAILURE )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"numfmt_create: unable to parse input parameters", 0 TSRMLS_CC );
		zval_dtor(return_value);
		RETURN_NULL();
	}

	INTL_CHECK_LOCALE_LEN_OBJ(locale_len, return_value);
	object = return_value;
	FORMATTER_METHOD_FETCH_OBJECT;

	/* Convert pattern (if specified) to UTF-16. */
	if(pattern && pattern_len) {
		intl_convert_utf8_to_utf16(&spattern, &spattern_len, pattern, pattern_len, &INTL_DATA_ERROR_CODE(nfo));
		INTL_CTOR_CHECK_STATUS(nfo, "numfmt_create: error converting pattern to UTF-16");
	}

	if(locale_len == 0) {
		locale = INTL_G(default_locale);
	}

	/* Create an ICU number formatter. */
	FORMATTER_OBJECT(nfo) = unum_open(style, spattern, spattern_len, locale, NULL, &INTL_DATA_ERROR_CODE(nfo));

	if(spattern) {
		efree(spattern);
	}

	INTL_CTOR_CHECK_STATUS(nfo, "numfmt_create: number formatter creation failed");
}