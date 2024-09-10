int dSscanf(const char *buffer, const char *format, ...)
{
   va_list args;
   va_start(args, format);
   return vsscanf(buffer, format, args);   
}   