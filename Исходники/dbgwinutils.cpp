// Open the process and break into it
bool winDebugBreakProcess(unsigned long  pid, QString *errorMessage)
{
    bool ok = false;
    HANDLE inferior = NULL;
    do {
        const DWORD rights = PROCESS_QUERY_INFORMATION|PROCESS_SET_INFORMATION
                |PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ
                |PROCESS_DUP_HANDLE|PROCESS_TERMINATE|PROCESS_CREATE_THREAD|PROCESS_SUSPEND_RESUME ;
        inferior = OpenProcess(rights, FALSE, pid);
        if (inferior == NULL) {
            *errorMessage = QString::fromLatin1("Cannot open process %1: %2").
                    arg(pid).arg(Utils::winErrorMessage(GetLastError()));
            break;
        }
        if (!DebugBreakProcess(inferior)) {
            *errorMessage = QString::fromLatin1("DebugBreakProcess failed: %1").arg(Utils::winErrorMessage(GetLastError()));
            break;
        }
        ok = true;
    } while (false);
    if (inferior != NULL)
        CloseHandle(inferior);
    return ok;
}