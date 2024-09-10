const long TimeF::utcOffset()
{
    long tz;

#ifdef __GNUC__
    tz = timezone;
#else // __GNUC__
    _get_timezone(&tz);
#endif // __GNUC__

    return tz;
}