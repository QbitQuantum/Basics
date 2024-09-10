void ProcessLister::getProcessImageInformation( HANDLE hProcess, Process* process )
{
    DWORD_PTR readImagebase = 0;
    process->imageBase = 0;
    process->imageSize = 0;

    if (hProcess && process->pebAddress)
    {
        PEB_CURRENT * peb = (PEB_CURRENT *)process->pebAddress;

        if (ReadProcessMemory(hProcess, &peb->ImageBaseAddress, &readImagebase, sizeof(DWORD_PTR), 0))
        {
            process->imageBase = readImagebase;
            process->imageSize = (DWORD)ProcessAccessHelp::getSizeOfImageProcess(hProcess, process->imageBase);
        }
    }
}