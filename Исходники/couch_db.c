LIBCOUCHSTORE_API
void couchstore_last_os_error(char* buf, size_t size) {
    struct _os_error *err = get_os_error_store();
#ifndef WINDOWS
    snprintf(buf, size, "errno = %d: `%s'", err->errno_err, strerror(err->errno_err));
#else
    char* win_msg = NULL;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, err->win_err,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   (LPTSTR) &win_msg,
                   0, NULL);
    snprintf(buf, size, "errno = %d: `%s', WINAPI error = %d: `%s'",
             err->errno_err, strerror(err->errno_err),
             err->win_err, win_msg);
    LocalFree(win_msg);
#endif
}