void terminate(wchar_t *message, ...) {
    va_list argptr;
    va_start(argptr, message);
    vfwprintf(stderr, message, argptr);
    va_end(argptr);
    fwprintf(stderr, L"\n");

    exit(1);
}