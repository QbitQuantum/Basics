/* parse headers for Content-Length */
size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
	int r;
	long len = 0;

	/* _snscanf() is Win32 specific */
	r = _snscanf(ptr, size * nmemb, "Content-Length: %ld\n", &len);

	if (r) /* Microsoft: we don't read the specs */
		*((long *) stream) = len;

	return size * nmemb;
}