const char *intl_locale_get_default( void )
{
	if( INTL_G(default_locale) == NULL ) {
		return uloc_getDefault();
	}
	return INTL_G(default_locale);
}