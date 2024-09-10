void pocl_cache_mk_temp_name(char* path) {
    assert(cache_topdir_initialized);
#if defined(_MSC_VER) || defined(__MINGW32__)
    char* tmp = _tempnam(cache_topdir, "pocl_");
    assert(tmp);
    int bytes_written = snprintf(path, POCL_FILENAME_LENGTH, "%s", tmp);
    free(tmp);
    assert(bytes_written > 0 && bytes_written < POCL_FILENAME_LENGTH);
#else
    int bytes_written = snprintf(path, POCL_FILENAME_LENGTH,
             "%s/temp_XXXXXX.cl", cache_topdir);
    assert(bytes_written > 0 && bytes_written < POCL_FILENAME_LENGTH);
    /* using mkstemp() instead of tmpnam() has no real benefit
     * here, as we have to pass the filename to llvm,
     * but tmpnam() generates an annoying warning... */
    int fd = mkstemps(path, 3);
    assert(fd >= 0);
    close(fd);
#endif
}