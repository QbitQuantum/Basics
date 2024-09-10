void WinDebugger::attach(ProcessId pid) {
    if (process_ != INVALID_HANDLE_VALUE) {
        kill();
    }
    process_ = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    BOOL ret = DebugActiveProcess(pid);
    if (!ret) {
        std::cerr << "error: attach: " << GetLastError() << std::endl;
        abort();
    }
}