POV_ULONG Timer::GetThreadTime () const
{
    FILETIME    ct;
    FILETIME    et;
    __int64     kt;
    __int64     ut;
    BOOL        success;

    POV_ASSERT (mCPUTimeSupported);

    success = GetThreadTimes (mThreadHandle, &ct, &et,
                              reinterpret_cast<FILETIME *>(&kt),
                              reinterpret_cast<FILETIME *>(&ut));

    POV_ASSERT (success);
    if (!success)
        return 0;

    return ((kt + ut) / 10000);
}