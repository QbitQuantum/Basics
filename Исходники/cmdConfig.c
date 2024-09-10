static
INT
DisplayWorkstationConfig(VOID)
{
    PWKSTA_INFO_100 WorkstationInfo = NULL;
    PWKSTA_USER_INFO_1 UserInfo = NULL;
    PWKSTA_TRANSPORT_INFO_0 TransportInfo = NULL;
    DWORD dwRead = 0, dwTotal = 0, i;
    INT nPaddedLength = 38;
    NET_API_STATUS Status;

    Status = NetWkstaGetInfo(NULL, 100, (PBYTE*)&WorkstationInfo);
    if (Status != NERR_Success)
        goto done;

    Status = NetWkstaUserGetInfo(NULL, 1, (PBYTE*)&UserInfo);
    if (Status != NERR_Success)
        goto done;

    Status = NetWkstaTransportEnum(NULL,
                                   0,
                                   (PBYTE*)&TransportInfo,
                                   MAX_PREFERRED_LENGTH,
                                   &dwRead,
                                   &dwTotal,
                                   NULL);
    if (Status != NERR_Success)
        goto done;

    PrintPaddedMessageString(4450, nPaddedLength);
    ConPrintf(StdOut, L"\\\\%s\n", WorkstationInfo->wki100_computername);

    PrintPaddedMessageString(4468, nPaddedLength);
    ConPuts(StdOut, L"...\n");

    PrintPaddedMessageString(4451, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", UserInfo->wkui1_username);

    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4453, nPaddedLength);
    ConPuts(StdOut, L"\n");
    for (i = 0; i < dwRead; i++)
    {
        ConPrintf(StdOut, L"      %s (%s)\n",
                  &TransportInfo[i].wkti0_transport_name[8],
                  TransportInfo[i].wkti0_transport_address);
    }
    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4452, nPaddedLength);
    ConPrintf(StdOut, L"%lu.%lu\n",
              WorkstationInfo->wki100_ver_major,
              WorkstationInfo->wki100_ver_minor);

    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4455, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", WorkstationInfo->wki100_langroup);

    PrintPaddedMessageString(4469, nPaddedLength);
    ConPuts(StdOut, L"...\n");

    PrintPaddedMessageString(4456, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", UserInfo->wkui1_logon_domain);

    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4458, nPaddedLength);
    ConPuts(StdOut, L"...\n");

    PrintPaddedMessageString(4459, nPaddedLength);
    ConPuts(StdOut, L"...\n");

    PrintPaddedMessageString(4460, nPaddedLength);
    ConPuts(StdOut, L"...\n");

done:
    if (TransportInfo != NULL)
        NetApiBufferFree(TransportInfo);

    if (UserInfo != NULL)
        NetApiBufferFree(UserInfo);

    if (WorkstationInfo != NULL)
        NetApiBufferFree(WorkstationInfo);

    return 0;
}