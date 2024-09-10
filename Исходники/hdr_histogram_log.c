static int print_time(FILE* f, hdr_timespec* timestamp)
{
    char time_str[128];
    struct tm date_time;

    if (!timestamp)
    {
        return 0;
    }

#if defined(__WINDOWS__)
	_gmtime32_s(&date_time, &timestamp->tv_sec);
#else
    gmtime_r(&timestamp->tv_sec, &date_time);
#endif
    long ms = timestamp->tv_nsec / 1000000;
    strftime(time_str, 128, "%a %b %X %Z %Y", &date_time);

    return fprintf(
        f, "#[StartTime: %d.%ld (seconds since epoch), %s]\n",
        (int) timestamp->tv_sec, ms, time_str);
}