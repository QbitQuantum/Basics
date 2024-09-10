HANDLE DllInjector::attachToProcess(DWORD procID)
{
    SetDebugPrivileges();

    if (IsWindows7OrGreater()) {
        return OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, procID);
    }
    else {
        if (_logger) _logger->error("get version ex Failed (probably bad win version!)! [%d]", GetLastError());
    }
   /* if (osver.dwMajorVersion == 5) {
        return OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD, 0, procID);
    }*/

    return NULL;
}