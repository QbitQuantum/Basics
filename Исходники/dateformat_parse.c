/* {{{
 * Internal function which calls the udat_parseCalendar
*/
static void internal_parse_to_localtime(IntlDateFormatter_object *dfo, char* text_to_parse, int32_t text_len, int32_t *parse_pos, zval *return_value)
{
	UCalendar      *parsed_calendar = NULL;
	UChar*  	text_utf16  = NULL;
	int32_t 	text_utf16_len = 0;
	zend_long 		isInDST = 0;

	/* Convert timezone to UTF-16. */
	intl_convert_utf8_to_utf16(&text_utf16, &text_utf16_len, text_to_parse, text_len, &INTL_DATA_ERROR_CODE(dfo));
	INTL_METHOD_CHECK_STATUS(dfo, "Error converting timezone to UTF-16" );

	parsed_calendar = (UCalendar *)udat_getCalendar(DATE_FORMAT_OBJECT(dfo));
	udat_parseCalendar( DATE_FORMAT_OBJECT(dfo), parsed_calendar, text_utf16, text_utf16_len, parse_pos, &INTL_DATA_ERROR_CODE(dfo));
	
	if (text_utf16) {
		efree(text_utf16);
	}

	INTL_METHOD_CHECK_STATUS( dfo, "Date parsing failed" );


	array_init( return_value );
	/* Add  entries from various fields of the obtained parsed_calendar */
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_SECOND, CALENDAR_SEC);
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_MINUTE, CALENDAR_MIN);
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_HOUR_OF_DAY, CALENDAR_HOUR);
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_YEAR, CALENDAR_YEAR); 
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_DAY_OF_MONTH, CALENDAR_MDAY);
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_DAY_OF_WEEK, CALENDAR_WDAY);
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_DAY_OF_YEAR, CALENDAR_YDAY);
	add_to_localtime_arr( dfo, return_value, parsed_calendar, UCAL_MONTH, CALENDAR_MON);

	/* Is in DST? */
	isInDST = ucal_inDaylightTime(parsed_calendar	, &INTL_DATA_ERROR_CODE(dfo));
	INTL_METHOD_CHECK_STATUS( dfo, "Date parsing - localtime failed : while checking if currently in DST." );
	add_assoc_long( return_value, CALENDAR_ISDST,(isInDST==1?1:0)); 
}