char *
OSSprintfFromSystem(const char *format, ...)
{
   va_list argptr;
   va_start(argptr, format);
   auto size = _vscprintf(format, argptr) + 1;
   auto buffer = reinterpret_cast<char *>(OSAllocFromSystem(size, 4));
   vsprintf_s(buffer, size, format, argptr);
   va_end(argptr);
   return buffer;
}