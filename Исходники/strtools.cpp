size_t mymbslen(const char *s, size_t max_len) {
#if !defined(WIN32) && !defined(WIN64)
	size_t result, pos = 0, len = 0;
	mbstate_t mbstate;

	memset(&mbstate, '\0', sizeof(mbstate));

	while (pos < max_len) {
		result = mbrlen(s + pos, max_len - pos, &mbstate);
		if (result < (size_t)0) {
			return -1;
		}
		if (result == 0) {	 /* L'\0' encountered */
				return len;
		}
		pos += result;
		len++;
	}

	return len;
#else
	size_t len;

	if (max_len == 0) {
		return 0;
	}

	len = MultiByteToWideChar(CP_UTF8, 0, s, SIZE_T_TO_MAX_INT(max_len), NULL, 0);

	return len == 0 ? -1 : len;
#endif
}