/* {{{
 * Internal function which sets UCalendar  from the passed array and retrieves timestamp
*/
static UDate internal_get_timestamp(IntlDateFormatter_object *dfo,
		HashTable *hash_arr)
{
	int32_t		year,
				month,
				hour,
				minute,
				second,
				mday;
	UCalendar	*pcal;
	UDate		result;
	intl_error	*err = &dfo->datef_data.error;

#define INTL_GET_ELEM(elem) \
	internal_get_arr_ele(dfo, hash_arr, (elem), err)

	/* Fetch  values from the incoming array */
	year	= INTL_GET_ELEM(CALENDAR_YEAR) + 1900; /* tm_year is years since 1900 */
	/* Month in ICU and PHP starts from January =0 */
	month	= INTL_GET_ELEM(CALENDAR_MON);
	hour	= INTL_GET_ELEM(CALENDAR_HOUR);
	minute	= INTL_GET_ELEM(CALENDAR_MIN);
	second	= INTL_GET_ELEM(CALENDAR_SEC);
	/* For the ucal_setDateTime() function, this is the 'date'  value */
	mday	= INTL_GET_ELEM(CALENDAR_MDAY);

#undef INTL_GET_ELEM

	pcal = ucal_clone(udat_getCalendar(DATE_FORMAT_OBJECT(dfo)),
			&INTL_DATA_ERROR_CODE(dfo));

	if (INTL_DATA_ERROR_CODE(dfo) != U_ZERO_ERROR) {
		intl_errors_set(err, INTL_DATA_ERROR_CODE(dfo), "datefmt_format: "
				"error cloning calendar", 0);
		return 0;
	}

	/* set the incoming values for the calendar */
	ucal_setDateTime(pcal, year, month, mday, hour, minute, second, &INTL_DATA_ERROR_CODE(dfo));
	/* actually, ucal_setDateTime cannot fail */

	/* Fetch the timestamp from the UCalendar */
	result = ucal_getMillis(pcal, &INTL_DATA_ERROR_CODE(dfo));
	ucal_close(pcal);
	return result;
}