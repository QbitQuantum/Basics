static void
xsltEnumSupportedLocales(void) {
    xmlRMutexLock(xsltLocaleMutex);
    if (xsltLocaleListSize <= 0) {
	size_t len;

	EnumSystemLocalesA(xsltCountSupportedLocales, LCID_SUPPORTED);

	len = xsltLocaleListSize * sizeof(xsltRFC1766Info);
	xsltLocaleList = xmlMalloc(len);
	memset(xsltLocaleList, 0, len);
	EnumSystemLocalesA(xsltIterateSupportedLocales, LCID_SUPPORTED);
    }
    xmlRMutexUnlock(xsltLocaleMutex);
}