size_t __cdecl _mbsnlen(
        const unsigned char *s,
        size_t maxsize
        )
{
    return _mbsnlen_l(s,maxsize, nullptr);
}