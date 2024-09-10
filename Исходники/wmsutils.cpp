int URLSearchAndReplace (CPLString *base, const char *search, const char *fmt, ...) {
    CPLString tmp;
    va_list args;

    size_t start = base->find(search);
    if (start == std::string::npos) {
        return -1;
    }

    va_start(args, fmt);
    tmp.vPrintf(fmt, args);
    va_end(args);

    base->replace(start, strlen(search), tmp);
    return static_cast<int>(start);
}