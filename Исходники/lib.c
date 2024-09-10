int lib_fprintf(FILE* file, __format_string const char* format, ...) {
    va_list params = NULL;
    int result = 0;
    va_start(params, format);
#ifdef __STDC_WANT_SECURE_LIB__
    result = vfprintf_s(file, format, params);
#else
    result = vfprintf(file, format, params);
#endif
    va_end(params);
    return result;
}