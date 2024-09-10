size_t _RTL_FUNC mbstowcs(wchar_t *pwcs,const char *mbs, size_t n)
{
    size_t rv ;
    rv = mbsrtowcs(pwcs,&mbs,n,&__getRtlData()->mbstowcs_st);
    if (rv == (size_t)-2)
        rv = (size_t)-1;
    if ((int)rv >=0 && rv != n)
        pwcs[rv] = 0 ;
    return rv ;
}