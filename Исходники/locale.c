static void php_canonicalize_locale_id(char **target, int32_t *target_len, char *locale, UErrorCode *status)
{
	char *canonicalized = NULL;
	int32_t canonicalized_len = 128;

	while (1) {
		*status = U_ZERO_ERROR;
		canonicalized = erealloc(canonicalized, canonicalized_len + 1);
		canonicalized_len = uloc_canonicalize(locale, canonicalized, canonicalized_len, status);
		if (*status != U_BUFFER_OVERFLOW_ERROR) {
			break;
		}
	}

	canonicalized[canonicalized_len] = 0;
	*target = canonicalized;
	*target_len = canonicalized_len;
}