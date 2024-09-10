DWORD wtodw(const wchar_t* num)
{
    if(NULL == num)
        return 0;
    //in VS2003 atoi/wtoi would convert an unsigned value even though it would overflow a signed value.  No more, and it causes trouble!
    __int64 res = _wtoi64(num);
    _ASSERT(res <= ULONG_MAX);
    return (DWORD)res;
}