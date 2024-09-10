/**
 * Generic function to retrieve the locale.  I'm simplifying this to
 * ignore the "modifier" and return "language_territory.codeset"
 */
int get_locale(I18N_STRING locale)
{
	int  error = I18N_SUCCESS;
	WCHAR localeBuffer[I18N_STRING_LEN];

	if (GetUserDefaultLocaleName(localeBuffer, I18N_STRING_LEN)  == 0)
	{
		locale[0] = '\0';
		error = I18N_FAIL;
	}
	else if (wcstombs(locale, localeBuffer, I18N_STRING_LEN) == (size_t)-1)
	{
		locale[0] = '\0';
		error = I18N_FAIL;
	}
	return error;
}