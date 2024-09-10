/*
 * Wraps `gmtime` functionality for multiple platforms. This
 * converts a time value to a time structure in UTC.
 *
 * Returns 0 on success, -1 on failure.
 */
static int
get_gmtime(NPY_TIME_T *ts, struct tm *tms)
{
    char *func_name = "<unknown>";
#if defined(_WIN32)
 #if defined(_MSC_VER) && (_MSC_VER >= 1400)
    if (gmtime_s(tms, ts) != 0) {
        func_name = "gmtime_s";
        goto fail;
    }
 #elif defined(__GNUC__) && defined(NPY_MINGW_USE_CUSTOM_MSVCR)
    if (_gmtime64_s(tms, ts) != 0) {
        func_name = "_gmtime64_s";
        goto fail;
    }
 #else
    struct tm *tms_tmp;
    tms_tmp = gmtime(ts);
    if (tms_tmp == NULL) {
        func_name = "gmtime";
        goto fail;
    }
    memcpy(tms, tms_tmp, sizeof(struct tm));
 #endif
#else
    if (gmtime_r(ts, tms) == NULL) {
        func_name = "gmtime_r";
        goto fail;
    }
#endif

    return 0;

fail:
    PyErr_Format(PyExc_OSError, "Failed to use '%s' to convert "
                                "to a UTC time", func_name);
    return -1;
}