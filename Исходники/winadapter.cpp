StringBuffer unixTimeToString(const unsigned long unixTime, const bool isUTC) {

    StringBuffer ret;
    struct tm sysTime;
    __time64_t tstamp = (__time64_t)unixTime;

    int err = _gmtime64_s(&sysTime, &tstamp);
    if (err) {
        LOG.error("error in _gmtime64_s (code %d)", err);
        return ret;
    }

    int year  = sysTime.tm_year + 1900;  // starting from 1900
    int month = sysTime.tm_mon + 1;      // range [0-11]
    ret.sprintf("%d%02d%02dT%02d%02d%02d", year, month, sysTime.tm_mday, sysTime.tm_hour, sysTime.tm_min, sysTime.tm_sec);

    if (isUTC) {
        ret.append("Z");
    }
    return ret;
}