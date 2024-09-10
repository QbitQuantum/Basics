void NicInfo::Prime()
{
    DWORD dwRet;

    dwRet = NotifyAddrChange(&hAddrChange, &Overlap);
    if (dwRet != ERROR_IO_PENDING)
    {
        XsLog("NotifyAddrChange failed:  %d", dwRet);
    }
}