void test___va_start_ignore_const(const char *format, ...) {
  va_list args;
  ((void)(__va_start(&args, (&const_cast<char &>(reinterpret_cast<const volatile char &>(format))), ((sizeof(format) + 4 - 1) & ~(4 - 1)), (&const_cast<char &>(reinterpret_cast<const volatile char &>(format))))));
}