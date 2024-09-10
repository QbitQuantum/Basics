/**
* @see clock.h
* @private
* Mock a clock on the PC 
* @param clockParam the clock
*/
ClockData* _readPcClock(Clock* clockParam) {
    time_t rawtime;
    struct tm timeinfo;
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    ClockData* data = &(clockParam->clockData);
    data->year = timeinfo.tm_year - 100; // we store the date after 2000 (100 = 2000 - 1900)
    data->month = timeinfo.tm_mon;
    data->day = timeinfo.tm_mday;
    data->dayofweek = timeinfo.tm_wday;
    data->hour = timeinfo.tm_hour;
    data->minute = timeinfo.tm_min;
    data->second = timeinfo.tm_sec;

    return &(clockParam->clockData);
}