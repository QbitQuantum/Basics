int vsscanf_l(const char* str, locale_t l, const char* fmt, va_list args) {
    return vsscanf(str, fmt, args);
}