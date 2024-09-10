/// An enhanced version of wcstoull().
///
/// This is needed because BSD and GNU implementations differ in several ways that make it really
/// annoying to use them in a portable fashion.
///
/// The caller doesn't have to zero errno. Sets errno to -1 if the int ends with something other
/// than a digit. Leading minus is considered invalid. Leading whitespace is ignored (per the base
/// wcstoull implementation). Trailing whitespace is also ignored.
unsigned long long fish_wcstoull(const wchar_t *str, const wchar_t **endptr, int base) {
    while (iswspace(*str)) ++str;  // skip leading whitespace
    if (!*str ||      // this is because some implementations don't handle this sensibly
        *str == '-')  // disallow minus as the first character to avoid questionable wrap-around
    {
        errno = EINVAL;
        if (endptr) *endptr = str;
        return 0;
    }

    errno = 0;
    wchar_t *_endptr;
    unsigned long long result = wcstoull(str, &_endptr, base);
    while (iswspace(*_endptr)) ++_endptr;  // skip trailing whitespace
    if (!errno && *_endptr) {
        if (_endptr == str) {
            errno = EINVAL;
        } else {
            errno = -1;
        }
    }
    if (endptr) *endptr = _endptr;
    return result;
}