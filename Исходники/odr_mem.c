Odr_int odr_strtol(const char *nptr, char **endptr, int base)
{
#if NMEM_64
#if WIN32
    return _strtoui64(nptr, endptr, base);
#else
    return strtoll(nptr, endptr, base);
#endif

#else
    return strtol(nptr, endptr, base);
#endif
}