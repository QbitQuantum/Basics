static void ini_ssl(void) {
    static int inited = 0;
    if (inited) return;
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    SSL_library_init();
    while (!RAND_status()) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        RAND_add(&ts.tv_nsec, sizeof(ts.tv_nsec), 0.1);
    }
    inited = 1;
#ifdef WIN32
    {
        WCHAR fnm[MAX_PATH];
        char buf[MAX_PATH];
        static char sbuf[MAX_PATH];
        if (SHGetFolderPathW(0, CSIDL_WINDOWS, NULL, 0, fnm) != S_OK) {
            check_error(set_errno(ERR_OTHER, "Cannot get WINDOWS folder path"));
        }
        if (!WideCharToMultiByte(CP_UTF8, 0, fnm, -1, buf, sizeof(buf), NULL, NULL)) {
            check_error(set_win32_errno(GetLastError()));
        }
        snprintf(sbuf, sizeof(sbuf), "%s/TCF", buf);
        tcf_dir = sbuf;
    }
#endif
}