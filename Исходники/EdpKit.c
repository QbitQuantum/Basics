static void FormatAt(char* buffer, int32_t len, time_t now)
{
#if 0
    struct tm timinfo;

    if (now == 0)
    {
        now = time(0);
    }
#endif

#if defined(linux) || defined(__linux) || defined(__linux__)
    strftime(buffer, len, "%F %T", localtime_r(&now, &timinfo));
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    localtime_s(&timinfo, &now);
    strftime(buffer, len, "%F %T", &timinfo);
#endif
}