bool AssertFailed(const char *file, int line, const char *s, ...)
{
    char str[4000];

    va_list args;
    va_start(args, s);
    vsprintf_s(str, LENGTH(str), s, args);
    va_end(args);

    return Warning("Assert failed at %s (%i)\n%s", file, line, str);
}