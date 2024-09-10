process_handle get_process_handle() {
#ifdef _WIN32
    return _getpid();
#else
    return getpid();
#endif
}