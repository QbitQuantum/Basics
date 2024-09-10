void   STDCALL OSInit()
{
    timeBeginPeriod(1);

    TIMECAPS chi;
    timeGetDevCaps(&chi, sizeof(chi));

    GetSystemInfo(&si);

    osVersionInfo.dwOSVersionInfoSize = sizeof(osVersionInfo);
    GetVersionEx(&osVersionInfo);

    if (OSGetVersion() == 8)
        bWindows8 = TRUE;

    QueryPerformanceFrequency(&clockFreq);
    QueryPerformanceCounter(&startTime);
    startTick = GetTickCount();
    prevElapsedTime = 0;

    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION pInfo = NULL, pTemp = NULL;
    DWORD dwLen = 0;
    if(!GetLogicalProcessorInformation(pInfo, &dwLen))
    {
        if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            pInfo = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(dwLen);

            if(GetLogicalProcessorInformation(pInfo, &dwLen))
            {
                pTemp = pInfo;
                DWORD dwNum = dwLen/sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

                coreCount = 0;
                logicalCores = 0;

                for(UINT i=0; i<dwNum; i++)
                {
                    if(pTemp->Relationship == RelationProcessorCore)
                    {
                        coreCount++;
                        logicalCores += CountSetBits(pTemp->ProcessorMask);
                    }

                    pTemp++;
                }
            }

            free(pInfo);
        }
    }

    hProfilerMutex = OSCreateMutex();
}