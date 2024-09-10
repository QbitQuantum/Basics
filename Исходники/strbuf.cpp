//The functions snprintf() and vsnprintf() do not write more than size 
//bytes (including the terminating null byte ('\0')).
void StrBuf::nstrcat(UINT size, CHAR const* format, ...)
{
    va_list args;
    va_start(args, format);
    va_list org_args;
    va_copy(org_args, args);
    UINT l = VSNPRINTF(NULL, 0, format, args);
    if (l > size) { l = size; }
    strcat(l, format, org_args);
    va_end(args);
    va_end(org_args);
}