char* jm_create_URL_from_abs_path(jm_callbacks* cb, const char* path) {
	/* worst case: all symbols are 4-byte UTF-8 and need to be %-encoded */
#define MAX_URL_LENGTH  (FILENAME_MAX * 4 * 3 + 7)
	char buffer[MAX_URL_LENGTH];
	char* url;
	size_t urllen;
	if(!cb) {
		cb = jm_get_default_callbacks();
	}

#if defined(_WIN32) || defined(WIN32)
	{
		DWORD pathLen = MAX_URL_LENGTH;
		HRESULT code = UrlCreateFromPathA(
			path,
			buffer,
			&pathLen,
			0);
		if( (code != S_FALSE) && (code != S_OK)) {
			jm_log_fatal(cb, module,"Could not constuct file URL from path %s", path);
			return 0;
		}
		urllen = pathLen;
	}
#else
	{
		size_t i, len = strlen(path);
		char *curBuf = buffer + 7;
		unsigned char ch;
		strcpy(buffer, "file://");
		for( i = 0; i < len; i++) {
			ch = (unsigned char)path[i];
			if( (ch == '/') || ((ch >= 'A') && (ch <= 'Z')) 
				|| ((ch >= 'a') && (ch <= 'z'))
				|| (ch == '-') || (ch == '_') || (ch == '.') ||(ch == '~')) {
					*curBuf = ch;
					curBuf++;
					continue;
			}
			sprintf(curBuf, "%%%2X", (int)ch);/*safe*/
			curBuf+=3;
		}
		*curBuf = 0;
		urllen = curBuf - buffer;
	}
#endif
	url = (char*)cb->malloc(urllen+1);
	if(!url) {
		jm_log_fatal(cb, module,"Could not allocate memory");
		return 0;
	}
	strcpy(url, buffer);
	return url;
}