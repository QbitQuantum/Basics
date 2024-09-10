int main()
{
    InitializeCriticalSectionAndSpinCount(&g_cs,4000);
    InitializeSRWLock(&g_SRWlock);
    g_hMutex = CreateMutex(NULL,FALSE,NULL);
	for (int i = 1; i < 17; i *= 2)
    {
        std::cout << std::left << std::setw(16) << "Volatile Read ";
        WaitFuncComplete(i,FuncVolatileRead);
        std::cout << std::setw(16) << "Volatile Write ";
        WaitFuncComplete(i,FuncVolatileWrite);
        std::cout << std::setw(16) << "Interlock ";
        WaitFuncComplete(i,FuncInterlock);
        std::cout << std::setw(16) << "CriticalSection ";
        WaitFuncComplete(i,FuncCriticalSection);
        std::cout << std::setw(16) << "SRWLock Read ";
        WaitFuncComplete(i,FuncSRWLockRead);
        std::cout << std::setw(16) << "SRWLock Write ";
        WaitFuncComplete(i,FuncSRWLockWrite);
        std::cout << std::setw(16) << "Mutex ";
        WaitFuncComplete(i,FuncMutex);
        std::cout << std::endl;
	}
    DeleteCriticalSection(&g_cs);
    CloseHandle(g_hMutex);
    getchar();
    return 0;
}