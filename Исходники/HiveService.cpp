  void onEvent(ProcessEvent&ev){
    LOGDEBUG("ProcessEvent received");
    if(ev.getEventType()==ProcessEvent::PROCESS_STOPPED){
#ifdef __WIN32__
        HANDLE hProcess;
        hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, GetCurrentProcessId());
        TerminateProcess(hProcess, (DWORD) - 1);
        CloseHandle(hProcess);
#else
        ::kill(getpid(), 15);
#endif
    }
  }