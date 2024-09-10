int printf(const char *format, ...) {
   va_list va;
   va_start(va, format);
   return vprintf(format, va);
}