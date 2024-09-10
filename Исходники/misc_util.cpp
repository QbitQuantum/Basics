time_t Util::sdTime::MakeGmTime(tm& timeUtc)
{
#if (_MSC_VER < MSVC_VER_2005)
    // VC++ 2003 doesn't have _mkgmtime
    // This does not seem to work properly with DST time zones sometimes - if that's of any concern for you, please upgrade your compiler :)
    TIME_ZONE_INFORMATION tzi;
    GetTimeZoneInformation(&tzi);
    const time_t timeUtcTimeT = mktime(&timeUtc) - tzi.Bias * 60;
#else
    const time_t timeUtcTimeT = _mkgmtime(&timeUtc);
#endif
    return timeUtcTimeT;
}