std::string getHTTPHeaderTimestamp ()
{
    // CHECKME This is probably called often enough that optimizing it makes
    //         sense. There's no point in doing all this work if this function
    //         gets called multiple times a second.
    char buffer[96];
    time_t now;
    time (&now);
    struct tm now_gmt{};
#ifndef _MSC_VER
    gmtime_r(&now, &now_gmt);
#else
    gmtime_s(&now_gmt, &now);
#endif
    strftime (buffer, sizeof (buffer),
        "Date: %a, %d %b %Y %H:%M:%S +0000\r\n",
        &now_gmt);
    return std::string (buffer);
}