size_t ossSnprintf(char* pBuffer, size_t iLength, const char* pFormat, ...)
{
   va_list ap;
   size_t n;
   va_start(ap, pFormat);
#if defined (_WINDOWS)
   n=_vsnprintf_s(pBuffer, iLength, _TRUNCATE, pFormat, ap);
#else
   n=vsnprintf(pBuffer, iLength, pFormat, ap);
#endif
   va_end(ap);
   if((n<0) || (size_t)n>=iLength)
      n=iLength-1;
   pBuffer[n]='\0';
   return n;
}