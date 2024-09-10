unsigned int __stdcall Win32Thread::threadFunc(void *args) {
    auto pThread = reinterpret_cast<Win32Thread*>(args);

    if (pThread) {
        pThread->Run();
    }

    _endthreadex(0);
    return 0;
}