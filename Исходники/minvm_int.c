void mvm_get_error (char *message, size_t size, errno_t err) {
#ifdef BUILD_WINDOWS
    strerror_s(message, size, err);
#else
    cchar *src = strerror(err);
    if (src) {
        strncpy(message, src, size);
    }
#endif
}