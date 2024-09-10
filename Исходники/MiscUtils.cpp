int sprintf_s(char *buffer, const char *str, va_list args)
{
    return vsprintf(buffer, str, args);
}