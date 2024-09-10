uintmax_t raw_string_to_scalar_type(const wchar_t *s, wchar_t ** end)
{
    return wcstoull(s, end, 0);
}