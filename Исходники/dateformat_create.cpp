/* {{{ */
static void datefmt_ctor(INTERNAL_FUNCTION_PARAMETERS)
{
	zval		*object;

	const char	*locale_str;
	size_t		locale_len		= 0;
	Locale		locale;
    zend_long	date_type		= 0;
    zend_long	time_type		= 0;
	zval		*calendar_zv	= NULL;
	Calendar	*calendar		= NULL;
	zend_long	calendar_type;
	bool		calendar_owned;
	zval		*timezone_zv	= NULL;
	TimeZone	*timezone		= NULL;
	bool		explicit_tz;
    char*       pattern_str		= NULL;
    size_t      pattern_str_len	= 0;
    UChar*      svalue			= NULL;		/* UTF-16 pattern_str */
    int32_t     slength			= 0;
	IntlDateFormatter_object* dfo;

	intl_error_reset(NULL);
	object = return_value;
	/* Parse parameters. */
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sll|zzs",
			&locale_str, &locale_len, &date_type, &time_type, &timezone_zv,
			&calendar_zv, &pattern_str, &pattern_str_len) == FAILURE) {
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,	"datefmt_create: "
				"unable to parse input parameters", 0);
		Z_OBJ_P(return_value) = NULL;
		return;
    }

	INTL_CHECK_LOCALE_LEN_OBJ(locale_len, return_value);
	if (locale_len == 0) {
		locale_str = intl_locale_get_default();
	}
	locale = Locale::createFromName(locale_str);

	DATE_FORMAT_METHOD_FETCH_OBJECT_NO_CHECK;

	if (DATE_FORMAT_OBJECT(dfo) != NULL) {
		intl_errors_set(INTL_DATA_ERROR_P(dfo), U_ILLEGAL_ARGUMENT_ERROR,
				"datefmt_create: cannot call constructor twice", 0);
		return;
	}

	/* process calendar */
	if (datefmt_process_calendar_arg(calendar_zv, locale, "datefmt_create",
			INTL_DATA_ERROR_P(dfo), calendar, calendar_type,
			calendar_owned)
			== FAILURE) {
		goto error;
	}

	/* process timezone */
	explicit_tz = timezone_zv != NULL && Z_TYPE_P(timezone_zv) != IS_NULL;

	if (explicit_tz || calendar_owned ) {
		//we have an explicit time zone or a non-object calendar
		timezone = timezone_process_timezone_argument(timezone_zv,
				INTL_DATA_ERROR_P(dfo), "datefmt_create");
		if (timezone == NULL) {
			goto error;
		}
	}

	/* Convert pattern (if specified) to UTF-16. */
	if (pattern_str && pattern_str_len > 0) {
		intl_convert_utf8_to_utf16(&svalue, &slength,
				pattern_str, pattern_str_len, &INTL_DATA_ERROR_CODE(dfo));
		if (U_FAILURE(INTL_DATA_ERROR_CODE(dfo))) {
			/* object construction -> only set global error */
			intl_error_set(NULL, INTL_DATA_ERROR_CODE(dfo), "datefmt_create: "
					"error converting pattern to UTF-16", 0);
			goto error;
		}
	}

	if (pattern_str && pattern_str_len > 0) {
		DATE_FORMAT_OBJECT(dfo) = udat_open(UDAT_IGNORE, UDAT_IGNORE,
				locale_str, NULL, 0, svalue, slength,
				&INTL_DATA_ERROR_CODE(dfo));
	} else {
		DATE_FORMAT_OBJECT(dfo) = udat_open((UDateFormatStyle)time_type,
				(UDateFormatStyle)date_type, locale_str, NULL, 0, svalue,
				slength, &INTL_DATA_ERROR_CODE(dfo));
	}

    if (!U_FAILURE(INTL_DATA_ERROR_CODE(dfo))) {
		DateFormat *df = (DateFormat*)DATE_FORMAT_OBJECT(dfo);
		if (calendar_owned) {
			df->adoptCalendar(calendar);
			calendar_owned = false;
		} else {
			df->setCalendar(*calendar);
		}

		if (timezone != NULL) {
			df->adoptTimeZone(timezone);
		}
    } else {
		intl_error_set(NULL, INTL_DATA_ERROR_CODE(dfo),	"datefmt_create: date "
				"formatter creation failed", 0);
		goto error;
	}

	/* Set the class variables */
	dfo->date_type			= date_type;
	dfo->time_type			= time_type;
	dfo->calendar			= calendar_type;
	dfo->requested_locale	= estrdup(locale_str);

error:
	if (svalue) {
		efree(svalue);
	}
	if (timezone != NULL && DATE_FORMAT_OBJECT(dfo) == NULL) {
		delete timezone;
	}
	if (calendar != NULL && calendar_owned) {
		delete calendar;
	}
	if (U_FAILURE(intl_error_get_code(NULL))) {
		/* free_object handles partially constructed instances fine */
		Z_OBJ_P(return_value) = NULL;
	}
}