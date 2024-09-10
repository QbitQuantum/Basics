static LONG CALLBACK ctrl_handler_w32(LPEXCEPTION_POINTERS info)
{
    switch (info->ExceptionRecord->ExceptionCode) {
    case EXCEPTION_ACCESS_VIOLATION:
        switch (info->ExceptionRecord->ExceptionInformation[0])
        {
        case 0:
            LbErrorLog("Attempt to read from inaccessible memory address.\n");
            break;
        case 1:
            LbErrorLog("Attempt to write to inaccessible memory address.\n");
            break;
        case 8:
            LbErrorLog("User-mode data execution prevention (DEP) violation.\n");
            break;
        default:
            LbErrorLog("Memory access voilation, code %d.\n",(int)info->ExceptionRecord->ExceptionInformation[0]);
            break;
        }
        break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        LbErrorLog("Attempt of integer division by zero.\n");
        break;
    default:
        LbErrorLog("Failure code %x received.\n",info->ExceptionRecord->ExceptionCode);
        break;
    }
    if (!SymInitialize(GetCurrentProcess(), 0, TRUE)) {
        LbErrorLog("Failed to init symbol context\n");
    }
    else {
            _backtrace(16 , info->ContextRecord);
            SymCleanup(GetCurrentProcess());
    }
    LbScreenReset();
    LbErrorLogClose();
    return EXCEPTION_EXECUTE_HANDLER;
}