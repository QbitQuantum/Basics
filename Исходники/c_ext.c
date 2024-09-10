static int l_gettime(lua_State *L)
{
#if 0
    union {
        FILETIME ft;
        ULONGLONG ull;
    } u = {0};
    const double scale = 1.0e9;
    GetSystemTimePreciseAsFileTime(&u.ft);
#elif 0
    union {
        LARGE_INTEGER li;
        ULONGLONG ull;
    } u = {0};
    const double scale = 1.0e7;
    NtQuerySystemTime(&u.li);
#else
    union {
        FILETIME ft;
        ULONGLONG ull;
    } u = {0};
    const double scale = 1.0e7;

    SYSTEMTIME st = {0};
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &u.ft);

#endif

    const double win32Epoch = ((double)u.ull)/scale;
    const double unixEpoch = win32Epoch - SEC_TO_UNIX_EPOCH;

    lua_pushnumber(L, (lua_Number)(unixEpoch));
    return 1;
}