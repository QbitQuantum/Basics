BOOL assignDriveLetter(PCWSTR share)
{
    DWORD driveMap;
    char drive;
    wchar_t cmdLine[MAX_PATH];
    STARTUPINFOW startupInfo;
    PROCESS_INFORMATION processInformation;
    BOOL ok = FALSE;

    driveMap = GetLogicalDrives();

    for (drive = _MRX_MAX_DRIVE_LETTERS - 1; drive >= 0; ++drive)
    {
        if (!(driveMap & (1 << drive)))
        {
            break;
        }
    }

    if (drive < 0)
    {
        wprintf(L"Failed finding an appropriate drive for shared folder\n");
        return 1;
    }

    drive += 'A';

    wsprintf(cmdLine, L"hackssign_client.exe assign %c %s", drive, share);
    RtlZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(STARTUPINFOW);

    if (!CreateProcessW(NULL,
                        (PVOID)cmdLine,
                        NULL,
                        NULL,
                        FALSE,
                        0,
                        NULL,
                        NULL,
                        &startupInfo,
                        &processInformation))
    {
        wprintf(L"Failed starting hackssign_client.exe\n");
        return 1;
    }

    ok = (WaitForSingleObject(processInformation.hProcess, -1) == WAIT_OBJECT_0);
    CloseHandle(processInformation.hProcess);
    CloseHandle(processInformation.hThread);

    wprintf(L"%c assigned to %s\n", drive, share);

    return ok;
}