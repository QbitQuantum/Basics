int c99_vsnprintf_retro__(char *outBuf, size_t size, const char *format, va_list ap)
{
   int count = -1;

   if (size != 0)
#if (_MSC_VER <= 1310)
       count = _vsnprintf(outBuf, size, format, ap);
#else
       count = _vsnprintf_s(outBuf, size, _TRUNCATE, format, ap);
#endif
   if (count == -1)
       count = _vscprintf(format, ap);

   return count;
}