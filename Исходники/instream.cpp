int StrReader::read_fmt(const char *fmt, va_list ap) {
    if (pos >= size) {
        bad = 1; return 0;
    }
    return vsscanf(pc+pos,fmt,ap);
}