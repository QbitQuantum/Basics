/**
 * Compose a string with a format string in the buffer pointed to by buf.
 *
 * It is up to the caller to ensure that the allocated buffer is large enough
 * to hold the formatted result.
 *
 * Internally, the function retrieves arguments from the list identified by
 * args as if va_arg was used on it, and thus the state of args is likely to
 * be altered by the call.
 *
 * In any case, args should have been initialized by va_start at some point
 * before the call, and it is expected to be released by va_end at some point
 * after the call.
 *
 * This version ignores the current locale and uses the locale "C" for Linux,
 * FreeBSD, OSX and Android.
 *
 * @param buf Pointer to a buffer where the resulting C string is stored.
 * @param format C string that contains a format string (see printf).
 * @param args A value identifying a variable arguments list initialized with
 *        va_start.
 *
 * @return On success, the number of characters that would have been written,
 *         not counting the terminating NUL character.
 *
 * @since 0.6.0
 */
SR_API int sr_vsprintf_ascii(char *buf, const char *format, va_list args)
{
#if defined(_WIN32)
	int ret;

#if 0
	/*
	 * TODO: This part compiles with mingw-w64 but doesn't run with Win7.
	 *       Doesn't start because of "Procedure entry point _create_locale
	 *       not found in msvcrt.dll".
	 *       mingw-w64 should link to msvcr100.dll not msvcrt.dll!
	 * See: https://msdn.microsoft.com/en-us/en-en/library/1kt27hek.aspx
	 */
	_locale_t locale;

	locale = _create_locale(LC_NUMERIC, "C");
	ret = _vsprintf_l(buf, format, locale, args);
	_free_locale(locale);
#endif

	/* vsprintf() uses the current locale, may not work correctly for floats. */
	ret = vsprintf(buf, format, args);

	return ret;
#elif defined(__APPLE__)
	/*
	 * See:
	 * https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/printf_l.3.html
	 * https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/xlocale.3.html
	 */
	int ret;
	locale_t locale;

	locale = newlocale(LC_NUMERIC_MASK, "C", NULL);
	ret = vsprintf_l(buf, locale, format, args);
	freelocale(locale);

	return ret;
#elif defined(__FreeBSD__) && __FreeBSD_version >= 901000
	/*
	 * See:
	 * https://www.freebsd.org/cgi/man.cgi?query=printf_l&apropos=0&sektion=3&manpath=FreeBSD+9.1-RELEASE
	 * https://www.freebsd.org/cgi/man.cgi?query=xlocale&apropos=0&sektion=3&manpath=FreeBSD+9.1-RELEASE
	 */
	int ret;
	locale_t locale;

	locale = newlocale(LC_NUMERIC_MASK, "C", NULL);
	ret = vsprintf_l(buf, locale, format, args);
	freelocale(locale);

	return ret;
#elif defined(__ANDROID__)
	/*
	 * The Bionic libc only has two locales ("C" aka "POSIX" and "C.UTF-8"
	 * aka "en_US.UTF-8"). The decimal point is hard coded as "."
	 * See: https://android.googlesource.com/platform/bionic/+/master/libc/bionic/locale.cpp
	 */
	int ret;

	ret = vsprintf(buf, format, args);

	return ret;
#elif defined(__linux__)
	int ret;
	locale_t old_locale, temp_locale;

	/* Switch to C locale for proper float/double conversion. */
	temp_locale = newlocale(LC_NUMERIC, "C", NULL);
	old_locale = uselocale(temp_locale);

	ret = vsprintf(buf, format, args);

	/* Switch back to original locale. */
	uselocale(old_locale);
	freelocale(temp_locale);

	return ret;
#elif defined(__unix__) || defined(__unix)
	/*
	 * This is a fallback for all other BSDs, *nix and FreeBSD <= 9.0, by
	 * using the current locale for snprintf(). This may not work correctly
	 * for floats!
	 */
	int ret;

	ret = vsprintf(buf, format, args);

	return ret;
#else
	/* No implementation for unknown systems! */
	return -1;
#endif
}