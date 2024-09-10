static char *escapeParameter(CONST char *parameter)
{
    size_t i;
    size_t last = strlen(parameter);
    size_t n = 0;
    size_t encoded = 0;
    size_t escaped = 0;
    char *result;
    char *needs_encoded = "<>|";
    char *needs_escaped = "%";
    char *needs_escaped_NT = "%&^";

    for (i = 0; i < last; ++i) {
	if (StrChr(needs_encoded, parameter[i]) != NULL) {
	    ++encoded;
	}
	if (system_is_NT) {
	    if (StrChr(needs_escaped_NT, parameter[i]) != NULL) {
		++escaped;
	    }
	} else if (StrChr(needs_escaped, parameter[i]) != NULL) {
	    ++escaped;
	}
    }

    result = (char *) malloc(last + encoded * 2 + escaped + 1);
    if (result == NULL)
	outofmem(__FILE__, "escapeParameter");

    n = 0;
    for (i = 0; i < last; i++) {
	if (StrChr(needs_encoded, parameter[i]) != NULL) {
	    sprintf(result + n, "%%%02X", (unsigned char) parameter[i]);
	    n += 3;
	    continue;
	}
	if (system_is_NT) {
	    if (StrChr(needs_escaped_NT, parameter[i]) != NULL) {
		result[n++] = '^';
		result[n++] = parameter[i];
		continue;
	    }
	} else if (StrChr(needs_escaped, parameter[i]) != NULL) {
	    result[n++] = '%';	/* parameter[i] is '%' */
	    result[n++] = parameter[i];
	    continue;
	}
	result[n++] = parameter[i];
    }
    result[n] = '\0';

    return result;
}