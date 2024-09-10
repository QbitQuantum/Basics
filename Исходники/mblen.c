int _RTL_FUNC mblen(const char *s, size_t n)
{
    size_t rv ;
    if (!s || !*s)
        return 0 ;
    if (n ==0)
        return -1 ;
    rv = mbrlen(s,n,&__getRtlData()->mblen_st);
    if (rv == (size_t)-2)
        rv = (size_t)-1;
    return (int)rv;
}