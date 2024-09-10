/*
 * Wrapper for chdir library function
 */
int
platform_chdir(const char *dir)
{
#ifdef HAVE_CHDIR
#ifdef _WIN32
    int res;
    struct gc_arena gc = gc_new();
    res = _wchdir(wide_string(dir, &gc));
    gc_free(&gc);
    return res;
#else  /* ifdef _WIN32 */
    return chdir(dir);
#endif
#else  /* ifdef HAVE_CHDIR */
    return -1;
#endif
}