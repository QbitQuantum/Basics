int _tmain(int argc, _TCHAR* argv[])
{
    ARGUMENTS params = { 0 };					// Parsed program arguments
    HANDLE hInDev = NULL;
    HANDLE hOutDev = NULL;

    // Disk Geometry
    LONGLONG DiskSize = { 0 };			// disk size in bytes
    DWORD SectorSize;					// Physical sector size
    std::queue <LPVOID> cola;

    // Thread synchronization
    HANDLE hMutex;
    HANDLE hThread[2] = { 0 };
    DWORD ThreadID[2] = { 0 };

    if (!ParseProgramArguments(&params, argc, argv)) {
        return 1;
    }

    BQUEUE data = { &cola, 0};					// data queue

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    HANDLE hToken;
    OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &hToken);
    DWORD infoLen;

    TOKEN_ELEVATION elevation;
    GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &infoLen);
    if (!elevation.TokenIsElevated)
    {
        wprintf(L"This program must run in elevated mode\n");
        return -1;
    }
#else
#error you are using an old version of sdk or not supported operating system
#endif

    if (!OpenDescriptors(params.sInDev, params.sOutDev, &hInDev, &hOutDev))
    {
        return -1;
    }

    if (!GetDescriptorGeometry(hInDev, &SectorSize, &DiskSize))
    {
        return -1;
    }

    /* Mutex Creation */
    hMutex = CreateMutex(NULL, FALSE, NULL);

    if (hMutex == NULL)
    {
        wprintf(L"CreateMutex() error: %d\n", GetLastError());
        return -1;
    }

    /* The party start now	*/
    wprintf(L">>> windd %s - By Luis Gonzalez Fernandez\n", VERSION);
    if (!params.NoDisclaimer)
        Disclaimer();
    wprintf(L"%s => %s\n", params.sInDev, params.sOutDev);

    /* Reader Thread */
    TPARAMS ReaderParams = { 0 };
    ReaderParams.hDev = hInDev;
    ReaderParams.cola = &data;
    ReaderParams.StartOffset = params.dwSkip;			// skip n bytes at input
    ReaderParams.EndOffset = DiskSize;

    if (params.dwInBs)
        ReaderParams.SectorSize = params.dwInBs;
    else
        ReaderParams.SectorSize = SectorSize;

    ReaderParams.MemBuff = params.dwBuff;
    ReaderParams.Mutex = hMutex;
    ReaderParams.DiskSize = DiskSize;
    ReaderParams.DataProcessed = 0;
    ReaderParams.Verbose = params.Verbose;

    hThread[0] = CreateThread(NULL, 0, ReadSect, &ReaderParams, 0, &ThreadID[0]);

    /* Writer Thread */
    TPARAMS WriterParams = { 0 };
    WriterParams.hDev = hOutDev;
    WriterParams.cola = &data;
    WriterParams.StartOffset = params.dwSeek;				// seek until this offset at write.
    WriterParams.EndOffset = (DiskSize + params.dwSeek - params.dwSkip);

    if (params.dwOutBs)
        WriterParams.SectorSize = params.dwOutBs;
    else
        WriterParams.SectorSize = SectorSize;

    WriterParams.Mutex = hMutex;
    WriterParams.DiskSize = DiskSize;
    WriterParams.DataProcessed = 0;
    WriterParams.Verbose = params.Verbose;

    hThread[1] = CreateThread(NULL, 0, WriteSect, &WriterParams, 0, &ThreadID[1]);

    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

    if (ReaderParams.DataProcessed == WriterParams.DataProcessed)
        wprintf(L"Done!\n");
    else
        wprintf(L"Error, %lu bytes are not copied.\n", (ReaderParams.DataProcessed - WriterParams.DataProcessed));

    CloseHandle(hInDev);
    CloseHandle(hOutDev);

    return 0;
}