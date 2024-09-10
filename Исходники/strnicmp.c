extern "C" int __cdecl _strnicmp(
    const char* dst,
    const char* src,
    size_t count
) {
    if (__locale_changed == 0) {
        /* validation section */
        _VALIDATE_RETURN(dst != NULL, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(src != NULL, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(count <= INT_MAX, EINVAL, _NLSCMPERROR);
        return __ascii_strnicmp(dst, src, count);
    } else {
        return _strnicmp_l(dst, src, count, NULL);
    }
}