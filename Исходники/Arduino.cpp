int Arduino::destroy()
{
    int rv = 0;
    if (fd >= 0)
    {
        rv = closePort();
    }
    return rv;
}