void info (const char*fmt, ...) {
    va_list ap;
    va_start(ap,fmt);
    printf("[INFO]: ");
    vprintf(fmt,ap);
}