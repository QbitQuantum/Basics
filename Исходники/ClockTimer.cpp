void ClockTimer::Tick()
{
    _tzset();
    // Obtain operating system-style time.
    _strtime(tmpbuf);
    notify();
}