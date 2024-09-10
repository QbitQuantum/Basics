void NativeMutexInitialize(NativeMutexType *mutex)
{
#ifndef Q_OS_WINRT
    InitializeCriticalSection(mutex);
#else
    InitializeCriticalSectionEx(mutex, 0, 0);
#endif
}