/* {{{ */
static void datefmt_ctor(INTERNAL_FUNCTION_PARAMETERS)
{
    char*       locale;
	int         locale_len = 0;
	zval*       object;
    long        date_type = 0;
    long        time_type = 0;
    long        calendar = UCAL_GREGORIAN;
    char*       timezone_str = NULL;
    int         timezone_str_len = 0;
    char*       pattern_str = NULL;
    int         pattern_str_len = 0;
    UChar*      svalue = NULL;		/* UTF-16 pattern_str */
    int         slength = 0;
    UChar*      timezone_utf16 = NULL;		/* UTF-16 timezone_str */
    int         timezone_utf16_len = 0;
	UCalendar   ucal_obj = NULL;
	IntlDateFormatter_object* dfo;
	
	intl_error_reset( NULL TSRMLS_CC );
	object = return_value;
	/* Parse parameters. */
    if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "sll|sls",
		&locale, &locale_len, &date_type, &time_type, &timezone_str, &timezone_str_len, &calendar,&pattern_str, &pattern_str_len ) == FAILURE )
    {
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,	"datefmt_create: unable to parse input parameters", 0 TSRMLS_CC );
		zval_dtor(return_value);
		RETURN_NULL();
    }

	INTL_CHECK_LOCALE_LEN_OBJ(locale_len, return_value);
	
	if (calendar != UCAL_TRADITIONAL && calendar != UCAL_GREGORIAN) {
		intl_error_set(NULL, U_ILLEGAL_ARGUMENT_ERROR, "datefmt_create: "
				"invalid value for calendar type; it must be one of "
				"IntlDateFormatter::TRADITIONAL (locale's default calendar) "
				"or IntlDateFormatter::GREGORIAN", 0 TSRMLS_CC);
		goto error;
	}
	
	DATE_FORMAT_METHOD_FETCH_OBJECT_NO_CHECK;
	
	if (DATE_FORMAT_OBJECT(dfo) != NULL) {
		intl_errors_set(INTL_DATA_ERROR_P(dfo), U_ILLEGAL_ARGUMENT_ERROR,
				"datefmt_create: cannot call constructor twice", 0 TSRMLS_CC);
		return;
	}
	
	/* Convert pattern (if specified) to UTF-16. */
	if( pattern_str && pattern_str_len>0 ){
		intl_convert_utf8_to_utf16(&svalue, &slength,
				pattern_str, pattern_str_len, &INTL_DATA_ERROR_CODE(dfo));
		if (U_FAILURE(INTL_DATA_ERROR_CODE(dfo))) {
			/* object construction -> only set global error */
			intl_error_set(NULL, INTL_DATA_ERROR_CODE(dfo), "datefmt_create: "
					"error converting pattern to UTF-16", 0 TSRMLS_CC);
			goto error;
		}
	}
	
	/* resources allocated from now on */

	/* Convert pattern (if specified) to UTF-16. */
	if( timezone_str && timezone_str_len >0 ){
		intl_convert_utf8_to_utf16(&timezone_utf16, &timezone_utf16_len,
				timezone_str, timezone_str_len, &INTL_DATA_ERROR_CODE(dfo));
		if (U_FAILURE(INTL_DATA_ERROR_CODE(dfo))) {
			intl_error_set(NULL, INTL_DATA_ERROR_CODE(dfo), "datefmt_create: "
					"error converting timezone_str to UTF-16", 0 TSRMLS_CC);
			goto error;
		}
	}

	if(locale_len == 0) {
		locale = INTL_G(default_locale);
	}

	if( pattern_str && pattern_str_len>0 ){
		DATE_FORMAT_OBJECT(dfo) = udat_open(UDAT_IGNORE, UDAT_IGNORE, locale, timezone_utf16, timezone_utf16_len, svalue, slength, &INTL_DATA_ERROR_CODE(dfo));
	} else {
		DATE_FORMAT_OBJECT(dfo) = udat_open(time_type, date_type, locale, timezone_utf16, timezone_utf16_len, svalue, slength, &INTL_DATA_ERROR_CODE(dfo));
	}

    if (!U_FAILURE(INTL_DATA_ERROR_CODE(dfo))) {
		if (calendar != UCAL_TRADITIONAL) {
			ucal_obj = ucal_open(timezone_utf16, timezone_utf16_len, locale,
					calendar, &INTL_DATA_ERROR_CODE(dfo));
			if (!U_FAILURE(INTL_DATA_ERROR_CODE(dfo))) {
				udat_setCalendar(DATE_FORMAT_OBJECT(dfo), ucal_obj);
				ucal_close(ucal_obj);
			} else {
				intl_error_set(NULL, INTL_DATA_ERROR_CODE(dfo), "datefmt_create"
						": error opening calendar", 0 TSRMLS_CC);
				goto error;
			}
		}
    } else {
		intl_error_set(NULL, INTL_DATA_ERROR_CODE(dfo),	"datefmt_create: date "
				"formatter creation failed", 0 TSRMLS_CC);
		goto error;
	}

	/* Set the class variables */
	dfo->date_type = date_type;
	dfo->time_type = time_type;
	dfo->calendar  = calendar;
	if( timezone_str && timezone_str_len > 0){
		dfo->timezone_id = estrndup( timezone_str, timezone_str_len);
	}
	
error:
	if (svalue) {
		efree(svalue);
	}
	if (timezone_utf16) {
		efree(timezone_utf16);
	}
	if (U_FAILURE(intl_error_get_code(NULL TSRMLS_CC))) {
		/* free_object handles partially constructed instances fine */
		zval_dtor(return_value);
		RETVAL_NULL();
	}
}