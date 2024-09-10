void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    if (argc < 2) return;

    DWORD    dwMaxThread, dwExitCode, dwCount = 0, dwTotal = 0;
    LPHANDLE phThread;
    SYSTEM_INFO si;
    LARGE_INTEGER lFrequency, lStopCounter, lStartCounter;

    GetSystemInfo(&si);
    dwMaxThread = si.dwNumberOfProcessors << 1;
    g_hSemaphore = CreateSemaphore(NULL, 1, dwMaxThread, NULL);
    if (g_hSemaphore == NULL)
    {
        printf("CreateSemaphore() failed.\n");
    }
    else
    {
        QueryPerformanceFrequency(&lFrequency);
        QueryPerformanceCounter(&lStartCounter);
        hHeap = GetProcessHeap();
        ExtractDict(pbDict);
        phThread = (LPHANDLE)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (argc - 1) * sizeof(*phThread));
        for (DWORD i = 0; i != argc - 1; ++i)
            phThread[i] = CreateThread(NULL, 0, Import, (LPVOID)argv[i + 1], 0, NULL);

        WaitForMultipleObjectsEx(argc - 1, phThread, TRUE, INFINITE, FALSE);
        for (DWORD i = 0; i != argc - 1; ++i)
        {
            GetExitCodeThread(phThread[i], &dwExitCode);
            dwCount += dwExitCode;
        }

        for (char i = 0; i != countof(Array_of_Data); ++i)
        {
            HeapFree(hHeap, 0, pbDict[i]);
        }

        CloseHandle(g_hSemaphore);
        QueryPerformanceCounter(&lStopCounter);
        printf("Success: %d\n"
               "Elapsed time: %lf ms\n",
               dwCount,
               (lStopCounter.QuadPart - lStartCounter.QuadPart) * 1000.0 / lFrequency.QuadPart);
    }
}