extern "C" size_t __cdecl _mbstrnlen(
    char const* const string,
    size_t      const max_size
    )
{
    return _mbstrnlen_l(string, max_size, nullptr);
}