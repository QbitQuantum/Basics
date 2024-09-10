HANDLE WINAPI CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName)
{
    int flags = 0;
    if (bInitialOwner)
        flags |= CREATE_MUTEX_INITIAL_OWNER;
    return CreateMutexExW(lpMutexAttributes, lpName, flags, EVENT_ALL_ACCESS);
}