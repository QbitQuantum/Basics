/**
 * @short Transforms a time_t to a ISO date string
 * 
 * The dest pointer must be at least 21 bytes long as thats the maximum size of the date.
 */
void onion_shortcut_date_string_iso(time_t t, char *dest){
	struct tm ts;
	gmtime_r(&t, &ts);
	strftime(dest, t, "%FT%TZ", &ts);
}