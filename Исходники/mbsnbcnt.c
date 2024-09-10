size_t _RTLENTRY _EXPFUNC _mbsnbcnt(const unsigned char *s, size_t n)
{
    const unsigned char *p;

    for (p = s; n > 0 && *p; n--, p++)
    {
        if (_ismbblead(*p))
        {
            if (p[1] == '\0')
                break;
            p++;
        }
    }
    return (size_t)(p - s);
}