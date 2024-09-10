bool BoIInjector::IsBoIRunning()
{
    bool isaac_running = false;

    PROCESSENTRY32W proc_entry = { 0 };
    proc_entry.dwSize = sizeof(proc_entry);
    HANDLE proc_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (proc_snapshot == INVALID_HANDLE_VALUE)
        throw std::runtime_error("[IsBoIRunning] Unable to obtain the system's process list to check if Isaac is running.");
    if (!Process32FirstW(proc_snapshot, &proc_entry))
        throw std::runtime_error("[IsBoIRunning] Unable to read the system's process list to check if Isaac is running.");
    do
    {
        if (std::wstring(proc_entry.szExeFile) == WCHAR_BOI_PROCESS_NAME)
        {
            isaac_running = true;
            break;
        }
    } while (Process32NextW(proc_snapshot, &proc_entry));
    CloseHandle(proc_snapshot);

    return isaac_running;
}