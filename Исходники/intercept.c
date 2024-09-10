wchar_t *wcpcpy(wchar_t *dest, const wchar_t *src)
{
    static wcpcpy_t real_wcpcpy = NULL;
    size_t max_bytes, max_wchars, len;

    if (!real_wcpcpy)
	real_wcpcpy = (wcpcpy_t) getLibraryFunction("wcpcpy");

    if (_libsafe_exclude)
	return real_wcpcpy(dest, src);

    if ((max_bytes = _libsafe_stackVariableP(dest)) == 0) {
	LOG(5, "strcpy(<heap var> , <src>)\n");
	return real_wcpcpy(dest, src);
    }

    LOG(4, "wcpcpy(<stack var> , <src>) stack limit=%d)\n", max_bytes);
    /*
     * Note: we can't use the standard wcsncpy()!  From the wcsncpy(3) manual
     * pages: "If the length wcslen(src) is smaller than n, the remaining wide
     * characters in the array pointed to by dest are filled with  L'\0'
     * characters."  We do not want null written all over the 'dest', hence,
     * our own implementation.
     */
    max_wchars = max_bytes / sizeof(wchar_t);
    if ((len = wcsnlen(src, max_wchars)) == max_wchars) {
	/*
	 * If wcsnlen() returns max_wchars, it means that no L'\0' character was
	 * found in the first max_wchars wide characters.  So, this
	 * wide-character string won't fit in the stack frame.
	 */
	_libsafe_die("Overflow caused by wcpcpy()");
    }

    /*
     * Note that we can use wcpcpy() directly since there is no memcpy()
     * optimization as in the case of strcpy().
     */
    return real_wcpcpy(dest, src);
}