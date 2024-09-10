void
_Py_bytes_swapcase(char *result, char *s, Py_ssize_t len)
{
	Py_ssize_t i;

        /*
	newobj = PyString_FromStringAndSize(NULL, len);
	if (newobj == NULL)
		return NULL;
	s_new = PyString_AsString(newobj);
        */
	for (i = 0; i < len; i++) {
		int c = Py_CHARMASK(*s++);
		if (ISLOWER(c)) {
			*result = TOUPPER(c);
		}
		else if (ISUPPER(c)) {
			*result = TOLOWER(c);
		}
		else
			*result = c;
		result++;
	}
}