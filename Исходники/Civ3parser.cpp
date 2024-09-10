char* to_c(char *token, char *c_token, int toupper)
{
	char *c_t = c_token;
	char *t = token;
	if (isdigit(*t)) {
		*c_t++ = '_';
	}
	for (; *t; ++t, ++c_t) {
		if (!isalnum(*t)) {
			*c_t = '_';
		} else {
			*c_t = toupper ? _toupper(*t) : *t;
		}
	}
	*c_t = 0;

	return c_token;
}