static bool compare_timespec(hdr_timespec* a, hdr_timespec* b)
{
    char a_str[128];
    char b_str[128];

    long a_tv_msec = ns_to_ms(a->tv_nsec);
    long b_tv_msec = ns_to_ms(b->tv_nsec);

    if (a->tv_sec == b->tv_sec && a_tv_msec == b_tv_msec)
    {
        return true;
    }

    if (a->tv_sec != b->tv_sec)
    {
#if defined(_MSC_VER)
		_ctime32_s(a_str, sizeof(a_str), &a->tv_sec);
		_ctime32_s(b_str, sizeof(b_str), &b->tv_sec);
		printf("tv_sec: %s != %s\n", a_str, b_str);
#else
        printf(
            "tv_sec: %s != %s\n",
            ctime_r(&a->tv_sec, a_str),
            ctime_r(&b->tv_sec, b_str));
#endif
    }

    if (a_tv_msec == b_tv_msec)
    {
        printf("%ld != %ld\n", a->tv_nsec, b->tv_nsec);
    }

    return false;
}