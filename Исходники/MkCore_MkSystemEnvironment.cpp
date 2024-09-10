MkStr MkSystemEnvironment::GetCurrentSystemTime(void) const
{
    wchar_t timeBuf[9];
    _wstrtime_s(timeBuf, 9);
    MkStr result = timeBuf;
    return result;
}