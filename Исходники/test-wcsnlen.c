static void
test_wcsnlen(const wchar_t *s)
{
	wchar_t *s1;
	size_t size, len, bufsize;
	int i;

	size = wcslen(s) + 1;
	for (i = 0; i <= 1; i++) {
	    for (bufsize = 0; bufsize <= size + 10; bufsize++) {
		s1 = makebuf(bufsize * sizeof(wchar_t), i);
		wmemcpy(s1, s, bufsize);
		len = (size > bufsize) ? bufsize : size - 1;
		assert(wcsnlen(s1, bufsize) == len);
	    }
	}
}