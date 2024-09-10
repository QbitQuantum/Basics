/** call-seq:
 *     calendar.format(pattern = nil , locale = nil)
 *
 * Formats this calendar time using given pattern and locale. Returns UString or nil on failure.
 * Valid value types for pattern are:
 *      nil        - long format for date and time
 *      UString    - specification of format, as defined in docs/FORMATTING
 *      Symbol     - one of :short, :medium, :long, :full, :none , sets format for both date and time
 *      Hash       - {:time => aSymbol, :date => aSymbol} - sets separate formats for date and time, valid symbols see above
 */
VALUE icu4r_cal_format(int argc, VALUE * argv, VALUE obj) 
{
	UErrorCode status = U_ZERO_ERROR;
	UDateFormat * format;
	UDate   time_to_format;
	UChar * buf = NULL, * pattern = NULL;
	long capa = 0, pattern_len = 0;
	char *locale = NULL;
	VALUE loc, pat, ret = Qnil;
	int n , def_d_format = UDAT_FULL, def_t_format = UDAT_FULL;
	
	n = rb_scan_args(argc, argv, "02", &pat, &loc);
	if( n == 2) {
		Check_Type(loc, T_STRING);
		locale = RSTRING_PTR(loc);
	}
	if (n >= 1 && pat != Qnil) {
		switch(TYPE(pat)) {
			case T_SYMBOL:
			 	def_d_format = def_t_format = icu4r_get_cal_format_int(pat);
				break;
			case T_HASH:
			 	def_d_format = icu4r_get_cal_format_int(rb_hash_aref(pat, ID2SYM(rb_intern("date"))));
				def_t_format = icu4r_get_cal_format_int(rb_hash_aref(pat, ID2SYM(rb_intern("time"))));
				break;
			default:
				Check_Class(pat, rb_cUString);
				pattern = ICU_PTR(pat);
				pattern_len = ICU_LEN(pat);
				break;
		}
	}
	
	format = udat_open(def_t_format, def_d_format, locale, NULL, 0,  NULL, 0, &status);
	if( pattern ) {
	   udat_applyPattern(format, 0, pattern, pattern_len);
	}
	ICU_RAISE(status);
	udat_setCalendar(format, UCALENDAR(obj));
	time_to_format = ucal_getMillis(UCALENDAR(obj), &status); 

	capa = udat_format(format, time_to_format, buf, capa, NULL, &status);
	if( U_BUFFER_OVERFLOW_ERROR == status) {
		buf = ALLOC_N(UChar, capa+1);
		status = U_ZERO_ERROR;
		capa = udat_format(format, time_to_format, buf, capa, NULL, &status);
		ret = icu_ustr_new_set(buf, capa, capa+1);
	}
	udat_close(format);
	ICU_RAISE(status);
	return ret;
}