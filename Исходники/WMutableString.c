	self->capacity = newCapacity;
	stringSelf->text = newText;
	return 0;
}

inline static int __ensureCapacity(struct WMutableString *const self, UInteger minCapacity) {
	if ( minCapacity > self->capacity )
		return __grow(self, minCapacity);
	return 0;
}


inline static char *__wideToCharConverter(const wchar_t *restrict wideContent) {
	if ( wideContent == NULL ) return errno = EINVAL, (char *)NULL;
	
	size_t charContentSize = wcstombs(NULL, wideContent, 0);
	if ( charContentSize == (size_t)-1 ) return errno = 0, NULL;
	
	char *restrict charContent = calloc(charContentSize+1, sizeof(char));
	if ( charContent == NULL ) return errno = ENOMEM, (char *)NULL;
	
	charContentSize = wcstombs(charContent, wideContent, charContentSize);
	if ( charContentSize == (size_t)-1 ) return free(charContent), errno = 0, (char *)NULL;
	
	return charContent;
}

inline static wchar_t *__charToWideConverter(const char *restrict charContent) {
	if ( charContent == NULL ) return errno = EINVAL, (wchar_t *)NULL;
	
	size_t wideContentSize = mbstowcs(NULL, charContent, 0);