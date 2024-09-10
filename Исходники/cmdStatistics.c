static
INT
DisplayServerStatistics(VOID)
{
    PSERVER_INFO_100 ServerInfo = NULL;
    PSTAT_SERVER_0 StatisticsInfo = NULL;
    LARGE_INTEGER LargeValue;
    FILETIME FileTime, LocalFileTime;
    SYSTEMTIME SystemTime;
    WORD wHour;
    INT nPaddedLength = 35;
    NET_API_STATUS Status;

    Status = NetServerGetInfo(NULL, 100, (PBYTE*)&ServerInfo);
    if (Status != NERR_Success)
        goto done;

    Status = NetStatisticsGet(NULL,
                              SERVICE_SERVER,
                              0,
                              0,
                              (LPBYTE*)&StatisticsInfo);
    if (Status != NERR_Success)
        goto done;

    PrintMessageStringV(4624, ServerInfo->sv100_name);
    ConPrintf(StdOut, L"\n\n");

    RtlSecondsSince1970ToTime(StatisticsInfo->sts0_start,
                              &LargeValue);
    FileTime.dwLowDateTime = LargeValue.u.LowPart;
    FileTime.dwHighDateTime = LargeValue.u.HighPart;
    FileTimeToLocalFileTime(&FileTime, &LocalFileTime);
    FileTimeToSystemTime(&LocalFileTime, &SystemTime);

    wHour = SystemTime.wHour;
    if (wHour == 0)
    {
        wHour = 12;
    }
    else if (wHour > 12)
    {
        wHour = wHour - 12;
    }

    PrintMessageString(4600);
    ConPrintf(StdOut, L" %d/%d/%d %d:%02d %s\n\n\n",
              SystemTime.wMonth, SystemTime.wDay, SystemTime.wYear,
              wHour, SystemTime.wMinute,
              (SystemTime.wHour >= 1 && SystemTime.wHour < 13) ? L"AM" : L"PM");

    PrintPaddedMessageString(4601, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n", StatisticsInfo->sts0_sopens);

    PrintPaddedMessageString(4602, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n", StatisticsInfo->sts0_stimedout);

    PrintPaddedMessageString(4603, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n\n", StatisticsInfo->sts0_serrorout);

    LargeValue.u.LowPart = StatisticsInfo->sts0_bytessent_low;
    LargeValue.u.HighPart = StatisticsInfo->sts0_bytessent_high;
    PrintPaddedMessageString(4604, nPaddedLength);
    ConPrintf(StdOut, L"%I64u\n", LargeValue.QuadPart / 1024);

    LargeValue.u.LowPart = StatisticsInfo->sts0_bytesrcvd_low;
    LargeValue.u.HighPart = StatisticsInfo->sts0_bytesrcvd_high;
    PrintPaddedMessageString(4605, nPaddedLength);
    ConPrintf(StdOut, L"%I64u\n", LargeValue.QuadPart / 1024);

    PrintPaddedMessageString(4606, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n\n", StatisticsInfo->sts0_avresponse);

    PrintPaddedMessageString(4610, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n", StatisticsInfo->sts0_syserrors);

    PrintPaddedMessageString(4612, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n", StatisticsInfo->sts0_permerrors);

    PrintPaddedMessageString(4611, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n\n", StatisticsInfo->sts0_pwerrors);

    PrintPaddedMessageString(4608, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n", StatisticsInfo->sts0_fopens);

    PrintPaddedMessageString(4613, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n", StatisticsInfo->sts0_devopens);

    PrintPaddedMessageString(4609, nPaddedLength);
    ConPrintf(StdOut, L"%lu\n\n", StatisticsInfo->sts0_jobsqueued);

    PrintMessageString(4620);
    ConPrintf(StdOut, L"\n");

    ConPrintf(StdOut, L"  ");
    PrintPaddedMessageString(4621, nPaddedLength - 2);
    ConPrintf(StdOut, L"%lu\n", StatisticsInfo->sts0_bigbufneed);

    ConPrintf(StdOut, L"  ");
    PrintPaddedMessageString(4622, nPaddedLength - 2);
    ConPrintf(StdOut, L"%lu\n\n", StatisticsInfo->sts0_reqbufneed);

done:
    if (StatisticsInfo != NULL)
        NetApiBufferFree(StatisticsInfo);

    if (ServerInfo != NULL)
        NetApiBufferFree(ServerInfo);

    return 0;
}