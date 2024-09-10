char* APP_API_STRUPR(char* s)
{
#ifndef __GNUC__
    return _strupr(s);
#else
    char* out = s;
    for(;*s;++s) *s = toupper(*s);
    return out;
#endif
}