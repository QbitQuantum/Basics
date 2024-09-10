int32_t
rust_time_localtime(int64_t sec, int32_t nsec, rust_time_tm *timeptr) {
    struct tm tm;
    time_t s = sec;
    if (LOCALTIME(&s, &tm) == NULL) { return 0; }

#if defined(__WIN32__)
    int32_t utcoff = -timezone;
#elif defined(__native_client__)
    int32_t utcoff = _timezone;
#else
    int32_t utcoff = tm.tm_gmtoff;
#endif

    tm_to_rust_tm(&tm, timeptr, utcoff, nsec);
    return 1;
}