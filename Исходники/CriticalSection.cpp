void CriticalSection_WM::lock(void) {
    DWORD current = GetCurrentThreadId();
    // czekamy a¿ lock siê zwolni...
    while (this->count && this->currentThread!=current) {
        if (_WMProcess) {
            if (MsgWaitForMultipleObjectsEx(1 , &event , INFINITE , QS_ALLINPUT | QS_ALLPOSTMESSAGE , MWMO_ALERTABLE | MWMO_INPUTAVAILABLE) != WAIT_OBJECT_0)
                _WMProcess();
        } else {
            if (WaitForSingleObjectEx(event, INFINITE, TRUE) == WAIT_OBJECT_0)
                break;
        }
    }
    // ustawiamy siebie
    this->currentThread = current;
    return;
}