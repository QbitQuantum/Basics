//-----------------------------------------------------------------------------
unsigned TTime::toUnixStamp() const
{
    struct tm utc;
    Date_Time(m_julianDate, &utc);

#if defined(_WIN32)
    time_t epoch = _mkgmtime(&utc);
#else
    time_t epoch = timegm(&utc);
#endif

    return (unsigned)epoch;
}