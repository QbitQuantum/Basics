/* {{{ */
static void collator_ctor(INTERNAL_FUNCTION_PARAMETERS)
{
	char*            locale;
	int              locale_len = 0;
	zval*            object;
	Collator_object* co;

	intl_error_reset( NULL TSRMLS_CC );
	object = return_value;
	/* Parse parameters. */
	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s",
		&locale, &locale_len ) == FAILURE )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"collator_create: unable to parse input params", 0 TSRMLS_CC );
		zval_dtor(return_value);
		RETURN_NULL();
	}

	INTL_CHECK_LOCALE_LEN_OBJ(locale_len, return_value);
	co = (Collator_object *) zend_object_store_get_object( object TSRMLS_CC );

	intl_error_reset( COLLATOR_ERROR_P( co ) TSRMLS_CC );

	if(locale_len == 0) {
		locale = UG(default_locale);
	}

	/* Open ICU collator. */
	co->ucoll = ucol_open( locale, COLLATOR_ERROR_CODE_P( co ) );
	INTL_CTOR_CHECK_STATUS(co, "collator_create: unable to open ICU collator");
}