/* return next token in configuration line */
wchar_t *
strdelim(wchar_t **s)
{
	wchar_t *old;
	int wspace = 0;

	if (*s == NULL)
		return (NULL);

	old = *s;

	*s = wcspbrk(*s, WHITESPACE QUOTE "=");
	if (*s == NULL)
		return (old);

	if (*s[0] == L'\"') {
		wmemmove(*s, *s + 1, wcslen(*s)); /* move nul too */
		/* Find matching quote */
		if ((*s = wcspbrk(*s, QUOTE)) == NULL) {
			return (NULL);		/* no matching quote */
		} else {
			*s[0] = L'\0';
			return (old);
		}
	}

	/* Allow only one '=' to be skipped */
	if (*s[0] == L'=')
		wspace = 1;
	*s[0] = L'\0';

	/* Skip any extra whitespace after first token */
	*s += wcsspn(*s + 1, WHITESPACE) + 1;
	if (*s[0] == L'=' && !wspace)
		*s += wcsspn(*s + 1, WHITESPACE) + 1;

	return (old);
}