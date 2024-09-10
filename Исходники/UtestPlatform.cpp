static const char* VisualCppTimeString()
{
    time_t the_time = time(NULL);
    struct tm the_local_time;
    static char dateTime[80];
    LOCALTIME(&the_local_time, &the_time);
    strftime(dateTime, 80, "%Y-%m-%dT%H:%M:%S", &the_local_time);
    return dateTime;
}