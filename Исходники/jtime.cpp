void setLocalTZ()
{
    _wputenv(localTZ);
    _tzset();
}