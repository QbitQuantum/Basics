int
__cdecl
vfwprintf_s(FILE* file, const wchar_t *format, va_list argptr)
{
    int ret;

    if(!MSVCRT_CHECK_PMT( file != NULL)) {
        _set_errno(EINVAL);
        return -1;
    }

    _lock_file(file);
    ret = wstreamout(file, format, argptr);
    _unlock_file(file);

    return ret;
}